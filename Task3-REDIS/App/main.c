#include <stdio.h>
#include <string.h>
#include <time.h>
#include <malloc.h>
#include <hiredis.h>
#include <sqlite3.h>
#include "hist.h"
#include "bdfile.h"

int main(){
    //creating and filling the main and time arrays
    int cycles_count = 100;
    int amount_of_channels = 100;
    int *main_arr = (int *)malloc(amount_of_channels * sizeof(int));
    for(int i = 0; i < amount_of_channels; i++){
        main_arr[i] = 0;
    }
    float *times_arr = (float *)malloc(amount_of_channels * sizeof(float));
    

    //creating indexes and time var-s
    int current_index = 1; //int-formated index for post
    char str_ind[6]; //string-formated index from subscribe
    int success_count;
    float time_spent = 0;
    float total_time_spent = 0;
    float max_time = 0;
    float avg_time = 0;

    //creating hist vars
    int histogram[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,};
    max_hist = 25*amount_of_channels; //50 - max experimental operation time
    hist_step = max_hist/10;

    //creating DB
    sqlite3 *DB;
    int exit = sqlite3_open("Times.db", &DB);
    if (exit) { 
        printf("Ошибка при открытии базы данных\n");
    } 
    create_DB(DB);
    

    //creating connections for subs and posts
    redisContext *subscript_con = redisConnect("127.0.0.1", 6379);
    redisContext *publish_con = redisConnect("127.0.0.1", 6379);
    if ((subscript_con == NULL || subscript_con->err) || (publish_con == NULL || publish_con->err)){
        printf("Connection error\n");
    }

    //subscribing for all 2* channels
    redisReply *reply_pub;
    redisReply *reply_sub;
    reply_sub = redisCommand(subscript_con,"PSUBSCRIBE Listening2_*");
    freeReplyObject(reply_sub);

    //publishing message with amount of channels
    reply_pub = redisCommand(publish_con, "PUBLISH Listening1_SPEC %d", 100);
    freeReplyObject(reply_pub);
    printf("Data sending in process:");
    fflush(stdout);
    for(int j = 0; j < cycles_count; j++){
        //sending messages on 1* shannels and listening for replies on 2* channels
        while(current_index <= amount_of_channels){
            reply_pub = redisCommand(publish_con, "SET VAL%d %d", current_index, main_arr[current_index-1]);
            reply_pub = redisCommand(publish_con, "PUBLISH Listening1_%d SENT", current_index);
            freeReplyObject(reply_pub);
            int time = clock();

            if(redisGetReply(subscript_con,(void *)&reply_sub) == REDIS_OK) {
                time_spent = (clock()-(float)time)/CLOCKS_PER_SEC;
                times_arr[current_index-1];
                total_time_spent += time_spent;
                //printf("End. Index: %d. Secs spent: %f\n", current_index, time_spent);

                reply_pub = redisCommand(publish_con, "GET VAL%d", current_index);
                int value_from_arr = atoi(reply_pub->str);
                main_arr[current_index-1] = value_from_arr;
                freeReplyObject(reply_pub);
            
                const char* channel = reply_sub->element[2]->str;
                strncpy(str_ind, channel + 11, 5);
                str_ind[5] = '\0';
                current_index = atoi(str_ind);
                //printf("%d\n", current_index);

                freeReplyObject(reply_sub);
                current_index++;
            }   
        }
        for(int i = 0; i < amount_of_channels; i++){
            success_count+=insert(DB, j, i, times_arr[i]*1000000);
        }
        //printf("Successful inserts: %d/%d\n", succes_count, amount_of_channels);

        total_time_spent*=1000000; //to mcs
        put_value(total_time_spent, histogram);
        //printf("%f\n", total_time_spent);
        max_time = (total_time_spent > max_time) ? total_time_spent : max_time;
        avg_time += total_time_spent/cycles_count;

        current_index = 1;
        total_time_spent = 0;
        printf("|");
        fflush(stdout);
    }

    float hist_norm[10];
    norm_hist(histogram, hist_norm);
    printf("\n");
    draw_hist(hist_norm);
    printf("Max time: %f\nAvg time: %f\n", max_time, avg_time);
    printf("Successful DB inserts: %d/%d", success_count, amount_of_channels*cycles_count);

    //disconnecting
    redisFree(subscript_con);
    redisFree(publish_con);
    sqlite3_close(DB);

    return 0;
}
#include <stdio.h>
#include <hiredis.h>
#include <string.h>
#include <time.h>

int main(){
    int current_index = 1; //int-formated index for post
    char str_ind[6]; //string-formated index from subscribe

    redisContext *subscript_con = redisConnect("127.0.0.1", 6379);
    redisContext *publish_con = redisConnect("127.0.0.1", 6379);
    if ((subscript_con == NULL || subscript_con->err) || (publish_con == NULL || publish_con->err)){
        printf("Connection error\n");
    }

    redisReply *reply_pub;
    redisReply *reply_sub;
    reply_sub = redisCommand(subscript_con,"PSUBSCRIBE Listening1_*");
    freeReplyObject(reply_sub);

    do{
        if(redisGetReply(subscript_con,(void *)&reply_sub) == REDIS_OK) {
            //printf("Reply: %s\n", reply_sub->element[2]->str);
            const char* channel = reply_sub->element[2]->str;
            strncpy(str_ind, channel + 11, 5);
            //printf("%s\n", reply_sub->element[3]->str);
        }
    } while(strcmp(str_ind, "SPEC") != 0);

    int indexes_remain = atoi(reply_sub->element[3]->str);
    freeReplyObject(reply_sub);

    for(int j = 0; j < 100; j++){
        while(current_index <= 100){
            if(redisGetReply(subscript_con,(void *)&reply_sub) == REDIS_OK) {
                //printf("Reply: %s-%d\n", reply_sub->element[2]->str, j);
                const char* channel = reply_sub->element[2]->str;
                strncpy(str_ind, channel + 11, 5);
                current_index = atoi(str_ind);
                freeReplyObject(reply_sub);

                reply_pub = redisCommand(publish_con, "GET VAL%d", current_index);
                int value_from_arr = atoi(reply_pub->str);
                value_from_arr++;
                freeReplyObject(reply_pub);

                reply_pub = redisCommand(publish_con, "SET VAL%d %d", current_index, value_from_arr);
                freeReplyObject(reply_pub);

                reply_pub = redisCommand(publish_con, "PUBLISH Listening2_%d UPDATED-NEXT", current_index);
                freeReplyObject(reply_pub);
                current_index++;
            }
        }
        current_index = 1;
        //printf("%d\n", j);
    }

    redisFree(subscript_con);
    redisFree(publish_con);

    return 0;
}
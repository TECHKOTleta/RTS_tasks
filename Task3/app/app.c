#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <libmemcached/memcached.h>

#include <sqlite3.h>

#include <time.h>
#include "dbfile.h"
#include "math.h"
#include "hist.h"


int main() {
    //------------------create an array------------------
    int cn;
    while (1) {
        printf("Enter a number: ");
        if (scanf("%d", &cn) == 1 && cn > 0) {
            break;
        }
        while(getchar() != '\n');
    }

    float time_all;
    int histogram[10] = {0};
    float histogram_f[10] = {0.0};
    float time_array[10];
    int cycle = 10;
    int *time_array_1000 = malloc(cn * cycle * sizeof(int));

    //-----------------creating DB-----------------
    sqlite3 *DB;
    int exit = sqlite3_open("Times.db", &DB);
    if (!exit) {
        printf("Error open DB\n");
    }
    create_DB(DB);
    
    //-----------------for 1---------------------
    for (int i = 0; i < cycle; i++) {
    time_all = clock();
    int *array = malloc(cn * sizeof(int));

    for (int i = 0; i < cn; i++) {
        array[i] = 0;
    }

    memcached_st *memc;
    memcached_return_t rc;
    memc = memcached_create(NULL);
    memcached_server_st *servers = memcached_server_list_append(NULL, "127.0.0.1", 11211, &rc);
    rc = memcached_server_push(memc, servers);
    if (rc != MEMCACHED_SUCCESS) {
        printf("Connect error\n");
    }

    char str_cn[8];
    sprintf(str_cn, "%d", cn);
    char key[256];
    size_t message_length;
    uint32_t flags;

    float time_channel;
    float time_cycle;

    snprintf(key, sizeof(key), "total");
    rc = memcached_set(memc, key, strlen(key), str_cn, strlen(str_cn), 0, 0);

    if (rc == MEMCACHED_SUCCESS) {
        printf("Message %s sends successfully on key %s\n", str_cn, key);
    }
        snprintf(key, sizeof(key), "get_total");
        while (1) {
            char *message = memcached_get(memc, key, strlen(key), &message_length, &flags, &rc);
            if (message) {
                printf("Message get: %s\n", message);
                free(message);
                break;
            }
            else {
                printf("Error get message with total\n");
                sleep(1);
            }
        }
       
    for (int j = 0; j < cn; j++) {
        sprintf(str_cn, "%d", j);
        snprintf(key, sizeof(key), "input_%s", str_cn);
        
        char input_message[20];
        snprintf(input_message, sizeof(input_message), "%d", array[j]);

        rc = memcached_set(memc, key, strlen(key), input_message, strlen(input_message), 0, 0);
        if (rc == MEMCACHED_SUCCESS) {
            time_channel = clock();
            //printf("Message %s sends successfully with key %s\n", input_message, key);
        }
        else {
            //printf("Error message get");
        }
            snprintf(key, sizeof(key), "output_%s", str_cn);
            while (1) { 
                char *message = memcached_get(memc, key, strlen(key), &message_length, &flags, &rc);
                if (message) {
                    time_channel = clock() - time_channel;
                    double microseconds = (double)time_channel *1000000 / CLOCKS_PER_SEC;
                    printf("Message %s key %s get with time: %f\n", message, key, microseconds);
                    time_array_1000[j+i] = microseconds;
                    free(message);
                    break;
                }
                else {
                    //printf("Error message get with key %s\n", key);
                }
            }
        }

        rc = memcached_flush(memc, 0);

    time_all = clock() - time_all;
    double microseconds = (double)time_all * 1000000 /CLOCKS_PER_SEC;
    printf("TIME ALL: %f\n", microseconds);
    int total_time_spent = microseconds;
    put_value(total_time_spent, histogram);
    time_array[i] = total_time_spent;
    }

    float hist_norm[10];
    norm_hist(histogram, hist_norm);
    printf("\n");
    draw_hist(hist_norm);
    float max_time = 0;
    float sum_of_time;
    for (int i = 0; i < cycle; i ++) {
        sum_of_time = sum_of_time + time_array[i];
        if (time_array[i] > max_time) {
            max_time = time_array[i];
        }
    }
    float avg_time = sum_of_time/cycle;

    printf("Max time: %f\nAvg time: %f\n", max_time, avg_time);

    //--------------add to DB----------------
    int success_count = 0;
    for (int i = 0; i < cycle; i ++) {
        for (int j = 0; j < cn; j++) {
            success_count = success_count + insert(DB, i, j, time_array_1000[i+j]);
        }
    }

    sqlite3_close(DB);

    printf("Successful DB inserts: %d/%d", success_count, cycle*cn); 
}

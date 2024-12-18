#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <libmemcached/memcached.h>
#include <time.h>

int main() {
    memcached_st *memc;
    memcached_return_t rc;

    memc = memcached_create(NULL);
    memcached_server_st *servers = memcached_server_list_append(NULL, "127.0.0.1", 11211, &rc);
    rc = memcached_server_push(memc, servers);
    if (rc != MEMCACHED_SUCCESS) {
        printf("Connect error");
    }
    rc = memcached_flush(memc, 0);

    char str_count[8];
    char key[256];
    size_t message_length;
    uint32_t flags;
    int total_count;

    for (int i = 0; i < 10; i++) {
    snprintf(key, sizeof(key), "total");
    while (1) {
        char *message = memcached_get(memc, key, strlen(key), &message_length, &flags, &rc);
        if (message) {
            total_count = atoi(message);
            printf("Message get: %d \n", total_count);
            free(message);
            break;
        }
        else {
            printf("Error total message get\n");
            sleep(1);
        }
    }

            snprintf(key, sizeof(key), "get_total");
            rc = memcached_set(memc, key, strlen(key), "get_total", strlen("get_total"), 0, 0);

            if (rc == MEMCACHED_SUCCESS) {
                printf("Message sends successfully with key %s\n", key);
            }

    int count = 0;
    while (count < total_count) {
        sprintf(str_count, "%d", count);
        snprintf(key, sizeof(key), "input_%s", str_count);

    char *input_message = NULL;
    int int_output_message;
    while (!input_message) {
        input_message = memcached_get(memc, key, strlen(key), &message_length, &flags, &rc);
        if (input_message) {
            int_output_message = atoi(input_message);
            int_output_message++;
            printf("Message get: %s %s\n", input_message, key);

        }
        else {
            //printf("Error message get\n");
        }
    }

    char output_message[20];
    sprintf(output_message, "%d", int_output_message);

    snprintf(key, sizeof(key), "output_%s", str_count);
            rc = memcached_set(memc, key, strlen(key), output_message, strlen(output_message), 0, 0);

            if (rc == MEMCACHED_SUCCESS) {
                printf("Message %s sends successfully\n", output_message);
                free(input_message);
                count++;
            }
        }
        rc = memcached_flush(memc, 0);
    }
}
//Blair z5351042

#include <stdlib.h>
#include <pthread.h>

void *increment_and_sleep(void *arg);

void costly_addition(int num){
    pthread_t threads[num];
    int i = 0;
    while(i < num){
        pthread_create(&threads[i], NULL, increment_and_sleep, NULL);
        i++;
    }
    i = 0;
    while(i < num){
        pthread_join(threads[i], NULL);
    }
}
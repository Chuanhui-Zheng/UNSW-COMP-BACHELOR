#include <pthread.h>
#include "thread_chain.h"

void *my_thread(int data) {
    thread_hello();
    if(data > 0){
        data--;
        pthread_t thread;
        pthread_create(&thread, NULL, my_thread, data);
        pthread_join(thread, NULL);
    }
    
    return NULL;
}

void my_main(void) {
    pthread_t thread_handle;
    pthread_create(&thread_handle, NULL, my_thread,(int)49);

    pthread_join(thread_handle, NULL);
}

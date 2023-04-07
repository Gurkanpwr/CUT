#include <stdio.h>
#include "threadfunctions.h"
#include <unistd.h>
#include "stdlib.h"


#define thread_num 3

extern pthread_mutex_t mutexlck,mutex;
pthread_t threads[thread_num];

int main() {
    int rc;
    rc = pthread_create(&threads[0], NULL, Reader, NULL);
    if (rc) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    rc = pthread_create(&threads[1], NULL, Analyzer, NULL);
    if (rc) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    rc = pthread_create(&threads[2], NULL, Printer, NULL);
    if (rc) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < thread_num ; i++) {
        rc = pthread_join(threads[i], NULL);
        if (rc) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    pthread_mutex_destroy(&mutexlck);
    pthread_mutex_destroy(&mutex);



}

#include <stdio.h>
#include "threadfunctions.h"
#include <unistd.h>
#include "stdlib.h"


#define thread_num 5

extern pthread_mutex_t mutex;
pthread_t threads[thread_num];

int main() {
    int rc;
    if (pthread_mutex_init(&mutex,NULL) !=0){
        perror("Mutex Error");
    }

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

    rc= pthread_create(&threads[3],NULL,Watchdog,NULL);
    if(rc){
        perror("Pthread error for Watchdog");
    }
    rc= pthread_create(&threads[4],NULL, Logger,NULL);
    if(rc){
        perror("Error occured at Logger thread");
    }
    //pause();
    for (int i = 0; i < thread_num ; i++) {
        rc = pthread_join(threads[i], NULL);
        if (rc) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }


    pthread_mutex_destroy(&mutex);
    return 0;
}

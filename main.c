#include <stdio.h>
#include "threadfunctions.h"
#include <unistd.h>
#include "stdlib.h"


#define thread_num 5

extern pthread_mutex_t mutex;
extern pthread_t threads[thread_num];

int main() {
    unit_test();

    int rc;
    remove("CPUlog.txt");

    if (pthread_mutex_init(&mutex,NULL) !=0){
        perror("Mutex Error");
    }

    rc = pthread_create(&threads[0], NULL, Reader, NULL);
    if (rc) {
        perror("Pthread error for Reader thread");
        exit(EXIT_FAILURE);
    }

    rc = pthread_create(&threads[1], NULL, Analyzer, NULL);
    if (rc) {
        perror("Pthread error for Analyzer thread");
        exit(EXIT_FAILURE);
    }

    rc = pthread_create(&threads[2], NULL, Printer, NULL);
    if (rc) {
        perror("Pthread error for Printer thread");
        exit(EXIT_FAILURE);
    }

    rc= pthread_create(&threads[3],NULL,Watchdog,NULL);
    if(rc){
        perror("Pthread error for Watchdog thread");
    }
    rc= pthread_create(&threads[4],NULL, Logger,NULL);
    if(rc){
        perror("Error occured at Logger thread");
    }

    struct sigaction sa;
    sa.sa_handler = sigterm_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

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

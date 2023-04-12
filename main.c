#include <stdio.h>
#include "threadfunctions.h"
#include <unistd.h>
#include "stdlib.h"

extern volatile int state1,state2,state3;

#define thread_num 3

extern pthread_mutex_t mutex;
pthread_t threads[thread_num];

int main() {
    int rc;
    if (pthread_mutex_init(&mutex,NULL) !=0){
        perror("Mutex Error");
    }

    signal(SIGALRM,Watchdog);
    alarm(5);

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

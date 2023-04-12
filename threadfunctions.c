#include "threadfunctions.h"
#include "stdlib.h"
#include "string.h"
#include <errno.h>

int array_comp(long double a[],long double b[],int size);
long double CPU[4];
long double usage;
volatile int Terminate=0;
FILE* fp;
volatile int watch_counter[3]={0,0,0};

pthread_mutex_t mutex;


void* Reader(void* p) {

    while(!Terminate){
        pthread_mutex_lock(&mutex);
        fp=fopen("/proc/stat","r");

        fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&CPU[0],&CPU[1],&CPU[2],&CPU[3]);
        fclose(fp);
        pthread_mutex_unlock(&mutex);
        sleep(1);
        watch_counter[0]++;

    }
    pthread_exit(NULL);
}

void* Analyzer(void* p){
    long double prev_tmp[4]={},tmp[4];
    while(!Terminate) {
        pthread_mutex_lock(&mutex);
        for (int i=0;i<4;i++){
            tmp[i]=CPU[i];
        }
        pthread_mutex_unlock(&mutex);

        if(array_comp(tmp,prev_tmp,4) != 0){
            if (pthread_mutex_trylock(&mutex) == EBUSY) {
                continue; // skip critical section and try again later
            }

            usage = ((tmp[0] + tmp[1] + tmp[2]) - (prev_tmp[0] + prev_tmp[1] + prev_tmp[2])) /
                    ((tmp[0] + tmp[1] + tmp[2] + tmp[3]) - (prev_tmp[0] + prev_tmp[1] + prev_tmp[2] + prev_tmp[3]));
            pthread_mutex_unlock(&mutex);
        }

        for(int i=0;i<4;i++){
            prev_tmp[i]=tmp[i];
        }
        sleep(1);
        watch_counter[1]++;
    }
    pthread_exit(NULL);
}

void* Printer(void* p){
   const int length=100;
    float data;
    int total=100;

    while(!Terminate){

        if (pthread_mutex_trylock(&mutex) == EBUSY) {
            continue; // skip critical section and try again later
        }
        data=(float)usage*100;

        pthread_mutex_unlock(&mutex);

        int fill=(int)(data*length/(float)total);
        int remain=length-fill;
        printf("[");
        if(data<=30){
        for(int i=0;i<fill;i++){
            printf("\x1b[1;32m*\x1b[0m");
        }
        }
        else if(data>30 && data <60){
            for(int i=0;i<fill;i++){
                printf("\x1b[1;33m*\x1b[0m");
            }
        }
        else{
            for(int i=0;i<fill;i++){
                printf("\x1b[1;31m*\x1b[0m");
            }
        }
        for(int j=0;j<remain;j++){
            printf(" ");
        }

        printf("] %3.2f% \r",data);
        fflush(stdout);
        sleep(1);
        watch_counter[2]++;

    }
    pthread_exit(NULL);
}

void* Watchdog(void* p){
    int last_progress[3] = {0, 0, 0};
    int deadlock_occurred = 0;

    while(!Terminate){
        sleep(2);

        deadlock_occurred = 0;
        for (int i = 0; i < 3; i++) {
            if (last_progress[i] == watch_counter[i]) {
                deadlock_occurred = 1;
                break;
            } else {
                last_progress[i] = watch_counter[i];
            }
        }
        if (deadlock_occurred) {
            printf("Deadlock occurred. Attempting to fix.\n");
            // Attempt to resolve the deadlock by unlocking the mutex
            pthread_mutex_unlock(&mutex);
        }
    }

    pthread_exit(NULL);
}

int array_comp(long double* a, long double* b,int size){

    for(int i=0;i<size;i++){
        if(a[i] !=b[i]){
            return 1;

        }
    }
    return 0;
}
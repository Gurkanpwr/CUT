//
// Created by gurkan on 28.03.23.
//
#include "threadfunctions.h"
#include "stdlib.h"
#include "string.h"


int array_comp(long double a[],long double b[],int size);
long double CPU[4];
long double usage;

FILE* fp;

pthread_mutex_t mutex,mutexlck;


void* Reader(void* p) {


    while(1){
        pthread_mutex_lock(&mutexlck);
        fp=fopen("/proc/stat","r");

        fscanf(fp,"%*s %Lf %Lf %Lf %Lf",&CPU[0],&CPU[1],&CPU[2],&CPU[3]);
        fclose(fp);
        pthread_mutex_unlock(&mutexlck);

        sleep(1);

    }
    pthread_exit(NULL);

}
void* Analyzer(void* p){
    long double prev_tmp[4]={},tmp[4];
    for(;;) {


        pthread_mutex_lock(&mutexlck);
        for (int i=0;i<4;i++){
            tmp[i]=CPU[i];
        }
        pthread_mutex_unlock(&mutexlck);

        if(array_comp(tmp,prev_tmp,4) != 0){

            pthread_mutex_lock(&mutex);
            usage = ((tmp[0] + tmp[1] + tmp[2]) - (prev_tmp[0] + prev_tmp[1] + prev_tmp[2])) /
                    ((tmp[0] + tmp[1] + tmp[2] + tmp[3]) - (prev_tmp[0] + prev_tmp[1] + prev_tmp[2] + prev_tmp[3]));
            pthread_mutex_unlock(&mutex);

        }

        for(int i=0;i<4;i++){
            prev_tmp[i]=tmp[i];
        }
        sleep(1);
    }
    pthread_exit(NULL);
}

void* Printer(void* p){
    for(;;){
        sleep(1);

        pthread_mutex_lock(&mutex);
        printf("Usage: %.2Lf\n",100*usage);
        pthread_mutex_unlock(&mutex);

    }
    pthread_exit(NULL);
}
void* Watchdog(void *p){

}

int array_comp(long double a[],long double b[],int size){

    for(int i=0;i<size;i++){
        if(a[i] !=b[i]){
            return 1;

        }
        else{
            return 0;
        }
    }
}
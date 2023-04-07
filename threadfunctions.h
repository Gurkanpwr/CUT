//
// Created by gurkan on 28.03.23.
//
#include "pthread.h"
#include "stdio.h"
#include "unistd.h"


#ifndef CUT_THREADFUNCTIONS_H
#define CUT_THREADFUNCTIONS_H

void* Reader(void *p);
void* Analyzer(void*);
void* Printer(void*);
void* Watchdog(void*);
void* Logger(void*);

#endif //CUT_THREADFUNCTIONS_H

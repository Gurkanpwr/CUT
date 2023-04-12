//
// Created by gurkan on 28.03.23.
//
#include "pthread.h"
#include "stdio.h"
#include "unistd.h"
#include "signal.h"
#include <sys/time.h>
#ifndef CUT_THREADFUNCTIONS_H
#define CUT_THREADFUNCTIONS_H

void* Reader(void* p );
void* Analyzer(void* p);
void* Printer(void* p);
void* Watchdog(void* p);
void* Logger(void*);
void* sigterm_handler(void* );

#endif //CUT_THREADFUNCTIONS_H

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

void* Reader(__attribute__((unused)) void* p );
void* Analyzer(__attribute__((unused)) void* p);
void* Printer(__attribute__((unused)) void* p);
void* Watchdog(__attribute__((unused)) void* p);
void* Logger(__attribute__((unused)) void*);
void sigterm_handler(__attribute__((unused)) int sig);

void unit_test(void);
#endif //CUT_THREADFUNCTIONS_H

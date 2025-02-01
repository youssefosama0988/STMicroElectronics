
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

// Log levels
#define ERROR    1
#define WARNING  2
#define INFO     3
#define DEBUG    4
#define DISABLE  0

// Log macros
#define LOG_ERROR(x)		Logger_output(ERROR , x)
#define LOG_WARNING(x)		Logger_output(WARNING , x)
#define LOG_INFO(x)		Logger_output(INFO , x)
#define LOG_DEBUG(x)		Logger_output(DEBUG , x)


// Global log level flags
extern bool error, warning, info, debug , disable;

// Function declarations
void Logger_output(int mode, const char *message);
void handler(int sig, siginfo_t *info, void *ucontext);

#endif 


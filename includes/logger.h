// MimE Email Server's Logger

#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdarg.h>

void logerr(char *msg, ...) {
    va_list args;
    va_start(args, msg);
    fprintf(stderr, "\033[1;31m");
    vfprintf(stderr, msg, args);
    fprintf(stderr, "\033[0m");
    va_end(args);
}

void logsucc(char *msg, ...) {
    va_list args;
    va_start(args, msg);
    fprintf(stdout, "\033[0;32m");
    vfprintf(stdout, msg, args);
    fprintf(stdout, "\033[0m");
    va_end(args);
}

void loginfo(char *msg, ...) {
    va_list args;
    va_start(args, msg);
    fprintf(stdout, "\033[0;33m");
    vfprintf(stdout, msg, args);
    fprintf(stdout, "\033[0m");
    va_end(args);
}

void logdbg(char *msg, ...) {
    va_list args;
    va_start(args, msg);
    fprintf(stdout, "\033[0;36m");
    vfprintf(stdout, msg, args);
    fprintf(stdout, "\033[0m");
    va_end(args);
}

#endif
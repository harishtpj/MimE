// Imports And Declarations for MimE Email Server

#ifndef DEFS_H
#define DEFS_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#define PORT "4192"
#define BACKLOG 10
#define AUTHOR "M.V.Harish Kumar"
#define MAXSIZE 1024

#define clrbuf(str) (memset(str, 0, MAXSIZE))
#define is_substr(mainstr, str) (strcasestr(mainstr, str) != NULL)

#endif
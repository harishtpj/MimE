// Imports And Global Declarations for MimE Email Server

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
#define MAX_DATA_SIZE 250000 //250 MB
#define MAX_USR_LEN 64
#define MAX_DOM_LEN 255
#define MAX_EMAIL_LEN (MAX_USR_LEN + 1 + MAX_DOM_LEN)
#define USERLST "mimeusrs"

#define clrbuf(str) (memset(str, 0, MAXSIZE))
#define is_substr(mainstr, str) (strcasestr(mainstr, str) != NULL)

typedef enum {
    C_WELCOME = 220,
    C_CLOSE = 221,
    C_OK = 250,
    C_SDATA = 354,
    C_SYNERR = 501,
    C_NOTIMPL = 502,
    C_BADSEQ = 503,
    C_NOUSR = 550,
    C_NLOCUSR = 551
} code_resp;

typedef enum { CLNT_HELO, CLNT_DATA, CLNT_DATA_END } clnt_sts;

typedef struct {
    char faddr[MAX_EMAIL_LEN];
    char tusr[MAX_USR_LEN];
    char tdomain[MAX_DOM_LEN];
    char msg[MAX_DATA_SIZE];
} mail;

bool isdbg = false;

#endif
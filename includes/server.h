// MimE Server Related Code

#ifndef SERVER_H
#define SERVER_H

#include <defs.h>
#include <helpers.h>
#include <logger.h>

int create_server() {
    int servfd, rv;
    int yes = 1;
    struct addrinfo hints, *servinfo, *p;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) {
        logerr("getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }

    for (p = servinfo; p != NULL; p = p->ai_next) {
        servfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (servfd == -1) {
            perror("mimeSMTP: socket");
            continue;
        }

        check_error(setsockopt(servfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)), "setsockopt");

        if (bind(servfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(servfd);
            perror("mimeSMTP: bind");
            continue;
        }

        break;
    }

    freeaddrinfo(servinfo);

    if (p == NULL) {
        logerr("mimeSMTP: failed to bind\n");
        exit(1);
    }

    return servfd;
}

void get_response(char *buf, int status) {
    clrbuf(buf);
    switch (status) {
    case C_WELCOME:
        strcpy(buf, "220 Welcome to mimeSMTP\r\n");
        break;
    case C_CLOSE:
        strcpy(buf, "221 Service closing transmission channel\r\n");
        break;
    case C_OK:
        strcpy(buf, "250 OK\r\n");
        break;
    case C_SDATA:
        strcpy(buf, "354 Start mail input; end with <CRLF>.<CRLF>\r\n");
        break;
    case C_SYNERR:
        strcpy(buf, "501 Syntax error in parameters or arguments\r\n");
        break;
    case C_NOTIMPL:
        strcpy(buf, "502 Command not implemented\r\n");
        break;
    case C_BADSEQ:
        strcpy(buf, "503 Bad sequence of commands\r\n");
        break;
    case C_NOUSR:
        strcpy(buf, "550 No such user\r\n");
        break;
    case C_NLOCUSR:
        strcpy(buf, "551 User not local. Can't forward the mail\r\n");
        break;
    default:
        sprintf(buf, "%d No description", status);
        break;
    }
}

#endif
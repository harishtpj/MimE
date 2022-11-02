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

#endif
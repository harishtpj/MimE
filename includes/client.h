// MimE Client Related Code

#ifndef CLIENT_H
#define CLIENT_H

#include <logger.h>
#include <defs.h>
#include <helpers.h>

int accept_client(int servfd, char *c_daddr) {
    int clntfd;
    socklen_t sin_size;
    struct sockaddr_storage clntaddr;
    bool got_client = false;
    char c_addr[INET6_ADDRSTRLEN];

    while (!got_client) {
        sin_size = sizeof clntaddr;
        clntfd = accept(servfd, (struct sockaddr *)&clntaddr, &sin_size);
        if (clntfd == -1)
            perror("accept");
        else
            got_client = true;
    }

    inet_ntop(clntaddr.ss_family, 
                  get_addr((struct sockaddr *)&clntaddr),
                  c_addr, sizeof c_addr);
    strcpy(c_daddr, c_addr);
    
    return clntfd;
}

#endif
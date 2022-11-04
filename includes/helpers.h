// MimE Server Helpers

#ifndef HELPERS_H
#define HELPERS_H

#include <defs.h>
#include <logger.h>

void *get_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void check_error(int val, char *fn_name) {
    if (val == -1) {
        perror(fn_name);
        exit(1);
    }
}

void sig_handler(int s) {
    int s_errno = errno;
    while (waitpid(-1, NULL, WNOHANG) > 0);
    errno = s_errno;
}

void handle_signal() {
    struct sigaction sa;

    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    check_error(sigaction(SIGCHLD, &sa, NULL), "sigaction");
}

void get_emladdr(char *buf, char *faddr) {
    int alen;
    char *start, *end;

    start = strchr(buf, '<');
    end = strchr(buf, '>');
    start++;
    alen = end - start;

    strncpy(faddr, start, alen);
}

void get_domain(char *email, char *dom) {
    char *domain;
    domain = strchr(email, '@');
    domain += 1;
    strcpy(dom, domain);
}

void get_user(char *email, char *user) {
    char *domain;
    domain = strchr(email, '@');
    domain += 1;
    strncpy(user, email, strlen(email)-strlen(domain)-1);
}

#endif
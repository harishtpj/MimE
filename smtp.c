// The MimE - Minimal Email Server's SMTP Server

#include <defs.h>
#include <server.h>
#include <client.h>
#include <helpers.h>
#include <logger.h>

int main(int argc, char *argv[]) {
    int servfd, clntfd, nb;
    char c_addr[INET6_ADDRSTRLEN], buf[MAXSIZE];


    servfd = create_server();
    check_error(listen(servfd, BACKLOG), "listen");
    handle_signal();
    
    loginfo("Welcome to MimE SMTP: Minimal Email Server(SMTP)\n");
    loginfo("Written by %s\n\n", AUTHOR);
    logsucc("Server Started running at 0.0.0.0:%s\n", PORT);
    logsucc("mimeSMTP: waiting for connections...\n");

    clntfd = accept_client(servfd, c_addr);
    logsucc("mimeSMTP: got connection from %s\n", c_addr);

    loginfo("----SMTP Server Communication Data----\n");

    clrbuf(buf);
    strcpy(buf, "220 OK, Welcome to MimE SMTP Server\r\n");
    logdbg("mimeSMTP: %s", buf);
    check_error(send(clntfd, buf, strlen(buf), 0), "send");

    do {
        clrbuf(buf);
        nb = recv(clntfd, buf, MAXSIZE-1, 0);
        if (nb < 0) {
            perror("recv");
            break;
        } else {
            buf[nb] = '\0';
            if (is_substr(buf, "EHLO")) {
                logdbg("%s: %s", c_addr, buf);
                clrbuf(buf);
                strcpy(buf, "250 OK MimE SMTP Server\r\n");
                logdbg("mimeSMTP: %s", buf);
                check_error(send(clntfd, buf, strlen(buf), 0), "send");
            } else if (is_substr(buf, "QUIT")) {
                break;
            } else {
                logdbg("%s: %s", c_addr, buf);
                clrbuf(buf);
                strcpy(buf, "502 Command not implemented\r\n");
                logdbg("mimeSMTP: %s", buf);
                check_error(send(clntfd, buf, strlen(buf), 0), "send");
            }
        }
    } while(strcmp(buf, "QUIT") != 0);

    logdbg("%s: %s", c_addr, buf);
    clrbuf(buf);
    strcpy(buf, "221 Bye\r\n");
    logdbg("mimeSMTP: %s", buf);
    check_error(send(clntfd, buf, strlen(buf), 0), "send");
    loginfo("----End of SMTP Server Communication Data----\n");
    logsucc("SMTP Server Closed Sucessfully\n");
}
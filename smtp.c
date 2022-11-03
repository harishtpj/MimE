// The MimE - Minimal Email Server's SMTP Server

#include <defs.h>
#include <server.h>
#include <client.h>
#include <helpers.h>
#include <logger.h>

int main(int argc, char *argv[]) {
    int servfd, clntfd, nb, clnt_sts;
    char c_addr[INET6_ADDRSTRLEN], buf[MAXSIZE];

    isdbg = true;

    servfd = create_server();
    check_error(listen(servfd, BACKLOG), "listen");
    handle_signal();
    
    loginfo("Welcome to MimE SMTP: Minimal Email Server(SMTP)\n");
    loginfo("Written by %s\n\n", AUTHOR);
    logsucc("Server Started running at 0.0.0.0:%s\n", PORT);
    logsucc("mimeSMTP: waiting for connections...\n");


    while (true) {
        clntfd = accept_client(servfd, c_addr);
        logsucc("mimeSMTP: got connection from %s\n", c_addr);

        logdbg("----SMTP Server Communication Data----\n");

        get_response(buf, C_WELCOME);
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
                logdbg("%s: %s", c_addr, buf);
                if (is_substr(buf, "HELO")) {
                    get_response(buf, C_OK);
                    check_error(send(clntfd, buf, strlen(buf), 0), "send");
                } /*else if (is_substr(buf, "MAIL FROM")) {
                    
                }*/ else if (is_substr(buf, "QUIT")) {
                    break;
                } else {
                    get_response(buf, C_NOTIMPL);
                    check_error(send(clntfd, buf, strlen(buf), 0), "send");
                }
                logdbg("mimeSMTP: %s", buf);
            }
        } while(strcmp(buf, "QUIT") != 0);

        logdbg("%s: %s", c_addr, buf);
        get_response(buf, C_CLOSE);
        logdbg("mimeSMTP: %s", buf);
        check_error(send(clntfd, buf, strlen(buf), 0), "send");

        logdbg("----End of SMTP Server Communication Data----\n");
        loginfo("Client %s got disconnected\n", c_addr);
    }
}
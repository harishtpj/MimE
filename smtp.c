// The MimE - Minimal Email Server's SMTP Server

#include <defs.h>
#include <server.h>
#include <client.h>
#include <helpers.h>
#include <logger.h>
#include <userdb.h>

int main(int argc, char *argv[]) {
    int servfd, clntfd, nb;
    char c_addr[INET6_ADDRSTRLEN], buf[MAXSIZE];
    clnt_sts clsts;
    mail mail_data;
    int ulen = get_usrcnt();
    userinfo *users = ld_usrdata();

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
                if (is_substr(buf, "EHLO")) {
                    clsts = CLNT_HELO;
                    get_response(buf, C_OK);

                } else if (is_substr(buf, "MAIL FROM")) {
                    if (clsts != CLNT_HELO) {
                        get_response(buf, C_BADSEQ);
                    } else {
                        get_emladdr(buf, mail_data.faddr);
                        logdbg("From address: %s\n", mail_data.faddr);
                        get_response(buf, C_OK);
                    }
                
                } else if (is_substr(buf, "RCPT TO")) {
                    if (clsts != CLNT_HELO) {
                        get_response(buf, C_BADSEQ);
                    } else {
                        char taddr[MAX_EMAIL_LEN];
                        get_emladdr(buf, taddr);
                        get_domain(taddr, mail_data.tdomain);
                        get_user(taddr, mail_data.tusr);

                        if (!has_usr(users, ulen, mail_data.tusr)) {
                            get_response(buf, C_NLOCUSR);
                        } else {
                            logdbg("To: %s Domain: %s\n", mail_data.tusr, mail_data.tdomain);
                            get_response(buf, C_OK);
                        }
                    }
                
                } else if (is_substr(buf, "DATA")) {
                    if (clsts != CLNT_DATA) {
                        clsts = CLNT_DATA;
                        get_response(buf, C_SDATA);
                        check_error(send(clntfd, buf, strlen(buf), 0), "send");
                        logdbg("mimeSMTP: %s", buf);
                    }
                    clrbuf(buf);
                    nb = recv(clntfd, buf, MAXSIZE-1, 0);
                    if (nb < 0) {
                        perror("recv");
                        break;
                    } else {
                        buf[nb] = '\0';
                        logdbg("%s: %s", c_addr, buf);
                        if (is_substr(buf, "\r\n.\r\n")) {
                            strncpy(mail_data.msg, buf, strlen(buf)-5);
                            logdbg("mimeSMTP: Data Over. Got the Following Data\n");
                            logdbg("%s\n", mail_data.msg);
                            clsts = CLNT_DATA_END;
                            strcpy(buf, "250 Message Accepted for delivery\r\n");
                        }
                    }
                } else if (is_substr(buf, "RSET")) {
                    memset(&mail_data, 0, sizeof(mail));
                    get_response(buf, C_OK);

                } else if (is_substr(buf, "QUIT")) {
                    break;

                } else {
                    get_response(buf, C_NOTIMPL);
                }
                check_error(send(clntfd, buf, strlen(buf), 0), "send");
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
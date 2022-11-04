#ifndef USERDB_H
#define USERDB_H

#include <defs.h>
#include <logger.h>

typedef struct {
    char name[128];
    char u_name[MAX_USR_LEN];
} userinfo; 

int get_usrcnt() {
    FILE *fp = fopen(USERLST, "r");
    if (fp == NULL) {
        logerr("Error in opening User List");
        return -1;
    }
    int usrcnt;
    fscanf(fp, "%d\n", &usrcnt);
    fclose(fp);
    return usrcnt;
}

userinfo *ld_usrdata() {
    FILE *fp = fopen(USERLST, "r");
    if (fp == NULL) {
        logerr("Error in opening User List");
        return NULL;
    }
    int usrcnt;
    fscanf(fp, "%d\n", &usrcnt);
    userinfo *users = malloc(usrcnt * sizeof(userinfo));

    for (int i = 0; i < usrcnt; i++) {
        fscanf(fp, "%[^,],%s\n", users[i].name, users[i].u_name);
    }
    fclose(fp);
    return users;
}

void pp_usrdata(userinfo *users, int ulen) {
    for (int i = 0; i < ulen; i++){
        loginfo("User Details\nName: %s\nUsername: %s\n\n", users[i].name, users[i].u_name);
    }
}

bool has_usr(userinfo *users, int ulen, char *uname) {
    for (int i = 0; i < ulen; i++) {
        if (strcmp(users[i].u_name, uname) == 0) {
            return true;
        }
    }
    return false;
}

#endif
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <grp.h>
#include <stdlib.h>

char* get_user_groups(uid_t user_uid);

void print_user_info(bool show_host, bool show_groups) {
    struct utmpx *entry;
    struct passwd *pwd;

    entry = getutxent();
    while (entry != NULL) {
        if (entry->ut_type == USER_PROCESS) {
            pwd = getpwnam(entry->ut_user);

            if (show_host && show_groups) {
                char *groups = get_user_groups(pwd->pw_uid);

                printf("%-10s (%s) [%s]\n", entry->ut_user, entry->ut_host, groups);
                
                free(groups);
            } else if (show_host) {
                printf("%-10s (%s)\n", entry->ut_user, entry->ut_host);
            } else if (show_groups) {
                char *groups = get_user_groups(pwd->pw_uid);
                
                printf("%-10s [%s]\n", entry->ut_user, groups);
                
                free(groups);
            } else {
                printf("%-10s\n", entry->ut_user);
            }
        }
        entry = getutxent();
    }
}

int main(int argc, char *argv[]) {
    bool show_host = false;
    bool show_groups = false;
    int opt;

    while ((opt = getopt(argc, argv, "hg")) != -1) {
        switch (opt) {
            case 'h':
                show_host = true;
                break;
            case 'g':
                show_groups = true;
                break;
            default:
                return 1;
        }
    }

    print_user_info(show_host, show_groups);

    return 0;
}

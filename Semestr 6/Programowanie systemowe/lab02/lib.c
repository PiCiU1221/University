#include <stdio.h>
#include <utmpx.h>
#include <pwd.h>
#include <sys/types.h>

void print_user_info() {
    struct utmpx *entry;
    struct passwd *pwd;

    entry = getutxent();
    while (entry != NULL) {
        if (entry->ut_type == USER_PROCESS) {
            pwd = getpwnam(entry->ut_user);

            printf("%-6d %-10s %-7s %-15s\n",
                   pwd->pw_uid,
                   entry->ut_user,
                   entry->ut_line,
                   entry->ut_host);
        }
        entry = getutxent();
    }
}

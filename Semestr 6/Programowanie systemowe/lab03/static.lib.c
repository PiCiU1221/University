#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <pwd.h>
#include <sys/types.h>
#include <string.h>

char* get_user_groups(uid_t user_uid) {
    struct passwd *pwd = getpwuid(user_uid);

    int ngroups = 0;
    gid_t *groups;
    
    getgrouplist(pwd->pw_name, pwd->pw_gid, NULL, &ngroups);

    groups = malloc(ngroups * sizeof(gid_t));
    
    getgrouplist(pwd->pw_name, pwd->pw_gid, groups, &ngroups);

    // needed space calculations needed for the result string
    // space for null terminator
    size_t result_size = 1;
    for (int i = 0; i < ngroups; i++) {
        // get group info
        struct group *grp = getgrgid(groups[i]);
        // add length of the group name for to the result string size
        result_size += strlen(grp->gr_name);
    }
    // add space for ", " after every group name (excluding the last one)
    result_size += (ngroups - 1) * 2;

    char *result = malloc(result_size);
    // initializing the result string as empty string to avoid garbage data
    result[0] = '\0';

    for (int i = 0; i < ngroups; i++) {
        struct group *grp = getgrgid(groups[i]);
        
        strcat(result, grp->gr_name);
        if (i < ngroups - 1) {
            strcat(result, ", ");
        }
    }

    return result;
}

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "../include/util.h"

bool update_workingdir(char* dir) {
    char buff[200];
    if (!getcwd(buff, sizeof(buff))) {
        return false;
    }
    char* abc = dir + 1;
    strcat(buff, abc);
    buff[strlen(buff) - 7] = '\0';
    printf("%s\n", buff);
    if (chdir(buff) != 0) {
        return false;
    }
    return true;
}
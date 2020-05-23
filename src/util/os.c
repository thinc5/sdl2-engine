#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../../include/debug.h"
#include "../../include/util/os.h"

#ifdef UNIX
#include <libgen.h>

/**
 * Change working directory to the same one as the binary on unix systems with access to /proc.
 */
void set_dir() {
    // Read exe complete path.
    char buff[1000];
    memset(buff, '\0', 1000);
    readlink("/proc/self/exe", buff, 90);
    // Find and remove the executable name.
    char* executableName = basename(buff);
    int exeLen = strlen(executableName);
    memset(buff + strlen(buff) - exeLen, '\0', exeLen);
    // Change directory to the executable's directory.
    INFO_LOG("%s\n", buff);
    chdir(buff);
}

#endif

#ifdef WIN
#include <windows.h>
#include <Shlwapi.h>

/**
 * Change working directory to the same one as the binary on windows.
 */
void set_dir() {
    // Read exe complete path.
    char buff[1000];
    memset(buff, '\0', 1000);
    GetModuleFileNameA(NULL, buff, 1000);
    // Find and remove the executable name.
    PathRemoveFileSpecA(buff);
    // Change directory to the executable's directory.
    INFO_LOG("%s\n", buff);
    chdir(buff);
}

#endif

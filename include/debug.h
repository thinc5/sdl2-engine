#ifndef DEBUG_H
#define DEBUG_H

/* This header file contains macros that allow for different build behaviour
   between debug and release builds. */

/**
 * If we are building a debug build we want DEBUG_LOG to alias to printf,
 * else we want it to do nothing and get removed by preprocessor.
 */
#ifdef DEBUG

#define DEBUG_LOG(...) fprintf(stdout, "DEBUG: "__VA_ARGS__)

#else

#define DEBUG_LOG(...)

#endif

#ifdef RELEASE

// We have no logging in release builds.
#define INFO_LOG(...)
#define ERROR_LOG(...)

#else

#define INFO_LOG(...) fprintf(stdout, "INFO: "__VA_ARGS__)
#define ERROR_LOG(...) fprintf(stderr, "ERROR: "__VA_ARGS__)

#endif

#endif

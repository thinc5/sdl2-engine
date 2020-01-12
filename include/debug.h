#ifndef DEBUG_H
#define DEBUG_H

/* This header file contains macros that allow for different build behaviour
   between debug and release builds. */

/**
 * If we are building a debug build we want DEBUG_PRINT to alias to printf,
 * else we want it to do nothing and get removed by preprocessor.
 */
#ifdef DEBUG

#define INFO_LOG(...) fprintf(stdout, "INFO: "__VA_ARGS__)
#define DEBUG_LOG(...) fprintf(stdout, "DEBUG: "__VA_ARGS__)
#define ERROR_LOG(...) fprintf(stderr, "ERROR: "__VA_ARGS__)

#else

#define INFO_LOG(...)
#define DEBUG_LOG(...)
#define ERROR_LOG(...)

#endif

#endif

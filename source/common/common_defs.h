#ifndef COMMONDEFS
#define COMMONDEFS

#if defined(DEBUG)
#define DEBUG_OUTPUT(format, ...) printf(format, ##__VA_ARGS__)
#else
#define DEBUG_OUTPUT(format, ...) (0)
#endif

#endif
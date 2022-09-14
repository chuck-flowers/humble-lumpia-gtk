#ifndef __LOGGING_H
#define __LOGGING_H

#include <stdio.h>

#define LOG_LEVEL_ERROR
#define LOG_LEVEL_WARN
#define LOG_LEVEL_INFO
// #define LOG_LEVEL_TRACE

#ifdef LOG_LEVEL_ERROR
#define LOG_ERR(...) LOG(__VA_ARGS__)
#else
#define LOG_ERR(...)
#endif

#ifdef LOG_LEVEL_WARN
#define LOG_WARN(...) LOG(__VA_ARGS__)
#else
#define LOG_WARN(...)
#endif

#ifdef LOG_LEVEL_INFO
#define LOG_INFO(...) LOG(__VA_ARGS__)
#else
#define LOG_INFO(...)
#endif

#ifdef LOG_LEVEL_TRACE
#define LOG_TRACE(...) LOG(__VA_ARGS__)
#else
#define LOG_TRACE(...)
#endif

#define LOG(...) fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")

#endif


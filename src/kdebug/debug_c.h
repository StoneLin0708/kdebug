#pragma once

#include <stdio.h>
#include <errno.h>

#ifdef DEBUG_MESSAGE
#define LOG(msg, ...) fprintf(stdout, "LOG: "msg"\n", ##__VA_ARGS__)
#define ERROR(msg) fprintf(stderr, "ERROR: %s, code: %d\n", msg, errno)
#else
#define LOG(msg, ...)
#define ERROR(msg)
#endif

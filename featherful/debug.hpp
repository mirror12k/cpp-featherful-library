
#pragma once

#include <cstdio>

#ifdef ENABLE_DEBUG
#define DEBUG(X, ...) do { fprintf(stderr, "DEBUG at %s:%d : " X, __FILE__, __LINE__, ##__VA_ARGS__); } while (0)
#else
#define DEBUG(X, ...)
#endif




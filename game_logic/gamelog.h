#pragma once
#ifdef DEBUG
#include <stdio.h>
#define log(...) \
    fprintf(stderr, __VA_ARGS__);
#else
#define log(message)
#endif

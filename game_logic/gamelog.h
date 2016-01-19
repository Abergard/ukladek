#pragma once
#ifdef DEBUG
#include <stdio.h>
#define log(...) \
    printf( __VA_ARGS__);
#else
#define log(message)
#endif

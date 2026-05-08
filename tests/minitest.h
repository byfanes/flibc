#ifndef MINITEST_H
#define MINITEST_H

#include "stdlib.h"

#define TEST_START(s)
#define TEST_PASS()

#define ASSERT(cond)  \
do {             \
    if(!(cond)) { \
        exit(1); \
    }            \
} while(0);

#define ASSERT_EQ(a, b) \
do {             \
    if(a != b) { \
        exit(1); \
    }            \
} while(0);

#define ASSERT_OK(a) \
do {             \
    if(a != fce_success) { \
        exit(1); \
    }            \
} while(0);

#endif

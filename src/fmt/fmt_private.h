#ifndef __FLIBC_FMT_PRIVATE_H__
#define __FLIBC_FMT_PRIVATE_H__

#include "fmt.h"
#include "io.h"

struct fmt_fp_parts_s {
    u64 mantissa;
    s32 exponent;
};

typedef struct fmt_fp_parts_s fmt_fp_parts_t;

#endif /* __FLIBC_FMT_PRIVATE_H__ */

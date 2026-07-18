#ifndef __FLIBC_TIME_H__
#define __FLIBC_TIME_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"
#include "error.h"
#include "os.h"

typedef struct time_s time_t;

error_t time_now(time_t* out);
error_t time_sleep_ms(u64 ms);
u64 time_diff_ms(time_t a, time_t b);
u64 time_diff_sec(time_t a, time_t b);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_TIME_H__ */

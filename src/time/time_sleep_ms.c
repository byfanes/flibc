#include "time_private.h"

error_t time_sleep_ms
(u64 ms)
{
    /* This is just a wrapper function */
    return __os_time_sleep_ms(ms);
}

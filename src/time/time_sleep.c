#include "time_private.h"

fc_error_t time_sleep
(u64 ms)
{
    /* Init variables */
    ssize_t ret = 0;
    time_t time = {0};

    /* Set time */
    time.sec  = ms / 1000;
    time.nsec = ms % 1000;

    /* Call and check syscall */
    ret = syscall_2(syscall_nanosleep, &time, nullptr);
    if(ret != 0) { return fce_time_error; }

    return fce_success;
}

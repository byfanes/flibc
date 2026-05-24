#include "time_private.h"

error_t time_sleep
(u64 ms)
{
    /* Init variables */
    time_t time = {0};

    /* Set time */
    time.sec  = ms / 1000;
    time.nsec = ms % 1000;

    /* Call and check syscall */
    if(0 != syscall_2_linux(syscall_nanosleep, (ssize_t)&time, (ssize_t)nullptr))
    { return time_error; }

    return success;
}

#include "time_private.h"

error_t time_now
(time_t* out)
{
    /* Init variables and check out */
    ssize_t ret = 0;
    if(!out) { return null_pointer; }

    /* Call gettime and check result */
    ret = syscall_2(syscall_gettime, CLOCK_MONOTONIC, out);
    if(ret == -1) { return time_error; }

    return success;
}

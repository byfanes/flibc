#include "time_private.h"

error_t time_now
(time_t* out)
{
    /* Init variables and check out */
    if(!out) { return null_pointer; }

    /* Call gettime and check result */
    if(-1 == syscall_2_linux(syscall_gettime, CLOCK_MONOTONIC, (ssz)out))
    { return time_error; }

    return success;
}

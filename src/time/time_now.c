#include "time_private.h"

error_t time_now
(time_t* out)
{
    return
        /* Check new variables */
        (!out) ? null_pointer :
        /* Call gettime and check result */
        (0 > syscall_2_linux(syscall_gettime, CLOCK_MONOTONIC, (ssz)out))
            ? time_error : success;
}

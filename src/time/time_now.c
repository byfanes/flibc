#include "time_private.h"

error_t time_now
(time_t* out)
{
    /* Check the pointer is valid and ask os layer for the time */
    return (!out) ? null_pointer : __os_time_now((void *)out);
}

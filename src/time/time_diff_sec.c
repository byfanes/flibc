#include "time_private.h"

u64 time_diff_sec
(time_t a, time_t b)
{
    return ((b.sec - a.sec) + (b.nsec - a.nsec) / (u64)1e9);
}

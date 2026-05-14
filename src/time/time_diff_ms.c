#include "time_private.h"

u64 time_diff_ms
(time_t a, time_t b)
{
    return ((b.sec - a.sec) * 1000 + (b.nsec - a.nsec) / 1000);
}

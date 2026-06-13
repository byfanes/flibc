#include "threads_private.h"

void thread_yield
(void)
{
    /* This function is just a syscall wrapper */
    syscall_0_linux(syscall_sched_yield);
}

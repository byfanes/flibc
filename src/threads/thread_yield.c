#include "threads_private.h"

void thread_yield
(void)
{
    /* This function is just a syscall wrapper */
    __os_thread_yield();
}

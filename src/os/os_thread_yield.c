#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_thread_yield
(void)
{
    syscall_0_linux(syscall_sched_yield);
    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */

#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_thread_cond_signal
(volatile u32 *addr)
{
    syscall_6_linux(syscall_futex, (ssz)addr, FUTEX_WAKE, 1, 0, 0, 0);
    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */

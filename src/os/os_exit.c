#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

noreturn __os_exit
(ssz code)
{
    syscall_1_linux(syscall_exit, code);
    __unreachable();
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */

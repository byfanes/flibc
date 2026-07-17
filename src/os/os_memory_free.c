#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_memory_free
(void *set, usz free_size)
{
    /* Init variables */
    ssz ret = 0;
    void *ptr = *(void **)set;

    /* Set users' pointer to null after copying it */
    *(void **)set = nullptr;

    ret = syscall_2_linux(syscall_munmap, (ssz)ptr, (ssz)free_size);
    return (ret == 0) ? success : __os_error_map(ret);
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */

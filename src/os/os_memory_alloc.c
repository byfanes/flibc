#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_memory_alloc
(void *set, usz alloc_size)
{
    /* Init variables */
    ssz ret = 0;
    error_t res = success;

    /* Ask kernel for new memory */
    ret = syscall_6_linux(syscall_mmap, 0, (ssz)alloc_size,
        (PROT_READ|PROT_WRITE), (MAP_PRIVATE|MAP_ANONYMOUS), (ssz)(-1), 0);

    /* If its in the error range zero the users' pointer and return error */
    if(0 > ret && ret > -MAX_ERRNO) {
        *(void **)set = nullptr;
        res = __os_error_map(ret);
        return (res == unknown_error) ? memory_error : res;
    }

    /* If its valid assign it to users' pointer and return success */
    *(void **)set = (void *)(uintptr_t)ret;
    return res;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */

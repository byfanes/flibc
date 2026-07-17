#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_path_exists
(const void *path, bool *out)
{
    /* Set default values */
    *out = false;
    
    /* Ask kernel if the path is reachable if not
     * it will return an error code so we treat as
     * the path does not exists
     */
    *out = (0 == syscall_2_linux(syscall_access, (ssz)path, F_OK));
    
    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */
        

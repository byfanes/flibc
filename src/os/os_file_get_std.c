#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_file_get_std
(os_fid_t *set, os_file_std_type_t type)
{
    switch(type) {
    default: return invalid_argument;
    case os_file_stdin: *set = UNIX_STDIN; return success;
    case os_file_stdout: *set = UNIX_STDOUT; return success;
    case os_file_stderr: *set = UNIX_STDERR; return success;
    }
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */

#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

error_t __os_error_map
(ssz code)
{
    switch(-code) {
        default:
            return unknown_error;

        case EOVERFLOW:
            return overflow_error;
            
        case EBADF:
        case ESPIPE:
        case EISDIR:
        case EINVAL:
            return invalid_argument;

        case ENOMEM:
            return exceeding_memory_allocation;

        case EINTR:
            return interrupted;

        case EPERM:
        case EACCES:
            return not_permitted;

        case EFAULT:
            return invalid_pointer;

        case ELOOP:
        case ENFILE:
        case ENOSPC:
        case EDQUOT:
        case EFBIG:
        case EROFS:
        case EBUSY:
            return fs_error;

        case EPIPE:
            return connection_closed;

        case EIO:
            return io_error;

        case EAGAIN:
            return io_partial;

        case ENXIO:
        case ENOENT:
        case ENOTDIR:
            return does_not_exist;

        case ENAMETOOLONG:
            return out_of_bounds;

        case EMFILE:
            return process_error;

    }
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */

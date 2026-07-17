#include "socket_private.h"

error_t socket_close
(socket_t* sock)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        /* Check the pointer and pass it to os layer */
        (res = (sock) ? success : null_pointer) ||
        (res = __os_socket_close(&sock->fd))
    ), (void)( /* Cleanup it safe to use nullpointer */
        mem_zeroed(sock)
    ), res);
}

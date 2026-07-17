#include "socket_private.h"

error_t __socket_write
(socket_t* sock, void* buf, usz el_size)
{
    /* Init variables */
    sl_u8_t* sl = buf;
    error_t res = success;

    return ((void)(
        /* Check user inputs and pass the paramters to os layer */
        (res = (sl && sock && sl->items) ? success : null_pointer) ||
        (res = (el_size) ? success : elsize_zero) ||
        (res = __os_socket_write(sock->fd, sl->items, sl->count * el_size))
    ), res);
}

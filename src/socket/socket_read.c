#include "socket_private.h"

error_t __socket_read
(socket_t* sock, void* buf, usz el_size, usz* read_count)
{
    /* Init variables */
    usz tmp = 0;
    sl_u8_t* sl = buf;
    error_t res = success;

    return ((void)(
        /* Check user inputs and pass parameters to os layer */
        (res = (sl && sock && sl->items) ? success : null_pointer) ||
        (res = (el_size) ? success : elsize_zero) ||
        (res = __os_socket_read(sock->fd, sl->items,
            sl->count * el_size, (read_count) ? read_count : &tmp))
    ), res);
}

#include "socket_private.h"

error_t socket_accept
(socket_t* sock, socket_t* out)
{
    return (!sock || !out) ? null_pointer
        : __os_socket_accept(sock->fd, &out->fd, (void *)&out->addr);
}

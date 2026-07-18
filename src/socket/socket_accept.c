#include "socket_private.h"

error_t socket_accept
(socket_t* sock, socket_t* out)
{
    return (!sock || !out) ? null_pointer
        : __os_socket_accept(sock->sid, &out->sid, &out->addr);
}

#include "socket_private.h"

error_t socket_bind
(socket_t* sock)
{
    return (!sock) ? null_pointer : __os_socket_bind(sock->sid, &sock->addr);
}

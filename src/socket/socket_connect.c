#include "socket_private.h"

error_t socket_connect
(socket_t* sock)
{
    return (!sock) ? null_pointer : __os_socket_connect(sock->sid, &sock->addr);
}


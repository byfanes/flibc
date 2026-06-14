#include "socket_private.h"

error_t socket_connect
(socket_t* sock)
{
    if(!sock) { return null_pointer; }

    if(-1 == syscall_3_linux(syscall_connect, sock->fd,
        (ssz)&sock->addr, sizeof(sock->addr)))
    { return socket_error; }
    
    return success;
}

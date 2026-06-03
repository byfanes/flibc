#include "socket_private.h"

error_t socket_bind
(socket_t* sock)
{
    if(!sock) { return null_pointer; }
        
    if(-1 == syscall_3_linux(syscall_bind, sock->fd,
        (ssize_t)&sock->addr, sizeof(sock->addr)))
    { return socket_error; }
    
    return success;
}

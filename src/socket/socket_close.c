#include "socket_private.h"

error_t socket_close
(socket_t* sock)
{
    usize_t i = 0;

    if(!sock) { return null_pointer; }
    
    if(0 != syscall_1_linux(syscall_close, sock->fd))
    { return socket_error; }

    sock->fd = 0;
    sock->addr.family = 0;
    for(i = 0; i < sizeof(sock->addr.data); ++i)
    { sock->addr.data[i] = 0; }
    
    return success;
}

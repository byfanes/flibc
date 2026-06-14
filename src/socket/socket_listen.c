#include "socket_private.h"

error_t socket_listen
(socket_t* sock)
{
    ssz ret = 0;

    if(!sock) { return null_pointer; }
    
    ret = syscall_2_linux(syscall_listen, sock->fd, 128);
    if(ret == -1) { return socket_error; }

    return success;
}

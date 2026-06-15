#include "socket_private.h"

error_t socket_accept
(socket_t* sock, socket_t* out)
{
    ssz ret = 0;
    ssz len = sizeof(out->addr);

    if(!sock || !out) { return null_pointer; }
    
    ret = syscall_3_linux(syscall_accept, sock->fd, (ssz)&out->addr, (ssz)&len);
    if(ret < 0) { return socket_error; }
    out->fd = ret;

    return success;
}

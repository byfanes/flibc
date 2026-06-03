#include "socket_private.h"

error_t socket_accept
(socket_t* sock, socket_t* out)
{
    ssize_t ret = 0;
    ssize_t len = sizeof(out->addr);

    if(!sock || !out) { return null_pointer; }
    
    ret = syscall_3_linux(syscall_accept, sock->fd, (ssize_t)&out->addr, &len);
    if(ret < 0) { return socket_error; }
    out->fd = ret;

    return success;
}

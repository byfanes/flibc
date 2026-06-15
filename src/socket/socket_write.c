#include "socket_private.h"

error_t __socket_write
(socket_t* sock, void* buf, usz el_size)
{
    ssz ret = 0;
    sl_u8_t* sl = buf;
    
    if(!sl || !sock || !sl->items) { return null_pointer; }
    if(!el_size) { return elsize_zero; }
    
    ret = syscall_3_linux(syscall_write, sock->fd, (ssz)sl->items, (ssz)(sl->count * el_size));
    if(ret < 0) { return io_error; }
    if(ret == 0) { return connection_closed; }
    return success;
}

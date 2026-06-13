#include "socket_private.h"

error_t __socket_read
(socket_t* sock, void* buf, usize_t el_size, usize_t* read_count)
{
    ssize_t ret = 0;
    sl_u8_t* sl = buf;
    
    if(!sl || !sock || !sl->items) { return null_pointer; }
    if(!el_size) { return elsize_zero; }
    
    ret = syscall_3_linux(syscall_read, sock->fd, sl->items, (ssize_t)(sl->count * el_size));
    if(ret < 0) { return io_error; }
    if(read_count) { *read_count = (usize_t)ret; }
    if(!ret) { return connection_closed; }
    return success;
}

#include "socket_private.h"

error_t socket_create
(socket_t* out, sock_family_t family, sock_type_t type,
 sock_protocol_t protocol, const char* addr, u16 port)
{
    ssize_t ret = 0;
    error_t res = success; 
    sock_addr_in_t* in = 0;
    
    if(!out || !addr) { return null_pointer; }

    ret = syscall_3_linux(syscall_socket, family, type, protocol.value);
    if(ret == -1) { return socket_error; }

    out->fd = ret;
    /* Safe to decay to u16 because AF_MAX is 45 */
    out->addr.family = (u16)family;

    if(family == AF_INET || family == AF_INET6) {
        in = (sock_addr_in_t*)(uintptr_t)&out->addr;
        if((res = inet_pton(AF_INET, addr, &in->addr))) { return res; }
        in->port = htons(port);
    }
    
    return success;
}

#include "socket_private.h"

error_t socket_create
(socket_t* out, sock_family_t family, sock_type_t type,
 sock_protocol_t protocol, const char* addr, u16 port)
{
    error_t res = success;
    sock_addr_in_t* in = 0;

    if(!out || !addr) { return null_pointer; }

    __os_socket_create(&out->fd, family, type, protocol.value);

    /* Safe to decay to u16 because AF_MAX is 45 */
    out->addr.family = (u16)family;

    if(family == AF_INET || family == AF_INET6) {
        in = (sock_addr_in_t*)(uintptr_t)&out->addr;
        if((res = inet_pton(AF_INET, addr, &in->addr))) { return res; }
        in->port = htons(port);
    }

    return success;
}

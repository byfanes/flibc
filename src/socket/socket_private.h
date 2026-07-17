#ifndef __FLIBC_SOCKET_PRIVATE_H__
#define __FLIBC_SOCKET_PRIVATE_H__

#include "socket.h"
#include "../os/os_private.h"

typedef struct sock_addr_in_s sock_addr_in_t;

struct sock_addr_in_s {
    u16 family;
    u16 port;
    u32 addr;
    u8 zeros[8];
};

#endif /* __FLIBC_SOCKET_PRIVATE_H__ */

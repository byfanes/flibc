#ifndef __FLIBC_SOCKET_H__
#define __FLIBC_SOCKET_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "da.h"
#include "parse.h"
#include "stdtypes.h"
#include "features.h"

enum sock_type_e {
    SOCK_STREAM     = 1,
    SOCK_DGRAM      = 2,
    SOCK_RAW        = 3,
    SOCK_RDM        = 4,
    SOCK_SEQPACKET  = 5,
    SOCK_DCCP       = 6,
    SOCK_PACKET     = 10
};

enum sock_family_e {
    AF_UNSPEC       = 0,
    AF_LOCAL        = 1,
    AF_UNIX         = 1,
    AF_FILE         = 1,

    AF_INET         = 2,
    AF_AX25         = 3,
    AF_IPX          = 4,
    AF_APPLETALK    = 5,
    AF_NETROM       = 6,
    AF_BRIDGE       = 7,
    AF_ATMPVC       = 8,
    AF_X25          = 9,
    AF_INET6        = 10,
    AF_ROSE         = 11,
    AF_DECnet       = 12,
    AF_NETBEUI      = 13,
    AF_SECURITY     = 14,
    AF_KEY          = 15,
    AF_NETLINK      = 16,
    AF_ROUTE        = 16,

    AF_PACKET       = 17,
    AF_ASH          = 18,
    AF_ECONET       = 19,
    AF_ATMSVC       = 20,
    AF_RDS          = 21,
    AF_SNA          = 22,
    AF_IRDA         = 23,
    AF_PPPOX        = 24,
    AF_WANPIPE      = 25,
    AF_LLC          = 26,
    AF_IB           = 27,
    AF_MPLS         = 28,
    AF_CAN          = 29,
    AF_TIPC         = 30,
    AF_BLUETOOTH    = 31,
    AF_IUCV         = 32,
    AF_RXRPC        = 33,
    AF_ISDN         = 34,
    AF_PHONET       = 35,
    AF_IEEE802154   = 36,
    AF_CAIF         = 37,
    AF_ALG          = 38,
    AF_NFC          = 39,
    AF_VSOCK        = 40,
    AF_KCM          = 41,
    AF_QIPCRTR      = 42,
    AF_SMC          = 43,
    AF_XDP          = 44,

    AF_MAX          = 45
};

enum sock_proto_domain_e {
    PROTO_DOMAIN_NONE = 0,

    PROTO_DOMAIN_INET,
    PROTO_DOMAIN_NETLINK,
    PROTO_DOMAIN_PACKET,
    PROTO_DOMAIN_UNIX
};

typedef enum sock_proto_domain_e sock_proto_domain_t;
typedef enum sock_type_e sock_type_t;
typedef enum sock_family_e sock_family_t;

typedef struct socket_s socket_t;
typedef struct sock_addr_s sock_addr_t;
typedef struct socket_info_s socket_info_t;
typedef struct sock_protocol_s sock_protocol_t;

can_be_da(socket_info_t, da_socket_info_t);
can_be_da(socket_t, da_socket_t);

struct sock_protocol_s {
    sock_proto_domain_t domain;
    u32 value;
};

struct sock_addr_s {
    /* family is sock_family_t but because of the alignment we use u16 here */
    u16 family;
    u8 data[14];
};

struct socket_s {
    ssz fd;
    sock_addr_t addr;
    /* For 16 byte alignment */
    u32 __padding;
};

/* If socket's family is different than AF_INIT or AF_INIT6 port is ignored */
error_t socket_create
(socket_t* out, sock_family_t family, sock_type_t type,
 sock_protocol_t protocol, const char* addr, u16 port);

error_t socket_bind(socket_t* sock);
error_t socket_connect(socket_t* sock);
error_t socket_listen(socket_t* sock);
error_t socket_accept(socket_t* sock, socket_t* out);
error_t socket_close(socket_t* sock);
error_t __socket_read(socket_t* sock, void* buf, usz el_size, usz* _Nullable read_count);
#define socket_read(sock, buf, read) __socket_read(sock, ptr_meta(buf), read)
error_t __socket_write(socket_t* sock, void* buf, usz el_size);
#define socket_write(sock, buf) __socket_write(sock, ptr_meta(buf))

u64 htonll(u64 x);
u32 htonl(u32 x);
u16 htons(u16 x);

u64 ntohll(u64 x);
u32 ntohl(u32 x);
u16 ntohs(u16 x);

error_t inet_pton(sock_family_t family, const char* src, void* dst);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_SOCKET_H__ */

#include "socket_private.h"

error_t socket_listen
(socket_t* sock)
{
    /* Check the pointer is valid and pass it to os layer */
    return (!sock) ? null_pointer : __os_socket_listen(sock->sid, 128);
}

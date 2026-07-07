#include "fs_private.h"

error_t path_cwd_get
(allocator_t* alloc, path_t* p)
{
    /* Init variables */
    error_t res = success;
    ssz ret = 0;

    return ((void)(
        /* Init a string with maxium capacity - alloc and p checked here */
        (res = str_init(alloc, p, MAX_PATH)) ||
        /* Call kernel to give the current working directory
         * ret is the error code and the length of the string including null byte
         */
        (res = (0 > (ret = syscall_2_linux(syscall_getcwd, (ssz)p->items, (ssz)p->capacity)))
            ? fs_error : (slice_set(p, p->items, (usz)ret - 1), success))
    ), (void)( /* Cleanup - if something fails deinit the string */
        (res ? str_deinit(p) : (0))
    ), res);
}

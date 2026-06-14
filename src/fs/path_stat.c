#include "fs_private.h"

error_t path_stat
(path_t* p, fs_stat_t* out)
{
    /* Check inputs */
    if(!p || !out || !p->items || !p->count) { return null_pointer; }

    /* Make sure its null-terminated pointer and call stat syscall */
    /* We already handled shadow null's error in the if statement */
    str_add_shadow_null(p);

    /* Check return of the syscall */
    if(0 != syscall_2_linux(syscall_stat, (ssz)p->items, (ssz)out))
    { return fs_error; }

    return success;
}

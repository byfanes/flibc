#include "fs_private.h"

fc_error_t path_stat
(path_t* p, fs_stat_t* out)
{
    /* Init variables */
    ssize_t ret = 0;

    /* Check inputs */
    if(!p || !out || !p->items || !p->count) { return fce_null_pointer; }

    /* Make sure its null-terminated pointer and call stat syscall */
    /* We already handled shadow null's error in the if statement */
    str_add_shadow_null(p);
    ret = syscall_2(syscall_stat, p->items, out);

    /* Check return of the syscall */
    if(ret != 0) { return fce_fs_error; }
    
    return fce_success;
}

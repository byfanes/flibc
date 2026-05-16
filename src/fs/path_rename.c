#include "fs_private.h"

error_t path_rename
(path_t* from, path_t* to)
{
    /* Init variables */
    ssize_t ret = 0;
    if(!from || !to || !from->items || !from->count || !to->items || !to->count)
    { return null_pointer; }

    /* Make sure its null-terminated pointer and call rename syscall */
    /* We already handled shadow null's error in the if statement */
    str_add_shadow_null(from);
    str_add_shadow_null(to);
    ret = syscall_2(syscall_rename, from->items, to->items);

    /* Check return of the syscall */
    if(ret != 0) { return fs_error; }
    
    return success;
}

#include "fs_private.h"

error_t path_rename
(path_t* from, path_t* to)
{
    /* Check input */
    if(!from || !to || !from->items || !from->count || !to->items || !to->count)
    { return null_pointer; }

    /* Make sure its null-terminated pointer and call rename syscall */
    /* We already handled shadow null's error in the if statement */
    str_add_shadow_null(from);
    str_add_shadow_null(to);

    /* Call and check return of the syscall */
    if(0 != syscall_2_linux(syscall_rename, (ssize_t)from->items, (ssize_t)to->items))
    { return fs_error; }
    
    return success;
}

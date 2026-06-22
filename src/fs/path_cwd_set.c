#include "fs_private.h"

error_t path_cwd_set
(path_t* p)
{
    /* Check inputs */
    if(!p || !p->items || !p->count) { return null_pointer; }

    /* Make path null terminated  */
    str_add_shadow_null(p);

    /* Call syscall and check return of the syscall */
    if(0 > syscall_1_linux(syscall_chdir, (ssz)p->items))
    { return fs_error; }

    return success;
}

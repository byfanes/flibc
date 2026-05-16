#include "fs_private.h"

error_t path_cwd_set
(path_t* p)
{
    /* Init variables */
    ssize_t ret = 0;
    
    /* Check inputs */
    if(!p || !p->items || !p->count) { return null_pointer; }

    /* Call syscall */
    str_add_shadow_null(p);
    ret = syscall_1(syscall_chdir, p->items);

    /* Check return of the syscall */
    if(ret != 0) { return fs_error; }
    
    return success;
}

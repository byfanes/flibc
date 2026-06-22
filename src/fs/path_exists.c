#include "fs_private.h"

error_t path_exists
(path_t* p, bool* out)
{
    /* Init variables */
    error_t res = success;

    /* Check inputs set it to false for failure case */
    if(!out) { return null_pointer; }
    *out = false;

    /* Check if not fail set it */
    if((res = str_add_shadow_null(p))) { return res; }
    if(0 == syscall_2_linux(syscall_access, (ssz)p->items, F_OK))
    { *out = true; }
    
    return success;
}

#include "process_private.h"

error_t system_run
(cmd_t cmd)
{
    /* Init variables */
    error_t res = success;

    /* Check input and add null byte to end */
    if((res = str_add_shadow_null(&cmd))) { return res; }

    /* Redirect to another system function to handle now on */
    return system_run_cstr((char*)cmd.items);
}

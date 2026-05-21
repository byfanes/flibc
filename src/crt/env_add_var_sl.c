#include "crt_private.h"

error_t env_add_var_sl
(allocator_t* alloc, env_t* env, slice(u8) key, slice(u8) val)
{
    /* Init variables */
    env_var_t var = {0};
    error_t res = success;

    /* Check input */
    if(!alloc || !env || !env->continues.items || !env->vars.items ||
       !key.base || !val.base || !key.count || !val.count)
    { return null_pointer; }

    /* Init strings and cat with corresponding slices */
    if((res = str_init(alloc, &var.key, key.count))) { return res; }
    if((res = str_init(alloc, &var.val, val.count))) { return res; }
    if((res = strcat_sl(&var.key, key))) { return res; }
    if((res = strcat_sl(&var.val, val))) { return res; }

    /* Give variable to function to handle rest of the stuff such as appending to DAs */
    return env_add_var_t(env, var);
}

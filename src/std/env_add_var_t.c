#include "std_private.h"

error_t env_add_var_t
(env_t* env, env_var_t var)
{
    /* Init variables */
    error_t res = success;

    /* Checks done inside of them - Add variable to variable list */
    if((res = da_push(&env->vars, &var))) { return res; }
    if((res = da_push(&env->list, (char**)&var.continues.items))) { return res; }
    if((res = da_add_shadow_null_segment(&env->list))) { return res; }

    return success;
}

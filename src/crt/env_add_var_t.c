#include "crt_private.h"

error_t env_add_var_t(env_t* env, env_var_t var)
{
    /* Init variables */
    error_t res = success;
    u8 null_byte = 0, eq = '=';
    usize_t idx = 0;
    cstr_t ptr = 0;

    /* env check done here */
    /* Add variable to variable list */
    if((res = da_push(&env->vars, &var))) { return res; }

    /* Add variable to continues list with '=' and '\0' */
    idx = env->continues.count;
    if((res = strcat(&env->continues, &var.key))) { return res; }
    if((res = da_push(&env->continues, &eq))) { return res; }
    if((res = strcat(&env->continues, &var.val))) { return res; }
    if((res = da_push(&env->continues, &null_byte))) { return res; }

    /* While adding to continues it might realloc so we use index instead */
    ptr = (cstr_t)&env->continues.items[idx];

    if((res = da_push(&env->list, &ptr))) { return res; }
    if((res = da_add_shadow_null_segment(&env->list))) { return res; }

    return success;
}

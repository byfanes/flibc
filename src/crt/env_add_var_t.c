#include "crt_private.h"

error_t env_add_var_t(env_t* env, env_var_t var)
{
    /* Init variables */
    error_t res = success;
    u8 null_byte = 0, eq = '=';

    /* env check done here */
    /* Add variable to variable list */
    if((res = da_push(&env->vars, &var))) { return res; }

    /* Add variable to continues list with '=' and '\0' */
    if((res = strcat(&env->continues, &var.key))) { return res; }
    if((res = da_push(&env->continues, &eq))) { return res; }
    if((res = strcat(&env->continues, &var.val))) { return res; }
    if((res = da_push(&env->continues, &null_byte))) { return res; }
    if((res = da_add_shadow_null_segment(&env->continues))) { return res; }

    return success;
}

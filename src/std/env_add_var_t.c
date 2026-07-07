#include "std_private.h"

error_t env_add_var_t
(env_t* env, env_var_t var)
{
    /* Init variables */
    error_t res = success;

    return ((void)(
        (res = (env) ? success : null_pointer) ||
        (res = da_push(&env->vars, &var)) ||
        (res = da_push(&env->list, (char**)(uintptr_t)&var.continues.items)) ||
        (res = da_add_shadow_null_segment(&env->list))
    ), res);
}

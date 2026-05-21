#include "crt_private.h"

error_t env_add_var
(allocator_t* alloc, env_t* env, str_t* key, str_t* val)
{
    /* Init variables */
    env_var_t var = {0};
    error_t res = success;

    /* alloc env key val check done here */
    /* Duplicate memory so we take the new ownership */
    if((res = strdup(alloc, key, &var.key))) { return res; }
    if((res = strdup(alloc, val, &var.val))) { return res; }

    /* Give variable to function to handle rest of the stuff such as appending to DAs */
    return env_add_var_t(env, var);
}

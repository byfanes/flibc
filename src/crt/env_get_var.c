#include "crt_private.h"

error_t env_get_var
(env_t* env, str_t* key, str_t* val)
{
    /* Init variables */
    u32 i = 0;

    /* Check input */
    if(!env || !env->vars.items || !key ||
       !key->items || !key->count || !val || !val->items)
    { return null_pointer; }

    /* Search for the key in the array if we found it copy it to val */
    for(; i < env->vars.count; ++i) {
        if(streq(key, &env->vars.items[i].key)) {
            return strcpy(val, &env->vars.items[i].val);
        }
    }

    /* We could not find it */
    return does_not_exist;
}

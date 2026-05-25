#include "crt_private.h"

error_t env_get_var
(env_t* env, str_t* key, str_t* val)
{
    /* Init variables */
    u32 i = 0;
    bool out = false;
    error_t res = success;

    /* Check input */
    if(!env || !env->vars.items || !key ||
       !key->items || !key->count || !val || !val->items)
    { return null_pointer; }

    /* Search for the key in the array if we found it copy it to val */
    for(; i < env->vars.count; ++i) {
        if((res = memcmp((slice_u8*)key, &env->vars.items[i].key, &out))) { return res; }
        if(out) {
            str_clear(val);
            return strcat_sl(val, env->vars.items[i].val);
        }
    }

    /* We could not find it */
    return does_not_exist;
}

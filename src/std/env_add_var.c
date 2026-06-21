#include "std_private.h"

error_t env_add_var
(allocator_t* alloc, env_t* env, sl_u8_t* key, sl_u8_t* val)
{
    /* Init variables */
    env_var_t var = {0};
    error_t res = success;

    /* Check input */
    /* Note: val count can be zero for things like 'PAGER=' */
    if(!alloc || !env || !env->vars.items ||
       !key->items || !val->items || !key->count)
    { return null_pointer; }

    /* Init strings and cat with corresponding slices */
    if((res = str_init(alloc, &var.continues, key->count + val->count + 1))) { return res; }
    if((res = str_cat_sl(&var.continues, key))) { return res; }
    if((res = str_cat_cstr(&var.continues, "="))) { return res; }
    if((res = str_cat_sl(&var.continues, val))) { return res; }
    if((res = str_cat_cstr(&var.continues, ""))) { return res; }

    slice_set(&var.key, var.continues.items, key->count);
    slice_set(&var.val, var.continues.items + key->count + 1, val->count);

    /* Give variable to function to handle rest of the stuff such as appending to DAs */
    return env_add_var_t(env, var);
}

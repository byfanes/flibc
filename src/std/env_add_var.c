#include "std_private.h"

error_t env_add_var
(allocator_t* alloc, env_t* env, sl_u8_t* key, sl_u8_t* val)
{
    /* Init variables */
    env_var_t var = {0};
    error_t res = success;

    /* Note: val count can be zero for things like 'PAGER=' */
    return ((void)(
        /* Check input */
        (res = (env && env->vars.items && val && key) ? success : null_pointer) ||
        /* Init strings and cat with corresponding slices */
        (res = str_init(alloc, &var.continues, key->count + val->count + 1)) ||
        (res = str_cat_sl(&var.continues, key)) ||
        (res = str_cat_cstr(&var.continues, "=")) ||
        (res = str_cat_sl(&var.continues, val)) ||
        (res = str_add_shadow_null(&var.continues)) ||
        (res = slice_set(&var.key, var.continues.items, key->count)) ||
        (res = slice_set(&var.val, var.continues.items + key->count + 1, val->count)) ||
        /* Give variable to function to handle rest of the stuff such as appending to DAs */
        (res = env_add_var_t(env, var))
    ), (void)( /* Cleanup */
        ((res) ? str_deinit(&var.continues) : (0))
    ), res);
}

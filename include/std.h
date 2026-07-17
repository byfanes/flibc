#ifndef __FLIBC_STD_H__
#define __FLIBC_STD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"
#include "io.h"
#include "memory.h"
#include "da.h"
#include "string.h"

typedef struct std_s std_t;
typedef struct env_s env_t;
typedef struct env_var_s env_var_t;

can_be_da(env_var_t, da_env_var_t);
can_be_slice(sl_cstr_t, sl_cstrs_t);
can_be_da(const char *, da_ccstr_t);

struct env_var_s {
    str_t continues;
    sl_u8_t key;
    sl_u8_t val;
};

struct env_s {
    da_env_var_t vars;
    /* Should end with a null */
    da_ccstr_t list;
};

struct std_s {
    allocator_t* alloc;
    io_t io;
    sl_u8_t exe;
    sl_cstrs_t args;
    env_t env;
};

#ifndef FLIBC_OLD_MAIN
/* if user wants to use old main signature this will cause some error so this needs to be disable
 * and if user wants to use old main they are probably use it with a glibc/musl or any other library
 * so those libraries should start/init their internals and thats mostly done before the main
 */
extern error_t main(std_t* std);
#endif /* FLIBC_OLD_MAIN */

error_t env_add_var_t(env_t* env, env_var_t var);
error_t env_add_var(allocator_t* alloc, env_t* env, sl_u8_t* key, sl_u8_t* val);

error_t env_get_var(env_t* env, str_t* key, str_t* val);

/* This assumes envp comes after argv */
void std_from_args(std_t* std, int argc, char** argv);
noreturn std_exit(std_t* std, ssz code);
noreturn std_abort(ssz code);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_STD_H__ */

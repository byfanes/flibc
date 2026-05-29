#ifndef __FLIBC_CRT_H__
#define __FLIBC_CRT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdtypes.h"
#include "stdlib.h"
#include "stdio.h"
#include "memory.h"
#include "da.h"
#include "string.h"

typedef struct std_s std_t;
typedef struct env_s env_t;
typedef struct env_var_s env_var_t;

can_be_da(env_var_t, da_env_var_t);
can_be_slice(sl_cstr_t, sl_cstrs_t);
can_be_da(char*, da_cstr_t);

struct env_var_s {
    str_t continues;
    sl_u8_t key;
    sl_u8_t val;
};

struct env_s {
    da_env_var_t vars;
    /* Should end with a null */
    da_cstr_t list;
};

struct std_s {
    allocator_t* alloc;
    stdio_t io;
    sl_u8_t exe;
    sl_cstrs_t args;
    env_t env;
};

extern error_t main(std_t);

error_t env_add_var_t(env_t* env, env_var_t var);
error_t env_add_var(allocator_t* alloc, env_t* env, sl_u8_t* key, sl_u8_t* val);

error_t env_get_var(env_t* env, str_t* key, str_t* val);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_CRT_H__ */

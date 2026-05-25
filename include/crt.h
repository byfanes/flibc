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
typedef char* cstr_t;

can_be_slice(slice_u8);
can_be_da(env_var_t);
can_be_da(cstr_t);

struct env_var_s {
    str_t continues;
    slice(u8) key;
    slice(u8) val;
};

struct env_s {
    da(env_var_t) vars;
    /* Should end with a null */
    da(cstr_t) list;
};

struct std_s {
    allocator_t* alloc;
    stdio_t io;
    slice(u8) exe;
    slice(slice_u8) args;
    env_t env;
};

extern error_t main(std_t);

error_t env_add_var_t(env_t* env, env_var_t var);
error_t env_add_var(allocator_t* alloc, env_t* env, slice(u8)* key, slice(u8)* val);

error_t env_get_var(env_t* env, str_t* key, str_t* val);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_CRT_H__ */

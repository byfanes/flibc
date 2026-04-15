#ifndef __FLIBC_DA_H__
#define __FLIBC_DA_H__

#include "stdtypes.h"
#include "memory.h"

/* This macro will be used with multiplying sizeof(*da->base) */
#ifndef FLIBC_DA_INIT
#define FLIBC_DA_INIT 32
#endif /* FLIBC_DA_INIT */

#define can_be_da_named(type,name) \
    typedef struct {               \
        type *items;               \
        const uint32_t count;      \
        const uint32_t capacity;   \
    } name

#define can_be_da(type)            \
    typedef struct type ## _da_s { \
        type *items;               \
        const uint32_t count;      \
        const uint32_t capacity;   \
    } type ## _da_t

struct def_da_header_s {
    void* items;
    uint32_t count;
    uint32_t capacity;
};

typedef struct def_da_header_s def_da_header_t;

#define da_push(da, element) ({             \
    typeof(da) _da = (da);                  \
    def_da_header_t* _def_da = (void*)_da;  \
    fc_error_t _err = __da_reserve          \
    (_def_da, sizeof(*(_da)->items),1);     \
    if (_err == fce_success) {              \
        _da->items[_da->count] = (element); \
        _def_da->count++;                   \
    }                                       \
    _err;                                   \
})

#define da_reserve(da, add_amount) ({       \
    typeof(da) _da = (da);                  \
    __da_reserve((def_da_header_t*)_da,     \
        sizeof(*(_da)->items), add_amount); \
})

#define da_init_cap(da,cap) ({                                        \
    typeof(da) _da = (da);                                            \
    __da_init_cap((def_da_header_t*)_da, sizeof(*(_da)->items), cap); \
})

fc_error_t __da_reserve(def_da_header_t* da, uint32_t n_size, uint32_t amount);
fc_error_t __da_init_cap(def_da_header_t* da, uint32_t n_size, uint32_t amount);


#endif /* __FLIBC_DA_H__ */

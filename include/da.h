#ifndef __FLIBC_DA_H__
#define __FLIBC_DA_H__

#include "stdtypes.h"
#include "memory.h"
#include "features.h"

/* This macro will be used with multiplying sizeof(*da->base) */
#define FLIBC_DA_INIT 32

/* Any optimization flags will broke '= {0};' statements
 * and will cause a segfault
 */

#define can_be_da(type)            \
    typedef struct { \
        type *items;               \
        uint32_t count;      \
        uint32_t capacity;   \
    } da_ ## type

#define da(type) CONCAT(da_,type)

can_be_da(uint64_t);
can_be_da(uint32_t);
can_be_da(uint16_t);
can_be_da(uint8_t);
can_be_da(int64_t);
can_be_da(int32_t);
can_be_da(int16_t);
can_be_da(int8_t);
can_be_da(char);
can_be_da(byte_t);

struct def_da_header_s {
    byte_t* items;
    uint32_t count;
    uint32_t capacity;
};

typedef struct def_da_header_s def_da_header_t;

#define da_push(err, da, element) do {                     \
    typeof(da) _da = (da);                                 \
    def_da_header_t* _def_da = (void*)_da;                 \
    err = __da_reserve(_def_da, sizeof(*(_da)->items), 1); \
    if (err == fce_success) {                              \
        _da->items[_da->count] = (element);                \
        _def_da->count++;                                  \
    }                                                      \
} while(0)

#define da_reserve(err, da, add_amount) \
    do { __da_reserve((void*)da, sizeof(*(da)->items), add_amount); } while(0)

#define da_init_cap(err, da, cap) \
    do { err = __da_init_cap((void*)(da), sizeof(*(da)->items), cap); } while(0)

#define da_zeroed(err, da) do {                      \
    typeof(da) _da = (da);                           \
    if(!_da->items) { err = fce_da_zeroed_nullptr; } \
    else {                                           \
        def_slice_t src = da_to_slice(_da);          \
        err = fc_memset(src,0);                      \
    }                                                \
} while(0)

#define da_clear(da) do { def_da_header_t* _da = (void*)(da);_da->count = 0; } while(0)
#define da_truncate(err, da, c) do { err = __da_truncate((void*)da, c); } while(0)

#define da_get(err, da, i, out) \
    do { err = __da_get((void*)(da), i, sizeof(*(da)->items), out); } while(0)

#define da_unordered_remove(err, da, i, out) \
    do { err = __da_unordered_remove((void*)(da), i, sizeof(*(da)->items), out); } while(0);

#define da_swap(err, da, lhs, rhs) \
    do { __da_swap((void*)(da), lhs, rhs, sizeof(*(da)->items)); } while(0)

#define da_insert(err, da, idx, element) do {                    \
    typeof(da) _da = (da);                                       \
    err = __da_insert((void*)(_da), idx, sizeof(*(_da)->items)); \
    if (err == fce_success) {                                    \
        _da->items[idx] = element;                               \
        ((def_da_header_t*)(void*)_da)->count++;                 \
    }                                                            \
} while(0)

#define da_remove(err, da, idx) \
    do { err = __da_remove((void*)(da), idx, sizeof(*(da)->items)); } while(0)

#define da_pop(err, da, out) \
    do { err = __da_pop((void*)(da), out, sizeof(*(da)->items)); } while(0)

#define da_pop_first(err, da, out) \
    do { err = __da_pop_first((void*)(da), out, sizeof(*(da)->items)); } while(0)

#define da_first(err, da, out) \
    do { err = __da_first((void*)(da), out, sizeof(*(da)->items)); } while(0)

#define da_last(err, da, out) \
    do { err = __da_last((void*)(da), out, sizeof(*(da)->items)); } while(0)

#define da_free(err, da) do {            \
    typeof(da) _da = (da);               \
    err = fc_free(&(_da)->items);        \
    memset_sized((_da), 0, sizeof((_da))); \
} while(0)

fc_error_t __da_push_slice(def_da_header_t* da, def_slice_t sl, uint32_t size, uint32_t count);

fc_error_t __da_reserve(def_da_header_t* da, uint32_t n_size, uint32_t amount);
fc_error_t __da_init_cap(def_da_header_t* da, uint32_t n_size, uint32_t amount);

fc_error_t __da_truncate(def_da_header_t* da, uint32_t len);
fc_error_t __da_unordered_remove(def_da_header_t* da, uint32_t idx, uint32_t n_size, void* out);

fc_error_t __da_get(def_da_header_t* da, uint32_t idx, uint32_t n_size, void* out);
fc_error_t __da_swap(def_da_header_t* da, uint32_t lhs, uint32_t rhs, uint32_t n_size);

fc_error_t __da_insert(def_da_header_t* da, uint32_t idx, uint32_t n_size);
fc_error_t __da_remove(def_da_header_t* da, uint32_t idx, uint32_t n_size);

fc_error_t __da_pop(def_da_header_t* da, void* out, uint32_t n_size);
fc_error_t __da_pop_first(def_da_header_t* da, void* out, uint32_t n_size);

fc_error_t __da_first(def_da_header_t* da, void* out, uint32_t n_size);
fc_error_t __da_last(def_da_header_t* da, void* out, uint32_t n_size);

#endif /* __FLIBC_DA_H__ */

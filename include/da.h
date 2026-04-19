#ifndef __FLIBC_DA_H__
#define __FLIBC_DA_H__

#include "stdtypes.h"
#include "memory.h"
#include "features.h"

/* This macro will be used with multiplying sizeof(*da->base) */
#define FLIBC_DA_INIT 32

#define can_be_da(type)            \
    typedef struct { \
        type *items;               \
        const uint32_t count;      \
        const uint32_t capacity;   \
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

#define da_push_slice(da, sl) (__da_push_slice((void*)(da), (sl), sizeof(*(sl).base), (sl).count))

#define da_pushs(da, ...) ({                                                        \
    typeof(da) _da = (da);                                                          \
    def_da_header_t* _def_da = (void*)_da;                                          \
    typeof(*(_da)->items) total[] = {__VA_ARGS__};                                  \
    uint32_t count = sizeof(total)/sizeof(total[0]);                                \
    fc_error_t _err = __da_reserve                                                  \
    (_def_da, sizeof(*(_da)->items),count);                                         \
    if (_err == fce_success) {                                                      \
        def_slice_t src = (def_slice_t) { .base = total, .count = count*sizeof(*(_da)->items) };\
        def_slice_t dst = (def_slice_t) { .base = &_da->items[_da->count], .count=src.count };  \
        if((_err = fc_memcpy(dst,src))) {                                           \
            return _err;                                                            \
        }                                                                           \
        _def_da->count += count;                                                    \
    }                                                                               \
    _err;                                                                           \
})

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

#define da_zeroed(da) ({                   \
    typeof(da) _da = (da);                 \
    fc_error_t _res = fce_success;         \
    if(!_da->items) {                      \
        _res = fce_da_zeroed_nullptr;      \
    }                                      \
    else {                                 \
        def_slice_t src = da_to_ptr(_da);  \
        _res = fc_memset(src,0);           \
    }                                      \
    _res;                                  \
})

#define da_clear(da) do { def_da_header_t* _da = (def_da_header_t*)(da);_da->count = 0; } while(0)
#define da_truncate(da,c) __da_truncate((def_da_header_t*)da, c)

#define da_get(da,i,out) ({             \
    typeof(da) _da = (da);              \
    __da_get((def_da_header_t*)(_da),i, \
         sizeof(*(_da)->items),out); \
})

#define da_unordered_remove(da,i,out) ({             \
    typeof(da) _da = (da);                           \
    __da_unordered_remove((def_da_header_t*)(_da),i, \
         sizeof(*(_da)->items),out); \
})

#define da_swap(da,lhs,rhs) ({           \
    typeof(da) _da = (da);               \
    __da_swap((def_da_header_t*)(_da),   \
         lhs,rhs,sizeof(*(_da)->items)); \
})

#define da_insert(da,idx,element) ({            \
    typeof(da) _da = (da);                      \
    def_da_header_t* _def_da = (void*)(_da);    \
    fc_error_t _res = fce_success;              \
    _res = __da_insert((def_da_header_t*)(_da), \
                idx,sizeof(*(_da)->items));     \
    if (_res == fce_success) {                  \
        _da->items[idx] = element;              \
        _def_da->count++;                       \
    }                                           \
    _res;                                       \
})

#define da_remove(da,idx) ({             \
    typeof(da) _da = (da);               \
    __da_remove((def_da_header_t*)(_da), \
         idx,sizeof(*(_da)->items));     \
})

#define da_pop(da,out) ({             \
    typeof(da) _da = (da);            \
    __da_pop((def_da_header_t*)(_da), \
         out,sizeof(*(_da)->items));  \
})

#define da_pop_first(da,out) ({           \
    typeof(da) _da = (da);                \
    __da_pop_first((def_da_header_t*)     \
        (_da),out,sizeof(*(_da)->items)); \
})

#define da_first(da,out) ({             \
    typeof(da) _da = (da);              \
    __da_first((def_da_header_t*)(_da), \
         out,sizeof(*(_da)->items));    \
})

#define da_last(da,out) ({             \
    typeof(da) _da = (da);             \
    __da_last((def_da_header_t*)(_da), \
         out,sizeof(*(_da)->items));   \
})

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

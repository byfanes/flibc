#ifndef __FLIBC_STRING_H__
#define __FLIBC_STRING_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "error.h"
#include "memory.h"
#include "da.h"
#include "base.h"

/* String - Implementation
 * Its almost same as dynamic arrays implementation but this one checks data's format being utf8 or not
 * yet again IT IS NOT SAFE FOR COPYING instead use pointers to dedicated struct
 * for function which mutates the variable they take as pointer other oners dont
 */

typedef da_u8_t str_t;
can_be_da(str_t, da_str_t);

error_t str_init(allocator_t* alloc, str_t* out, usz amount);
error_t str_deinit(str_t* out);
error_t str_to_cstr(allocator_t* alloc, str_t* base, char** out);
error_t str_from_cstr(allocator_t* alloc, str_t* out, const char* cstr);
error_t str_dup(allocator_t* alloc, str_t* base, str_t* out);

error_t str_formatf(str_t* base, const char* fmt, ...);
error_t str_formatf_sl(str_t* base, sl_u8_t fmt, ...);

/* We allow user to pass different pointers in strcat_sl because we will check it for utf8 */
error_t __str_cat_sl(str_t* base, void* sl, usz el_size);
#define str_cat_sl(base, sl) __str_cat_sl((base), (sl), sizeof((sl)->items[0]))
error_t str_copy(str_t* base, str_t* cpy);
error_t str_cat(str_t* base, str_t* extend);
error_t str_cat_cstr(str_t* base, const char* cstr);

/* cstrlen as in the name suggest it takes a null terminated string */
usz cstr_len(const char* s);
error_t cstr_utf8_len(const char* s, usz* out);
error_t str_utf8_len(str_t* base, usz* out);

error_t __sl_utf8_len(void* sl, usz el_size, usz* out);
#define sl_utf8_len(sl, out) __sl_utf8_len((sl), sizeof((sl)->items[0]), out)

error_t str_grow(str_t* str, usz amount);
error_t str_grow_if(str_t* str, usz amount);

error_t str_add_shadow_null(str_t* str);
error_t str_clear(str_t* str);

/* Those functions just matches the data so they can not result with an error */
bool str_eq(str_t* lhs, str_t* rhs);
bool str_eq_cstr(str_t* lhs, const char* cstr);
bool str_eq_sl(str_t* lhs, sl_u8_t* sl);
/* cstreq as in the name suggest it takes a null terminated string */
bool cstr_eq(const char* l, const char* r);

bool __sl_is_utf8(void* sl, usz el_size);
#define sl_is_utf8(sl) __sl_is_utf8((sl), sizeof((sl)->base[0]))

error_t sl_formatf(sl_u8_t buf, usz* _Nullable wrote_count, const char* fmt, ...);
error_t sl_formatf_sl(sl_u8_t buf, usz* _Nullable wrote_count, sl_u8_t fmt, ...);

error_t sl_vformatf(sl_u8_t buf, usz* _Nullable wrote_count, const char* fmt, va_list ap);
error_t sl_vformatf_sl(sl_u8_t buf, usz* _Nullable wrote_count, sl_u8_t fmt, va_list ap);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_STRING_H__ */

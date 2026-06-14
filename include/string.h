#ifndef __FLIBC_STRING_H__
#define __FLIBC_STRING_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "error.h"
#include "memory.h"
#include "da.h"

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
error_t strdup(allocator_t* alloc, str_t* base, str_t* out);

error_t str_formatf(str_t* base, const char* fmt, ...);
error_t str_formatf_sl(str_t* base, sl_u8_t fmt, ...);

error_t strcpy(str_t* base, str_t* cpy);
error_t strcat(str_t* base, str_t* extend);

/* We allow user to pass different pointers in strcat_sl because we will check it for utf8 */
error_t __strcat_sl(str_t* base, void* sl, usz el_size);
#define strcat_sl(base, sl) __strcat_sl((base), (sl), sizeof((sl)->items[0]))

error_t strcat_cstr(str_t* base, const char* cstr);
error_t str_utf8len(str_t* base, usz* out);
error_t __sl_utf8len(void* sl, usz el_size, usz* out);
#define sl_utf8len(sl, out) __sl_utf8len((sl), sizeof((sl)->items[0]), out)

error_t str_grow(str_t* str, usz amount);
error_t str_grow_if(str_t* str, usz amount);

error_t str_add_shadow_null(str_t* str);

error_t str_clear(str_t* str);

/* Those functions just matches the data so they can not result with an error */
bool streq(str_t* lhs, str_t* rhs);
bool streq_cstr(str_t* lhs, const char* cstr);
bool __is_utf8_sl(void* sl, usz el_size);
#define is_utf8_sl(sl) __is_utf8_sl((sl), sizeof((sl)->base[0]))

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_STRING_H__ */

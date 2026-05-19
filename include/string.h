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

typedef da(u8) str_t;
can_be_da(str_t);

error_t str_init(allocator_t* alloc, str_t* out, usize_t amount);
error_t str_deinit(str_t* out);
error_t str_to_cstr(allocator_t* alloc, str_t* base, char** out);
error_t str_from_cstr(allocator_t* alloc, str_t* out, const char* cstr);
error_t strdup(allocator_t* alloc, str_t* base, str_t* out);

error_t strcpy(str_t* base, str_t* cpy);
error_t strcat(str_t* base, str_t* extend);
error_t strcat_sl(str_t* base, slice(u8) sl);
error_t strcat_cstr(str_t* base, const char* cstr);
error_t str_utf8len(str_t* base, usize_t* out);
error_t sl_utf8len(slice(u8) sl, usize_t* out);

error_t str_grow(str_t* str, usize_t amount);
error_t str_grow_if(str_t* str, usize_t amount);

error_t str_add_shadow_null(str_t* str);

error_t str_clear(str_t* str);

/* Those functions just matches the data so they can not result with an error */
bool streq(str_t* lhs, str_t* rhs);
bool streq_cstr(str_t* lhs, const char* cstr);
bool is_utf8_sl(slice(u8) sl);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_STRING_H__ */

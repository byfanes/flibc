#ifndef __FLIBC_STRING_H__
#define __FLIBC_STRING_H__

#include "memory.h"

/* String - Implementation
 * Its almost same as dynamic arrays implementation but this one checks data's format being utf8 or not
 * yet again IT IS NOT SAFE FOR COPYING instead use pointers to dedicated struct
 * for function which mutates the variable they take as pointer other oners dont
 */

typedef const struct str_s str_t;

struct str_s {
    u8* items;
    u32 count;
    u32 capacity;
};

fc_error_t str_from_cstr(str_t* out, const char* cstr);
fc_error_t str_to_cstr(str_t base, char** out);
fc_error_t strdup(str_t base, str_t* out);
fc_error_t strcpy(str_t* base, str_t cpy);
fc_error_t strcat(str_t* base, str_t extend);
fc_error_t strcat_sl(str_t* base, slice_t sl);
fc_error_t str_utf8len(str_t base, u32* out);
fc_error_t sl_utf8len(slice_t sl, u32* out);
fc_error_t str_reserve(str_t* str, u32 amount);
fc_error_t str_reserve_if(str_t* str, u32 amount);

/* Those functions just matches the data so they can not result with an error */
bool streq(str_t lhs, str_t rhs);
bool is_utf8_sl(slice_t sl);

#endif /* __FLIBC_STRING_H__ */

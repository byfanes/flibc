#ifndef __FLIBC_STRING_PRIVATE_H__
#define __FLIBC_STRING_PRIVATE_H__

#include "string.h"
#include "../memory/memory_private.h"

/* This is an internal function so it does not any validation for arguments or its avaliable length */
fc_error_t str_copy_content(str_t* str, slice_t sl);

#endif /* __FLIBC_STRING_PRIVATE_H__ */

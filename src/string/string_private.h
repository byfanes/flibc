#ifndef __FLIBC_STRING_PRIVATE_H__
#define __FLIBC_STRING_PRIVATE_H__

#include "string.h"
#include "../memory/memory_private.h"
#include "../da/da_private.h"

/* This is an internal function so it does not any validation for arguments or its avaliable length */
error_t __str_copy_content(str_t* str, slice(u8) sl);

#endif /* __FLIBC_STRING_PRIVATE_H__ */

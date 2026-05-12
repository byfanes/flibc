#ifndef __FLIBC_STDLIB_H__
#define __FLIBC_STDLIB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdtypes.h"
#include "features.h"

_Noreturn void exit(ssize_t code);
_Noreturn void abort(void);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_STDLIB_H__ */

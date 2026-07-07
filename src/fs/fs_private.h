#ifndef __FLIBC_FS_PRIVATE_H__
#define __FLIBC_FS_PRIVATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "../helpers/helpers.h"
#include "../da/da_private.h"
#include "syscall.h"
#include "fs.h"
#include "io.h"
#include "memory.h"

/* TODO: in future we will but __arch_* functions which will handle platform
 * layer right now the code has lots of OS/arch depending functions and for
 * the structure all OS/arch depending code should be in the arch/ directory
 * and rest of all can be writable in C and its should be crossplatform
 */

/* TODO: This is not cross-platform like other functions
 * This struct has been stolen from linux kernel
 */
typedef struct linux_dirent64_s linux_dirent64_t;
struct linux_dirent64_s {
    u64 d_ino;
    i64 d_off;
    u16 d_reclen;
    u8 d_type;
    char d_name[1];
};

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_FS_PRIVATE_H__ */

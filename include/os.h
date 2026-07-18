#ifndef __OS_H__
#define __OS_H__

#include "base.h"

/* This header is for public definitions of os types
 * This done to prevent code duplication
 */

/* Note: To unify platform specific resource identifiers for example linux file
 * descriptors and windows handles we use a type + id naming convention
 * for example a file id is named `os_fid_t`
 */

/* Note: This file should only have struct definitions not type definitions */

#if SYS_OS == SYS_OS_LINUX
typedef ssz   os_fid_t;
typedef ssz   os_pid_t;
typedef ssz   os_sid_t;
typedef void* os_tid_t;
#define OS_INVALID_FILE_HANDLE ((os_fid_t)(-1))
#else
#error "Current platform is not supported yet!"
#endif/* SYS_OS == SYS_OS_LINUX */

enum file_type_e {
    file_read,
    file_write,
    file_append,
    file_read_plus,
    file_write_plus,
    file_append_plus
};

enum seek_type_e {
    seek_set = 0,
    seek_cur = 1,
    seek_end = 2
};

struct sock_addr_s {
    /* family is sock_family_t but because of the alignment we use u16 here */
    u16 family;
    u8 data[14];
};

struct socket_s {
    os_sid_t sid;
    struct sock_addr_s addr;
    /* For 16 byte alignment */
    u32 __padding;
};

struct time_s {
    u64 sec;
    u64 nsec;
};

struct thread_s {
    os_tid_t tid;
};

struct mutex_s {
    volatile i32 state;
};

struct thread_cond_s {
    volatile u32 seq;
};

/* This will work because can_be_slice macros defines types which are already typedef-ed */
struct sl_cstr_s {
    char *items;
    usz   count;
};


#endif /* __OS_H__ */

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
/* Forward declaration for thread structure to use in internals */
struct os_thread_s;
typedef struct os_thread_s *os_tid_t;
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

struct timestamp_s {
    u64 sec;
    u64 nsec;
};

struct thread_s {
    os_tid_t tid;
};

struct mutex_s {
    volatile s32 state;
};

struct thread_cond_s {
    volatile u32 seq;
};

/* This will work because can_be_slice macros defines types which are already typedef-ed */
struct sl_cstr_s {
    char *items;
    usz   count;
};

#define FS_STAT_VALID_TYPE      (1u << 0)
#define FS_STAT_VALID_UID       (1u << 1)
#define FS_STAT_VALID_GID       (1u << 2)
#define FS_STAT_VALID_PERM      (1u << 3)
#define FS_STAT_VALID_RDEV      (1u << 4)
#define FS_STAT_VALID_BLOCKS    (1u << 5)
#define FS_STAT_VALID_BLKSIZE   (1u << 6)
#define FS_STAT_VALID_CTIME     (1u << 7)
#define FS_STAT_VALID_BTIME     (1u << 8)

/* Generic type and mode fields */
enum fs_file_type_e {
    fs_file_unknown = 0,
    fs_file_regular,
    fs_file_directory,
    fs_file_symlink,
    fs_file_char_device,
    fs_file_block_device,
    fs_file_fifo,
    fs_file_socket
};

struct fs_stat_generic_s {
    /* valid field's bits determines which variables are valid to use */
    u32 valid;
    u32 __pad;

    u64 dev;
    u64 ino;
    u64 nlink;

    /* Same as enum fs_file_type_e type */
    u32 type;
    u32 perm;

    u32 uid;
    u32 gid;

    u64 rdev;

    s64 size;
    s64 blksize;
    s64 blocks;

    struct timestamp_s atime;
    struct timestamp_s mtime;
    struct timestamp_s ctime;
    struct timestamp_s btime;
};

/* Generic Unix-style permission bits. */
#define FS_STAT_MODE_UR  0x0001
#define FS_STAT_MODE_UW  0x0002
#define FS_STAT_MODE_UX  0x0004

#define FS_STAT_MODE_GR  0x0008
#define FS_STAT_MODE_GW  0x0010
#define FS_STAT_MODE_GX  0x0020

#define FS_STAT_MODE_OR  0x0040
#define FS_STAT_MODE_OW  0x0080
#define FS_STAT_MODE_OX  0x0100

struct std_s;

typedef void* (*f_std_thread_func)(struct std_s *, void *);
typedef void* (*f_thread_func)(void *);

#endif /* __OS_H__ */

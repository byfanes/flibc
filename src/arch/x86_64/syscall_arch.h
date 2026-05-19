#ifndef __FLIBC_SYSCALL_ARCH__
#define __FLIBC_SYSCALL_ARCH__

#ifdef __cplusplus
extern "C" {
#endif

#include "features.h"
#include "stdtypes.h"

#ifdef __linux__

/* Linux syscalls functions written in assembly this is for linking */
extern ssize_t syscall_0_linux
(ssize_t num);
extern ssize_t syscall_1_linux
(ssize_t num, ssize_t arg1);
extern ssize_t syscall_2_linux
(ssize_t num, ssize_t arg1, ssize_t arg2);
extern ssize_t syscall_3_linux
(ssize_t num, ssize_t arg1, ssize_t arg2, ssize_t arg3);
extern ssize_t syscall_4_linux
(ssize_t num, ssize_t arg1, ssize_t arg2, ssize_t arg3, ssize_t arg4);
extern ssize_t syscall_5_linux
(ssize_t num, ssize_t arg1, ssize_t arg2, ssize_t arg3, ssize_t arg4, ssize_t arg5);
extern ssize_t syscall_6_linux
(ssize_t num, ssize_t arg1, ssize_t arg2, ssize_t arg3, ssize_t arg4, ssize_t arg5, ssize_t arg6);

#define MAX_PATH 4096

#define syscall_read 0
#define syscall_write 1
#define syscall_open 2
#define syscall_close 3
#define syscall_stat 4
#define syscall_lseek 8
#define syscall_mmap 9
#define syscall_munmap 11
#define syscall_nanosleep 35
#define syscall_fork 57
#define syscall_execve 59
#define syscall_exit 60
#define syscall_wait4 61
#define syscall_getcwd 79
#define syscall_chdir 80
#define syscall_rename 82
#define syscall_mkdir 83
#define syscall_rmdir 84
#define syscall_unlink 87
#define syscall_gettime 228

#define S_IFREG 0100000
#define S_IFDIR 0040000

#define UNIX_STDIN 0
#define UNIX_STDOUT 1
#define UNIX_STDERR 2

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define MMAP_FAILED (void*)-1
#define MAP_PRIVATE 0x02
#define MAP_ANONYMOUS 0x20

#define PROT_NONE 0
#define PROT_READ 1
#define PROT_WRITE 2
#define PROT_EXEC 4

#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR 2
#define O_CREAT 64
#define O_TRUNC 512
#define O_APPEND 1024

#define S_IRUSR 256
#define S_IWUSR 128
#define S_IRGRP 32
#define S_IWGRP 16
#define S_IROTH 4
#define S_IWOTH 2

#define CLOCK_MONOTONIC 1

#else /* __linux__ */
#error "Unsupported OS"
#endif /* __linux__ */

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_SYSCALL_ARCH__ */

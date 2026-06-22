#ifndef __FLIBC_SYSCALL_ARCH__
#define __FLIBC_SYSCALL_ARCH__

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"
#include "syscall.h"

#ifdef __linux__

/* Linux syscalls functions written in assembly this is for linking */
extern ssz syscall_6_linux
(ssz num, ssz r1, ssz r2, ssz r3, ssz r4, ssz r5, ssz r6);

ssz syscall_0_linux
(ssz num);

ssz syscall_1_linux
(ssz num, ssz r1);

ssz syscall_2_linux
(ssz num, ssz r1, ssz r2);

ssz syscall_3_linux
(ssz num, ssz r1, ssz r2, ssz r3);

ssz syscall_4_linux
(ssz num, ssz r1, ssz r2, ssz r3, ssz r4);

ssz syscall_5_linux
(ssz num, ssz r1, ssz r2, ssz r3, ssz r4, ssz r5);

#define MAX_PATH 4096

#define syscall_read        0
#define syscall_write       1
#define syscall_open        2
#define syscall_close       3
#define syscall_stat        4
#define syscall_lseek       8
#define syscall_exit        60
#define syscall_fork        57
#define syscall_execve      59
#define syscall_wait4       61

#define syscall_mmap        9
#define syscall_munmap      11

#define syscall_access      21
#define syscall_getcwd      79
#define syscall_chdir      80
#define syscall_rename     82
#define syscall_mkdir      83
#define syscall_rmdir      84
#define syscall_unlink     87
#define syscall_openat     257
#define syscall_getdents64 217

#define syscall_sched_yield 24
#define syscall_nanosleep   35
#define syscall_gettime     228
#define CLOCK_MONOTONIC     1

#define syscall_futex      202

#define syscall_socket     41
#define syscall_connect    42
#define syscall_accept     43
#define syscall_bind       49
#define syscall_listen     50

#define UNIX_STDIN 0
#define UNIX_STDOUT 1
#define UNIX_STDERR 2

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define MAP_PRIVATE 0x02
#define MAP_ANONYMOUS 0x20

#define PROT_NONE 0
#define PROT_READ 1
#define PROT_WRITE (1 << 1)
#define PROT_EXEC (1 << 2)

#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR (1 << 1)
#define O_CREAT (1 << 6)
#define O_TRUNC (1 << 9)
#define O_APPEND (1 << 10)
#define O_CLOEXEC (1 << 19)
#define O_DIRECTORY (1 << 16)

#define S_IRUSR (1 << 8)
#define S_IWUSR (1 << 7)
#define S_IRGRP (1 << 5)
#define S_IWGRP (1 << 4)
#define S_IROTH (1 << 2)
#define S_IWOTH (1 << 1)

#define S_IFMT  0170000

#define S_IFDIR 0040000
#define S_IFCHR 0020000
#define S_IFBLK 0060000
#define S_IFREG 0100000
#define S_IFIFO 0010000
#define S_IFLNK 0120000
#define S_IFSOCK 0140000

#define S_TYPEISMQ(buf)  0
#define S_TYPEISSEM(buf) 0
#define S_TYPEISSHM(buf) 0
#define S_TYPEISTMO(buf) 0

#define S_ISDIR(mode)  (((mode) & S_IFMT) == S_IFDIR)
#define S_ISCHR(mode)  (((mode) & S_IFMT) == S_IFCHR)
#define S_ISBLK(mode)  (((mode) & S_IFMT) == S_IFBLK)
#define S_ISREG(mode)  (((mode) & S_IFMT) == S_IFREG)
#define S_ISFIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#define S_ISLNK(mode)  (((mode) & S_IFMT) == S_IFLNK)
#define S_ISSOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)

#define SOCK_CLOEXEC 0x80000

#define FUTEX_WAIT 0
#define FUTEX_WAKE 1

#define CLONE_VM        0x00000100
#define CLONE_FS        0x00000200
#define CLONE_FILES     0x00000400
#define CLONE_SIGHAND   0x00000800
#define CLONE_THREAD    0x00010000

#define THREAD_FLAGS (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD)

#define AT_FDCWD        -100
#define DT_REG          8
#define DT_DIR          4
#define F_OK 0

#define EINTR 4
#define EAGAIN 11

#define CLOCK_MONOTONIC 1

/* Forward declaration */
struct std_s;
struct thread_s;

/* For threads and this needs to be implemented in assembly */
extern ssz thread_clone_linux
(ssz flags, void *child_stack, void* (*fn)(struct std_s* std, void*),
 struct std_s* std, void *arg);

#else /* __linux__ */
#error "Unsupported OS"
#endif /* __linux__ */

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_SYSCALL_ARCH__ */

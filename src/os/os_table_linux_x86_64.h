#ifndef __OS_LINUX_TABLE_X86_64_H__
#define __OS_LINUX_TABLE_X86_64_H__

#if SYS_OS != SYS_OS_LINUX
#error "Linux syscall codes included on a non-Linux platform"
#endif

#if SYS_ARCH != SYS_ARCH_X86_64
#error "x86-64 Linux syscall codes included on a non-x86-64 architecture"
#endif

/* Linux syscalls functions written in assembly this is for linking */
extern ssz syscall_0_linux
(ssz num);

extern ssz syscall_1_linux
(ssz num, ssz r1);

extern ssz syscall_2_linux
(ssz num, ssz r1, ssz r2);

extern ssz syscall_3_linux
(ssz num, ssz r1, ssz r2, ssz r3);

extern ssz syscall_4_linux
(ssz num, ssz r1, ssz r2, ssz r3, ssz r4);

extern ssz syscall_5_linux
(ssz num, ssz r1, ssz r2, ssz r3, ssz r4, ssz r5);

extern ssz syscall_6_linux
(ssz num, ssz r1, ssz r2, ssz r3, ssz r4, ssz r5, ssz r6);

/* Standard unix io descriptors */
#define UNIX_STDIN  ((os_fid_t) 0)
#define UNIX_STDOUT ((os_fid_t) 1)
#define UNIX_STDERR ((os_fid_t) 2)

/* Thread stack size for allocating new memory */
/* 2 MB */
#define THREAD_STACK_SIZE 1024*1024*2

#define MAX_PATH 4096

/* Errno list */
#define MAX_ERRNO 4095

#define EPERM             1
#define ENOENT            2
#define EINTR             4
#define EIO               5
#define ENXIO             6
#define EBADF             9
#define EAGAIN           11
#define ENOMEM           12
#define EACCES           13
#define EFAULT           14
#define EBUSY            16
#define ENOTDIR          20
#define EISDIR           21
#define EINVAL           22
#define ENFILE           23
#define EMFILE           24
#define EFBIG            27
#define ENOSPC           28
#define ESPIPE           29
#define EROFS            30
#define EPIPE            32
#define ENAMETOOLONG     36
#define ELOOP            40
#define EOVERFLOW        75
#define EDQUOT          122

#define EWOULDBLOCK EAGAIN

/* Syscall list */
#define syscall_read          0
#define syscall_write         1
#define syscall_open          2
#define syscall_close         3
#define syscall_lseek         8
#define syscall_mmap          9
#define syscall_munmap       11

#define syscall_sched_yield  24
#define syscall_nanosleep    35

#define syscall_exit         60
#define syscall_getcwd       79
#define syscall_rename       82
#define syscall_mkdir        83
#define syscall_rmdir        84
#define syscall_unlink       87

#define syscall_futex       202
#define syscall_getdents64  217
#define syscall_gettime     228
#define syscall_openat      257

/* openat access types and modes */
#define AT_FDCWD -100
#define DT_REG      8
#define DT_DIR      4
#define F_OK        0

/* clock types */
#define CLOCK_MONOTONIC 1

/* thread flags */
#define CLONE_VM        0x00000100
#define CLONE_FS        0x00000200
#define CLONE_FILES     0x00000400
#define CLONE_SIGHAND   0x00000800
#define CLONE_THREAD    0x00010000

#define THREAD_FLAGS (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_THREAD)

/* futex operations */
#define FUTEX_WAIT 0
#define FUTEX_WAKE 1

/* mmap flags list */
#define MAP_PRIVATE   0x02
#define MAP_ANONYMOUS 0x20

/* mmap prot list */
#define PROT_NONE  (0 << 0)
#define PROT_READ  (1 << 0)
#define PROT_WRITE (1 << 1)
#define PROT_EXEC  (1 << 2)

/* open flags list */
#define O_RDONLY    (0 <<  0)
#define O_WRONLY    (1 <<  0)
#define O_RDWR      (1 <<  1)
#define O_CREAT     (1 <<  6)
#define O_TRUNC     (1 <<  9)
#define O_APPEND    (1 << 10)
#define O_CLOEXEC   (1 << 19)
#define O_DIRECTORY (1 << 16)

/* macros for pid returns */
#define WEXITSTATUS(s) (((s) & 0xff00) >> 8)
#define WTERMSIG(s) ((s) & 0x7f)
#define WSTOPSIG(s) WEXITSTATUS(s)
#define WIFEXITED(s) (!WTERMSIG(s))
#define WIFSTOPPED(s) ((short)((((s)&0xffff)*0x10001U)>>8) > 0x7f00)
#define WIFSIGNALED(s) (((s)&0xffff)-1U < 0xffu)

/* Struct definitions */
typedef struct linux_dirent64_s linux_dirent64_t;
struct linux_dirent64_s {
    u64 d_ino;
    i64 d_off;
    u16 d_reclen;
    u8 d_type;
    char d_name[1];
};

/* Forward declaration */
struct std_s;
struct thread_s;

/* For threads and this needs to be implemented in assembly */
extern ssz __thread_clone_linux
(ssz flags, void *child_stack, void* (*fn)(struct std_s* std, void*),
 struct std_s* std, void *arg);


#endif /* __OS_LINUX_TABLE_X86_64_H__ */

#ifndef __FLIBC_SYSCALL_H__
#define __FLIBC_SYSCALL_H__

#include "features.h"
#include "stdtypes.h"

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
#error "Only Unix Is Supported Right Now !"
#endif

INTERNAL arch_t syscall_0
(arch_t num)
{
    register arch_t _rax __asm__("rax") = num;
    __asm__ volatile (
        "syscall"
        : "+r" (_rax)
        :
        : "rcx", "r11", "memory"
    );
    return _rax;
}

INTERNAL arch_t syscall_1
(arch_t num, arch_t arg1)
{
    register arch_t _rax __asm__("rax") = num;
    register arch_t _rdi __asm__("rdi") = arg1;
    __asm__ volatile (
        "syscall"
        : "+r" (_rax)
        : "r" (_rdi)
        : "rcx", "r11", "memory"
    );
    return _rax;
}

INTERNAL arch_t syscall_2
(arch_t num, arch_t arg1, arch_t arg2)
{
    register arch_t _rax __asm__("rax") = num;
    register arch_t _rdi __asm__("rdi") = arg1;
    register arch_t _rsi __asm__("rsi") = arg2;
    __asm__ volatile (
        "syscall"
        : "+r" (_rax)
        : "r" (_rdi), "r" (_rsi)
        : "rcx", "r11", "memory"
    );
    return _rax;
}

INTERNAL arch_t syscall_3
(arch_t num, arch_t arg1, arch_t arg2, arch_t arg3)
{
    register arch_t _rax __asm__("rax") = num;
    register arch_t _rdi __asm__("rdi") = arg1;
    register arch_t _rsi __asm__("rsi") = arg2;
    register arch_t _rdx __asm__("rdx") = arg3;
    __asm__ volatile (
        "syscall"
        : "+r" (_rax)
        : "r" (_rdi), "r" (_rsi), "r" (_rdx)
        : "rcx", "r11", "memory"
    );
    return _rax;
}

INTERNAL arch_t syscall_4
(arch_t num, arch_t arg1, arch_t arg2, arch_t arg3, arch_t arg4)
{
    register arch_t _rax __asm__("rax") = num;
    register arch_t _rdi __asm__("rdi") = arg1;
    register arch_t _rsi __asm__("rsi") = arg2;
    register arch_t _rdx __asm__("rdx") = arg3;
    register arch_t _r10 __asm__("r10") = arg4;
    __asm__ volatile (
        "syscall"
        : "+r" (_rax)
        : "r" (_rdi), "r" (_rsi), "r" (_rdx), "r" (_r10)
        : "rcx", "r11", "memory"
    );
    return _rax;
}

INTERNAL arch_t syscall_5
(arch_t num, arch_t arg1, arch_t arg2,
 arch_t arg3, arch_t arg4, arch_t arg5)
{
    register arch_t _rax __asm__("rax") = num;
    register arch_t _rdi __asm__("rdi") = arg1;
    register arch_t _rsi __asm__("rsi") = arg2;
    register arch_t _rdx __asm__("rdx") = arg3;
    register arch_t _r10 __asm__("r10") = arg4;
    register arch_t _r8  __asm__("r8")  = arg5;
    __asm__ volatile (
        "syscall"
        : "+r" (_rax)
        : "r" (_rdi), "r" (_rsi), "r" (_rdx), "r" (_r10), "r" (_r8)
        : "rcx", "r11", "memory"
    );
    return _rax;
}

INTERNAL arch_t syscall_6
(arch_t num, arch_t arg1, arch_t arg2, arch_t arg3,
 arch_t arg4, arch_t arg5, arch_t arg6)
{
    register arch_t _rax __asm__("rax") = num;
    register arch_t _rdi __asm__("rdi") = arg1;
    register arch_t _rsi __asm__("rsi") = arg2;
    register arch_t _rdx __asm__("rdx") = arg3;
    register arch_t _r10 __asm__("r10") = arg4;
    register arch_t _r8  __asm__("r8")  = arg5;
    register arch_t _r9  __asm__("r9")  = arg6;
    __asm__ volatile (
        "syscall"
        : "+r" (_rax)
        : "r" (_rdi), "r" (_rsi), "r" (_rdx), "r" (_r10), "r" (_r8), "r" (_r9)
        : "rcx", "r11", "memory"
    );
    return _rax;
}

#define syscall_read 0
#define syscall_write 1
#define syscall_open 2
#define syscall_close 3
#define syscall_lseek 8

#define syscall_mmap 9
#define syscall_munmap 11
#define syscall_exit 60

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
#define PROT_EXEC 3

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

#endif /* __FLIBC_SYSCALL_H__ */

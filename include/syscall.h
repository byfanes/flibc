#ifndef __FLIBC_SYSCALL_H__
#define __FLIBC_SYSCALL_H__

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
#error "Only Unix Is Supported Right Now !"
#endif

#define syscall_0(num) ({ \
    register long _rax __asm__("rax") = (long)(num); \
    __asm__ volatile ( \
        "syscall" \
        : "+r" (_rax) \
        : \
        : "rcx", "r11", "memory" \
    ); \
    _rax; \
})

#define syscall_1(num, arg1) ({ \
    register long _rax __asm__("rax") = (long)(num); \
    register long _rdi __asm__("rdi") = (long)(arg1); \
    __asm__ volatile ( \
        "syscall" \
        : "+r" (_rax) \
        : "r" (_rdi) \
        : "rcx", "r11", "memory" \
    ); \
    _rax; \
})

#define syscall_2(num, arg1, arg2) ({ \
    register long _rax __asm__("rax") = (long)(num); \
    register long _rdi __asm__("rdi") = (long)(arg1); \
    register long _rsi __asm__("rsi") = (long)(arg2); \
    __asm__ volatile ( \
        "syscall" \
        : "+r" (_rax) \
        : "r" (_rdi), "r" (_rsi) \
        : "rcx", "r11", "memory" \
    ); \
    _rax; \
})

#define syscall_3(num, arg1, arg2, arg3) ({ \
    register long _rax __asm__("rax") = (long)(num); \
    register long _rdi __asm__("rdi") = (long)(arg1); \
    register long _rsi __asm__("rsi") = (long)(arg2); \
    register long _rdx __asm__("rdx") = (long)(arg3); \
    __asm__ volatile ( \
        "syscall" \
        : "+r" (_rax) \
        : "r" (_rdi), "r" (_rsi), "r" (_rdx) \
        : "rcx", "r11", "memory" \
    ); \
    _rax; \
})

#define syscall_4(num, arg1, arg2, arg3, arg4) ({ \
    register long _rax __asm__("rax") = (long)(num); \
    register long _rdi __asm__("rdi") = (long)(arg1); \
    register long _rsi __asm__("rsi") = (long)(arg2); \
    register long _rdx __asm__("rdx") = (long)(arg3); \
    register long _r10 __asm__("r10") = (long)(arg4); \
    __asm__ volatile ( \
        "syscall" \
        : "+r" (_rax) \
        : "r" (_rdi), "r" (_rsi), "r" (_rdx), "r" (_r10) \
        : "rcx", "r11", "memory" \
    ); \
    _rax; \
})

#define syscall_5(num, arg1, arg2, arg3, arg4, arg5) ({ \
    register long _rax __asm__("rax") = (long)(num); \
    register long _rdi __asm__("rdi") = (long)(arg1); \
    register long _rsi __asm__("rsi") = (long)(arg2); \
    register long _rdx __asm__("rdx") = (long)(arg3); \
    register long _r10 __asm__("r10") = (long)(arg4); \
    register long _r8  __asm__("r8")  = (long)(arg5); \
    __asm__ volatile ( \
        "syscall" \
        : "+r" (_rax) \
        : "r" (_rdi), "r" (_rsi), "r" (_rdx), "r" (_r10), "r" (_r8) \
        : "rcx", "r11", "memory" \
    ); \
    _rax; \
})

#define syscall_6(num, arg1, arg2, arg3, arg4, arg5, arg6) ({ \
    register long _rax __asm__("rax") = (long)(num); \
    register long _rdi __asm__("rdi") = (long)(arg1); \
    register long _rsi __asm__("rsi") = (long)(arg2); \
    register long _rdx __asm__("rdx") = (long)(arg3); \
    register long _r10 __asm__("r10") = (long)(arg4); \
    register long _r8  __asm__("r8")  = (long)(arg5); \
    register long _r9  __asm__("r9")  = (long)(arg6); \
    __asm__ volatile ( \
        "syscall" \
        : "+r" (_rax) \
        : "r" (_rdi), "r" (_rsi), "r" (_rdx), "r" (_r10), "r" (_r8), "r" (_r9) \
        : "rcx", "r11", "memory" \
    ); \
    _rax; \
})

#define syscall_mmap 9
#define syscall_munmap 11
#define syscall_exit 60

#define MMAP_FAILED (void*)-1
#define MAP_PRIVATE 0x02
#define MAP_ANONYMOUS 0x20
#define PROT_NONE 0
#define PROT_READ 1
#define PROT_WRITE 2
#define PROT_EXEC 3

#endif /* __FLIBC_SYSCALL_H__ */

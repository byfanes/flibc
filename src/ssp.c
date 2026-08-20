#include "error.h"
#include "base.h"
#include "std.h"
#include "memory.h"
#include "os/os_private.h"
#include "helpers/helpers.h"

extern uintptr_t __stack_chk_guard;
extern u64 __flibc_hardware_random(void);
extern uintptr_t __flibc_fallback_random_by_time_and_sp(void);

#if __SIZEOF_POINTER__ == 4
uintptr_t __stack_chk_guard = 0xe2dee396;         /* 32-bit */
#else
uintptr_t __stack_chk_guard = 0x595e9fbd94fda766; /* 64-bit */
#endif

noreturn __stack_chk_fail(void);
void __flibc_stack_chk_init(s32 argc, char **argv);

noreturn __stack_chk_fail
(void)
{
    __helper_panic("Stack smashing detected. The program will now terminate.\n");
}

void __flibc_stack_chk_init
(s32 argc, char **argv)
{
    u64 hw_rand = 0;

    /* First Method: If were on linux or linux-like system we will try to use AT_RANDOM value */
    #if SYS_OS == SYS_OS_LINUX || SYS_OS == SYS_OS_UNIX
    #define AT_RANDOM 25
    uintptr_t *auxv = nullptr, at_random_ptr = null;
    char** auxv_ptr = argc + argv + 1;

    /* Skip the envp and argv and the null at the end */
    while(*auxv_ptr++);
    auxv = (uintptr_t *)auxv_ptr;

    /* Iterate and look for AT_RANDOM */
    while(*auxv) {
        if(auxv[0] != AT_RANDOM) { auxv += 2; continue; }
        at_random_ptr = auxv[1];
        if(at_random_ptr) {
            /* This address might not be aligned better to use mem_copy_raw */
            mem_copy_raw(&__stack_chk_guard, (const void *)at_random_ptr, sizeof(__stack_chk_guard));
            /* We found it and set it now we can continue */
            return;
        }
    }
    #else
    /* For other platforms argc and argv are unused */
    (void)argc;
    (void)argv;
    #endif

    /* Second try: We will try with cpu's random generation */
    hw_rand = __flibc_hardware_random();
    if(hw_rand != 0) {
        __stack_chk_guard = hw_rand;
    } else {
        /* Last One: We could not use hardware random now try it with time */
        __stack_chk_guard = __flibc_fallback_random_by_time_and_sp();
    }
}

#include "stdtypes.h"

/* 
 * The "canary" value. 
 * In a real OS, you would randomize this value at program startup.
 * For now, we just use a hardcoded random-looking number.
 */
#if __SIZEOF_POINTER__ == 4
uintptr_t __stack_chk_guard = 0xe2dee396;         /* 32-bit */
#else
uintptr_t __stack_chk_guard = 0x595e9fbd94fda766; /* 64-bit */
#endif

/* 
 * The function GCC calls when a buffer overflow occurs.
 */
void __stack_chk_fail(void) 
{
    /* 
     * A buffer overflow happened! The program is unsafe to continue.
     * Since you don't have printf yet, the easiest way to crash safely
     * is an infinite loop or a sys_exit system call.
     */
     
    /* Option A: Infinite loop (Hangs the program) */
    while (1) {}

    /* Option B: Linux x86_64 sys_exit (Aborts immediately) */
    /*
    __asm__ volatile (
        "mov $60, %%rax\n"
        "mov $134, %%rdi\n" // Exit code 134 usually means Abort
        "syscall\n"
        ::: "rax", "rdi"
    );
    */
}

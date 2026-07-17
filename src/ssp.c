#include "error.h"
#include "base.h"
#include "std.h"

extern uintptr_t __stack_chk_guard;

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

noreturn __stack_chk_fail(void);

/* Todo Make it use random 16 bytes which is given by linux
 * The function GCC calls when a buffer overflow occurs.
 */
noreturn __stack_chk_fail(void)
{
    std_abort(ssp_fail);
}

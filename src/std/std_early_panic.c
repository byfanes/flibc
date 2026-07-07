#include "std_private.h"

_Noreturn void __std_early_panic
(const char* msg)
{
    /* Ignore its failure because we will close the program after it */
    syscall_3_linux(syscall_write, UNIX_STDERR, (ssz)msg, (ssz)cstr_len(msg));
    syscall_1_linux(syscall_exit, 255);
    __unreachable();
}

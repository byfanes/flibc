#include "std_private.h"

_Noreturn void abort
(void)
{
    syscall_1_linux(syscall_exit, 1);
    __unreachable();
}

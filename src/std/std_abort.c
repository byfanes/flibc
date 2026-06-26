#include "std_private.h"

_Noreturn void std_abort
(ssz code)
{
    syscall_1_linux(syscall_exit, code);
    __unreachable();
}

#include "stdlib.h"
#include "syscall.h"

_Noreturn void exit
(ssz code)
{
    syscall_1_linux(syscall_exit, code);
    __unreachable();
}

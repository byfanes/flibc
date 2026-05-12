#include "stdlib.h"
#include "syscall.h"

_Noreturn void abort
(void)
{
    syscall_1(syscall_exit,1);
    __unreachable();
}

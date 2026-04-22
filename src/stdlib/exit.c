#include "stdlib.h"
#include "syscall.h"
#include "features.h"

_Noreturn void exit
(int code)
{
    syscall_1(syscall_exit, (arch_t)code);
    __unreachable();
}

#include "stdlib.h"
#include "syscall.h"
#include "features.h"

_Noreturn void exit
(arch_t code)
{
    syscall_1(syscall_exit, code);
    __unreachable();
}

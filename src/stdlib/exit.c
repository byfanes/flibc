#include "stdlib.h"
#include "syscall.h"

_Noreturn void exit
(ssize_t code)
{
    syscall_1(syscall_exit, code);
    __unreachable();
}

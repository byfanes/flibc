#include "stdlib.h"
#include "syscall.h"

_Noreturn void exit
(ssize_t code)
{
    syscall_1_linux(syscall_exit, code);
    __unreachable();
}

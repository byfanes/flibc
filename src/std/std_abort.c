#include "std_private.h"

noreturn std_abort
(ssz code)
{
    __os_exit(code);
}

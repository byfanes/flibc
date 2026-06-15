#include "syscall_arch.h"

ssz syscall_0_linux
(ssz num)
{ return syscall_6_linux(num, 0, 0, 0, 0, 0, 0); }

ssz syscall_1_linux
(ssz num, ssz r1)
{ return syscall_6_linux(num, r1, 0, 0, 0, 0, 0); }

ssz syscall_2_linux
(ssz num, ssz r1, ssz r2)
{ return syscall_6_linux(num, r1, r2, 0, 0, 0, 0); }

ssz syscall_3_linux
(ssz num, ssz r1, ssz r2, ssz r3)
{ return syscall_6_linux(num, r1, r2, r3, 0, 0, 0); }

ssz syscall_4_linux
(ssz num, ssz r1, ssz r2, ssz r3, ssz r4)
{ return syscall_6_linux(num, r1, r2, r3, r4, 0, 0); }

ssz syscall_5_linux
(ssz num, ssz r1, ssz r2, ssz r3, ssz r4, ssz r5)
{ return syscall_6_linux(num, r1, r2, r3, r4, r5, 0); }

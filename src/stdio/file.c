#include "stdio.h"
#include "syscall.h"

file_t __stdout = {
    .fd = UNIX_STDOUT,
    .buf = {0},
};
file_t* const stdout = &__stdout;

file_t __stdin = {
    .fd = UNIX_STDIN,
    .buf = {0},
};
file_t* const stdin = &__stdin;

file_t __stderr = {
    .fd = UNIX_STDERR,
    .buf = {0},
};
file_t* const stderr = &__stderr;

void __fflush_stdio
(void)
{
    fflush(stdin);
    fflush(stdout);
    fflush(stderr);
}

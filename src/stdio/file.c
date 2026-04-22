#include "stdio.h"
#include "syscall.h"

/* Todo: Null Check */

fc_error_t get_stdout
(file_t* set)
{
    fc_error_t res = fce_success;
    set->fd = UNIX_STDOUT;
    da_init_cap(res, &set->buf, FLIBC_FILE_BUF_SIZE);
    return res;
}

fc_error_t get_stdin
(file_t* set)
{
    fc_error_t res = fce_success;
    set->fd = UNIX_STDIN;
    da_init_cap(res, &set->buf, FLIBC_FILE_BUF_SIZE);
    return res;
}

fc_error_t get_stderr
(file_t* set)
{
    fc_error_t res = fce_success;
    set->fd = UNIX_STDERR;
    da_init_cap(res, &set->buf, FLIBC_FILE_BUF_SIZE);
    return res;
}

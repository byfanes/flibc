#include "helpers.h"

noreturn __panic_len
(const void* msg, usz msg_len)
{
    /* Ignore its failure because we will close the program after it */
    os_fid_t fid = OS_INVALID_FILE_HANDLE;
    __os_file_get_std(&fid, os_file_stderr);
    __os_file_write(fid, msg, msg_len);
    __os_exit(255);
}

#include "helpers.h"

noreturn __panic_len
(const void* msg, usz msg_len)
{
    /* Ignore its failure because we will close the program after it */
    os_fid_t handle = OS_INVALID_FILE_HANDLE;
    __os_file_get_std(&handle, os_file_stderr);
    __os_file_write(handle, msg, msg_len);
    __os_exit(255);
}

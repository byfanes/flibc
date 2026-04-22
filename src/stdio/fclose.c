#include "memory.h"
#include "stdio.h"

fc_error_t fclose
(file_t* file)
{
    fc_error_t res = fce_success;
    da_free(res, &file->buf);
    memset_sized(file, 0, sizeof(file_t));
    /* TODO: Close the file */
    return res;
}

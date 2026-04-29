#ifndef __FLIBC_STDIO_H__
#define __FLIBC_STDIO_H__

#include "error.h"
#include "stdtypes.h"
#include "memory.h"

typedef struct file_s file_t;

fc_error_t fclose(file_t** file);
fc_error_t fopen(const char* name, file_t** out);
fc_error_t fopen_stderr(file_t** out);
fc_error_t fopen_stdout(file_t** out);
fc_error_t fopen_stdin(file_t** out);

fc_error_t fflush(file_t* file);
fc_error_t fwrite(file_t* file, slice_t sl);
fc_error_t fread(file_t* file, slice_t* buf);

#endif /* __FLIBC_STDIO_H__ */

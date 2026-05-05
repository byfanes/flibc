#ifndef __FLIBC_STDIO_H__
#define __FLIBC_STDIO_H__

#include "error.h"
#include "stdtypes.h"
#include "stdarg.h"
#include "memory.h"

typedef struct file_s file_t;

typedef struct stdio_s stdio_t;
struct stdio_s {
    file_t *out, *in, *err;
};

fc_error_t fclose(file_t** file);
fc_error_t fopen(const char* name, file_t** out);
fc_error_t fopen_stderr(file_t** out);
fc_error_t fopen_stdout(file_t** out);
fc_error_t fopen_stdin(file_t** out);

fc_error_t fflush(file_t* file);
fc_error_t fwrite(file_t* file, slice_t sl);
fc_error_t fread(file_t* file, slice_t buf, u32* _Nullable read_count);

fc_error_t sprintf(slice_t buf, u32* _Nullable wrote_count, slice_t fmt, ...);
fc_error_t fprintf(file_t* file, slice_t fmt, ...);

fc_error_t vsprintf(slice_t buf, u32* _Nullable wrote_count, slice_t fmt, va_list ap);
fc_error_t vfprintf(file_t* file, slice_t fmt, va_list ap);


#endif /* __FLIBC_STDIO_H__ */

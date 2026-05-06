#ifndef __FLIBC_STDIO_H__
#define __FLIBC_STDIO_H__

#include "error.h"
#include "stdtypes.h"
#include "stdarg.h"
#include "memory.h"

enum file_type_e {
    file_read,
    file_write,
    file_append,
    file_read_plus,
    file_write_plus,
    file_append_plus
};

enum seek_type_e {
    seek_set,
    seek_cur,
    seek_end
};

typedef enum seek_type_e seek_type_t;
typedef enum file_type_e file_type_t;
typedef struct file_s file_t;
typedef struct stdio_s stdio_t;

struct stdio_s {
    file_t *out, *in, *err;
};

fc_error_t fclose(file_t** file);
fc_error_t fopen(const char* name, file_t** out, file_type_t type);
fc_error_t fopen_stderr(file_t** out);
fc_error_t fopen_stdout(file_t** out);
fc_error_t fopen_stdin(file_t** out);

fc_error_t fflush(file_t* file);
fc_error_t fwrite(file_t* file, slice_t sl);
fc_error_t fread(file_t* file, slice_t buf, u32* _Nullable read_count);

fc_error_t fsetpos(file_t* file, arch_t pos);
fc_error_t fgetpos(file_t* file, arch_t* _Nullable pos);

fc_error_t ftell(file_t* file, arch_t* _Nullable out);
fc_error_t fseek(file_t* file, arch_t off, seek_type_t type, arch_t* _Nullable out);
fc_error_t rewind(file_t* file);

fc_error_t fputs(file_t* file, slice_t sl);
fc_error_t fputc(file_t* file, uint8_t c);

fc_error_t sprintf(slice_t buf, u32* _Nullable wrote_count, slice_t fmt, ...);
fc_error_t fprintf(file_t* file, slice_t fmt, ...);

fc_error_t vsprintf(slice_t buf, u32* _Nullable wrote_count, slice_t fmt, va_list ap);
fc_error_t vfprintf(file_t* file, slice_t fmt, va_list ap);


#endif /* __FLIBC_STDIO_H__ */

#ifndef __FLIBC_STDIO_H__
#define __FLIBC_STDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "error.h"
#include "stdtypes.h"
#include "stdarg.h"
#include "memory.h"
#include "features.h"

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

/* TODO: We might add flags for example skipping mutex and assuming its used in only one thread so */

error_t fclose(file_t** file);
error_t fopen(allocator_t* alloc, const char* name, file_t** out, file_type_t type);
error_t fopen_stderr(allocator_t* alloc, file_t** out);
error_t fopen_stdout(allocator_t* alloc, file_t** out);
error_t fopen_stdin(allocator_t* alloc, file_t** out);

error_t fflush(file_t* _Nullable file);
error_t __fwrite(file_t* file, void* sl, usize_t el_size);
#define fwrite(file, sl) __fwrite((file), ptr_meta(sl))
error_t __fread(file_t* file, void* buf, usize_t el_size, u32* _Nullable read_count);
#define fread(file, buf, read_count) __fread((file), ptr_meta(buf), (read_count))

error_t fsetpos(file_t* file, usize_t pos);
error_t fgetpos(file_t* file, usize_t* _Nullable pos);

error_t ftell(file_t* file, usize_t* out);
error_t fseek(file_t* file, usize_t off, seek_type_t type, usize_t* _Nullable out);
error_t rewind(file_t* file);

error_t __fputs(file_t* file, void* sl, usize_t el_size);
#define fputs(file, sl) __fputs((file), ptr_meta(sl))
error_t fputc(file_t* file, uint8_t c);

error_t sprintf(sl_u8_t buf, usize_t* _Nullable wrote_count, const char* fmt, ...);
error_t sprintf_sl(sl_u8_t buf, usize_t* _Nullable wrote_count, sl_u8_t fmt, ...);

error_t fprintf(file_t* file, const char* fmt, ...);
error_t fprintf_sl(file_t* file, sl_u8_t fmt, ...);

error_t vsprintf(sl_u8_t buf, usize_t* _Nullable wrote_count, const char* fmt, va_list ap);
error_t vsprintf_sl(sl_u8_t buf, usize_t* _Nullable wrote_count, sl_u8_t fmt, va_list ap);

error_t vfprintf(file_t* file, const char* fmt, va_list ap);
error_t vfprintf_sl(file_t* file, sl_u8_t fmt, va_list ap);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_STDIO_H__ */

#ifndef __FLIBC_IO_H__
#define __FLIBC_IO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "error.h"
#include "base.h"
#include "memory.h"
#include "os.h"

typedef enum seek_type_e seek_type_t;
typedef enum file_type_e file_type_t;
typedef struct file_s file_t;
typedef struct io_s io_t;

struct io_s {
    file_t *out, *in, *err;
};

/* TODO: We might add flags for example skipping mutex and assuming its used in only one thread so */

error_t io_close(file_t** file);
error_t io_open(allocator_t* alloc, const char* name, file_t** out, file_type_t type);
error_t io_open_stderr(allocator_t* alloc, file_t** out);
error_t io_open_stdout(allocator_t* alloc, file_t** out);
error_t io_open_stdin(allocator_t* alloc, file_t** out);

error_t io_flush(file_t* _Nullable file);
error_t __io_write(file_t* file, const void* sl, usz el_size);
#define io_write(file, sl) __io_write((file), ptr_meta(sl))
error_t __io_read(file_t* file, void* buf, usz el_size, usz* _Nullable read_count);
#define io_read(file, buf, read_count) __io_read((file), ptr_meta(buf), (read_count))

error_t io_setpos(file_t* file, usz pos);
error_t io_getpos(file_t* file, usz* _Nullable pos);

error_t io_tell(file_t* file, usz* out);
error_t io_seek(file_t* file, usz off, seek_type_t type, usz* _Nullable out);
error_t io_rewind(file_t* file);

#define io_puts(file, sl) __io_write((file), ptr_meta(sl))
error_t io_putc(file_t* file, u8 c);

error_t io_printf(file_t* file, const char* fmt, ...);
error_t io_printf_sl(file_t* file, sl_u8_t fmt, ...);

error_t io_vprintf(file_t* file, const char* fmt, va_list ap);
error_t io_vprintf_sl(file_t* file, sl_u8_t fmt, va_list ap);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_IO_H__ */

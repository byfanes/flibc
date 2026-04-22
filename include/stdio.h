#ifndef __FLIBC_STDIO_H__
#define __FLIBC_STDIO_H__

#include "error.h"
#include "stdtypes.h"
#include "memory.h"
#include "stdarg.h"
#include "da.h"

#define FLIBC_FILE_BUF_SIZE 4096

struct file_s {
    uint32_t fd;
    da(byte_t) buf;
};

typedef struct file_s file_t;

fc_error_t get_stdout(file_t* set);
fc_error_t get_stdin(file_t* set);
fc_error_t get_stderr(file_t* set);

fc_error_t fclose(file_t* file);
fc_error_t fwrite(file_t* file,def_slice_t buf);
fc_error_t fflush(file_t* file);

def_slice_t fmt_from_cstr(const char* str);

fc_error_t vsprintf_sl(def_slice_t buf, def_slice_t fmt, va_list va);
fc_error_t vprintf_sl(def_slice_t fmt, va_list va);
fc_error_t vfprintf_sl(file_t* file, def_slice_t fmt, va_list va);

fc_error_t sprintf_sl(def_slice_t buf, def_slice_t fmt, ...);
fc_error_t printf_sl(def_slice_t fmt, ...);
fc_error_t fprintf_sl(file_t* file, def_slice_t fmt, ...);

fc_error_t sprintf(def_slice_t buf,const char* fmt, ...);
fc_error_t printf(const char* fmt, ...);
fc_error_t fprintf(file_t* file,const char* fmt, ...);


#endif /* __FLIBC_STDIO_H__ */

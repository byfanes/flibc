
#include "stdio.h"
#include "error.h"
#include "stdtypes.h"
#include "memory.h"
#include "stdarg.h"

extern fc_error_t __printf_size(def_slice_t fmt, fc_args_t args, uint32_t* out);
extern fc_error_t __printf_format(def_slice_t buf,def_slice_t fmt, fc_args_t args);

fc_error_t vsprintf
(def_slice_t buf,def_slice_t fmt, fc_args_t args)
{
    uint32_t needed = 0;
    fc_error_t res = fce_success;
    if((res = __printf_size(fmt,args,&needed))) { return res; }
    if(needed > buf.len) { return fce_printf_small_buffer; }
    return __printf_format(buf,fmt,args);
}

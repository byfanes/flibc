#include "stdio.h"
#include "error.h"
#include "stdtypes.h"
#include "memory.h"
#include "stdarg.h"
#include "syscall.h"

fc_error_t __printf_size(def_slice_t fmt, uint32_t* out, va_list va);
uint32_t len_of_hex(uint64_t num);
uint32_t len_of_decimal(uint64_t num);

uint32_t len_of_hex
(uint64_t num)
{
    uint32_t count = 0;
    if(num == 0) {count++;}
    while(num) { count++; num /= 16; }
    return count;
}

uint32_t len_of_decimal
(uint64_t num)
{
    uint32_t count = 0;
    if(num == 0) {count++;}
    while(num) { count++; num /= 10; }
    return count;
}

fc_error_t __printf_size
(def_slice_t fmt, uint32_t* out, va_list va)
{
    uint32_t i = 0, count = 0, str_i = 0;
    char* cur_ptr = 0;
    uint64_t cur_u64 = 0;
    int64_t cur_i64 = 0;
    bool long_num = false;
    if(!fmt.base || !out) { return fce_printf_nullptr; }
    *out = 0;
    for(;i < fmt.count; ++i) {
        if(fmt.base[i] != '%') { count++; continue; }
        i++; long_num = false;
        if(i >= fmt.count) { return fce_printf_invalid_format; }
        /* Handle percentage symbol */
        if(fmt.base[i] == '%') { count++; }

        /* Handle single char */
        else if(fmt.base[i] == 'c') { count++; }

        /* Check for long number(8-bytes) and double 'l' */
        else if(fmt.base[i] == 'l') { i++;long_num = true; }
        else if(fmt.base[i] == 'l') { i++;long_num = true; }

        /* Handle %lld / %ld / %d or %lli / %li / %i for signed decimal integers */
        else if(fmt.base[i] == 'd' || fmt.base[i] == 'i') {
            if(long_num) { cur_i64 = va_arg(va, int64_t);}
            else { cur_i64 = va_arg(va, int32_t); }
            if(cur_i64 < 0) { count++; cur_i64 = -cur_i64;}
            count += len_of_decimal((uint64_t)cur_i64);
        }

        /* Handle %llu / %lu / %u unsigned decimal integer */
        else if(fmt.base[i] == 'u') {
            if(long_num) { cur_u64 = va_arg(va, uint64_t);}
            else { cur_u64 = va_arg(va, uint32_t);}
            count += len_of_decimal(cur_u64);
        }

        /* Todo: Handle %o unsigned octal */
        else if(fmt.base[i] == 'o') { }
        
        /* Handle %llx / %lx / %x or %llX / %llX / %X unsigned hexadecimal integer */
        else if(fmt.base[i] == 'x' || fmt.base[i] == 'X') {
            if(long_num) { cur_u64 = va_arg(va, uint64_t);}
            else { cur_u64 = va_arg(va, uint32_t);}
            count += len_of_hex(cur_u64);
        }

        /* Handle %p it will write as hexadecimal */
        else if(fmt.base[i] == 'p') {
            cur_ptr = va_arg(va, void*);
            count += len_of_hex((uint64_t)cur_ptr);
        }
        
        /* Todo: Handle %f or %F decimal floating point */
        else if(fmt.base[i] == 'f' || fmt.base[i] == 'F') { }

        /* Handle %s strings */
        else if(fmt.base[i] == 's') {
            cur_ptr = va_arg(va, char*);
            if(cur_ptr) {
                str_i = 0;
                while(cur_ptr[str_i++]) { count++; }
                count--;
            } else {
                count += 6; /* "(null)" */
            }
        }

        else {
            return fce_printf_invalid_format;
        }
    }
    *out = count;
    return fce_success;
}

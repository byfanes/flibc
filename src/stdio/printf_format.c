#include "stdio.h"
#include "stdlib.h"
#include "error.h"
#include "stdtypes.h"
#include "memory.h"
#include "stdarg.h"

fc_error_t __printf_format(def_slice_t buf, def_slice_t fmt, va_list va);
uint32_t write_decimal_to_buf(uint64_t num, char* tmp);
uint32_t write_hex_to_buf(uint64_t num, char* tmp);
void write_num_to_buf(byte_t* start, uint32_t* idx, bool isHex, uint64_t num);

uint32_t write_decimal_to_buf
(uint64_t num, char* tmp)
{
    uint32_t count = 0;
    if(num == 0) { tmp[count++] = '0'; }
    while(num) {
        tmp[count++] = (char)('0' + (num % 10));
        num /= 10;
    };
    return count;
}

uint32_t write_hex_to_buf
(uint64_t num, char* tmp)
{
    uint32_t count = 0;
    static const char hexDigits[] = "0123456789ABCDEF";
    if(num == 0) { tmp[count++] = '0'; }
    while(num) {
        tmp[count++] = hexDigits[num % 16];
        num /= 16;
    };
    return count;
}

void write_num_to_buf
(byte_t* start, uint32_t* idx, bool isHex, uint64_t num)
{
    /* Do not initialize tmp buffer with '= {0}' it does not work with -O3 */
    char tmp[128];
    uint32_t count = 0, i = 0;
    if (isHex) { count = write_hex_to_buf(num, tmp); }
    else { count = write_decimal_to_buf(num, tmp); }
    for(i = 0;i < count; ++i) { start[*idx + i] = (byte_t)tmp[count - 1 - i]; }
    *idx += count;
}

/* This function is an internal function and assumes
 * buf and args are checked via __printf_size function
 */
fc_error_t __printf_format
(def_slice_t buf, def_slice_t fmt, va_list iva)
{
    uint32_t idx = 0, i = 0, str_i = 0;
    char* cur_ptr = 0;
    uint64_t cur_u64 = 0; int64_t cur_i64 = 0;
    bool long_num = false;
    fc_error_t res = fce_success;
    va_list va;
    va_copy(va,iva);
    if (fmt.count == 0) return res;
    for(;i < fmt.count; ++i) {
        if(fmt.base[i] != '%') { buf.base[idx++] = fmt.base[i]; continue; }
        i++;
        if(i >= fmt.count) { return fce_printf_invalid_format; }
        /* Handle percentage symbol */
        if(fmt.base[i] == '%') { buf.base[idx++] = '%'; }

        /* Handle single char */
        else if(fmt.base[i] == 'c') {
            int c = va_arg(va,int);
            buf.base[idx++] = (byte_t)c;
        }
        /* Check for long number(8-bytes) and double 'l' */
        else if(fmt.base[i] == 'l') { i++;long_num = true; }
        else if(fmt.base[i] == 'l') { i++;long_num = true; }
        
        /* Handle %ld / %d or %li / %i for signed decimal integers */
        else if(fmt.base[i] == 'd' || fmt.base[i] == 'i') {
            if(long_num) { cur_i64 = va_arg(va, int64_t);}
            else { cur_i64 = va_arg(va, int32_t); }
            if(cur_i64 < 0) { buf.base[idx++] = '-'; cur_i64 = -cur_i64;}
            write_num_to_buf(buf.base, &idx, false, (uint64_t)cur_i64);
        }

        /* Handle %llu / %lu / %u unsigned decimal integer */
        else if(fmt.base[i] == 'u') {
            if(long_num) { cur_u64 = va_arg(va, uint64_t);}
            else { cur_u64 = va_arg(va, uint32_t);}
            write_num_to_buf(buf.base, &idx, false, (uint64_t)cur_u64);
        }

        /* Todo: Handle %o unsigned octal */
        else if(fmt.base[i] == 'o') { }
        
        /* Handle %llx / %lx / %x or %llX / %llX / %X unsigned hexadecimal integer */
        else if(fmt.base[i] == 'x' || fmt.base[i] == 'X') {
            if(long_num) { cur_u64 = va_arg(va, uint64_t);}
            else { cur_u64 = va_arg(va, uint32_t);}
            write_num_to_buf(buf.base, &idx, true, (uint64_t)cur_u64);
        }

        /* Handle %p it will write as hexadecimal */
        else if(fmt.base[i] == 'p') {
            cur_ptr = va_arg(va, void*);
            write_num_to_buf(buf.base, &idx, true, (uint64_t)cur_ptr);
        }
        
        /* Todo: Handle %f or %F decimal floating point */
        else if(fmt.base[i] == 'f' || fmt.base[i] == 'F') { }

        /* Handle %s strings */
        else if(fmt.base[i] == 's') {
            cur_ptr = va_arg(va, char*);
            if(cur_ptr) {
                str_i = 0;
                while(cur_ptr[str_i]) { buf.base[idx++] = (byte_t)cur_ptr[str_i++]; }
                idx += str_i - 1;
            } else {
                memcpy_sized(&buf.base[idx], (char*)"(null)", 6);
                idx += 6; /* "(null)" */
            }
        }

        else { return fce_printf_unknown; }
    }
    return res;
}

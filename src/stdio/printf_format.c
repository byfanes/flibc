
#include "stdio.h"
#include "stdlib.h"
#include "error.h"
#include "stdtypes.h"
#include "memory.h"
#include "stdarg.h"

uint32_t write_decimal_to_buf
(uint64_t num,char* tmp)
{
    uint32_t count = 0;
    if(num == 0) { tmp[count++] = '0'; }
    while(num) {
        tmp[count++] = '0' + (num % 10);
        num /= 10;
    };
    return count;
}

uint32_t write_hex_to_buf
(uint64_t num,char* tmp)
{
    static const char hexDigits[] = "0123456789ABCDEF";
    uint32_t count = 0;
    if(num == 0) { tmp[count++] = '0'; }
    while(num) {
        tmp[count++] = hexDigits[num % 16];
        num /= 16;
    };
    tmp[count++] = 'x';
    tmp[count++] = '0';
    return count;
}

void write_num_to_buf
(char* start,uint32_t* idx,bool isHex,uint64_t num)
{
    char tmp[128] = {0};
    uint32_t count = 0;
    if (isHex) {
        count = write_hex_to_buf(num,tmp);
    } else {
        count = write_decimal_to_buf(num,tmp);
    }
    uint32_t i = 0;
    for(;i < count; ++i) {
        start[*idx + i] = tmp[count - 1 - i];
    }
    *idx += count;
}

fc_error_t parse_arg
(char* start,uint32_t* idx,fc_arg_t arg,bool isHex)
{
    fc_error_t res = fce_success;
    int64_t num = 0;
    volatile fc_arg_t dbg = arg;
    arg = dbg;
    switch (arg.type) {
        default: case _type_unknown: { return fce_printf_unknown; };
        case _type_i8:  { num = arg.data._i8;  } break;
        case _type_u8:  { num = arg.data._u8;  } break;
        case _type_i16: { num = arg.data._i16; } break;
        case _type_u16: { num = arg.data._u16; } break;
        case _type_i32: { num = arg.data._i32; } break;
        case _type_u32: { num = arg.data._u32; } break;
        case _type_i64: { num = arg.data._i64; } break;
        case _type_char: { start[(*idx)++] = arg.data._char; } return res;
        case _type_char_ptr: {
            char* str = arg.data._cptr;
            uint32_t count = *idx;
            while(*str) { start[count++] = *str; str++;}
            *idx = count;
            return res;
        }
        case _type_u64: { write_num_to_buf(start,idx,isHex,arg.data._u64);} return res;
        case _type_void_ptr: {
            write_num_to_buf(start,idx,true,(uint64_t)arg.data._vptr);
        } return res;
    }
    if(num < 0) { start[(*idx)++] = '-'; num = -num; }
    write_num_to_buf(start,idx,isHex,(uint64_t)num);
    return res;
}

fc_error_t __printf_format
(def_slice_t buf,def_slice_t fmt, fc_args_t args)
{
    char* start = (char*)buf.base;
    uint32_t idx = 0;
    uint32_t arg_i = 0;
    uint32_t i = 0;
    fc_error_t res = fce_success;
    if (fmt.count == 0) return res;
    for(;i + 1 < fmt.count ; ++i) {
        if(fmt.base[i] != '%') { start[idx++] = fmt.base[i]; continue; }
        if(fmt.base[i + 1] == '%') { start[idx++] = '%'; i++; continue; }
        bool isHex = false;
        if(fmt.base[i + 1] == 'x' || fmt.base[i + 1] == 'X') { isHex = true; i++;}
        if((res = parse_arg(start,&idx,args.args[arg_i++],isHex))) { return res; }
    }
    if(fmt.base[i] != '%') {
        start[idx++] = fmt.base[i];
        return res;
    }
    return parse_arg(start,&idx,args.args[arg_i++],false);
}

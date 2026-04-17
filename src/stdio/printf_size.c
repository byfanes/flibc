
#include "stdio.h"
#include "error.h"
#include "stdtypes.h"
#include "memory.h"
#include "stdarg.h"
#include "syscall.h"

uint32_t len_of_num
(uint64_t num,bool isHex)
{
    uint32_t count = 0;
    if(num == 0) {count++;}
    if (isHex) {
        while(num) { count++; num /= 16; }
        count += 2;
    } else {
        while(num) { count++; num /= 10; }
    }
    return count;
}

fc_error_t parse_arg_count
(fc_arg_t arg,bool isHex,uint32_t* out)
{
    *out = 0;
    int64_t num = 0;
    uint32_t count = 0;
    fc_error_t res = fce_success;
    switch (arg.type) {
        default: case _type_unknown: {
            return fce_printf_unknown;
        };
        case _type_char: {
            *out = 1; return res;
        }
        case _type_i8:  { num = arg.data._i8;  } break;
        case _type_u8:  { num = arg.data._u8;  } break;
        case _type_i16: { num = arg.data._i16; } break;
        case _type_u16: { num = arg.data._u16; } break;
        case _type_i32: { num = arg.data._i32; } break;
        case _type_u32: { num = arg.data._u32; } break;
        case _type_i64: { num = arg.data._i64; } break;
        case _type_char_ptr: {
            char* str = arg.data._cptr;
            while(*str) { count++; str++; };
            *out = count;
            return res;
        }
        case _type_u64: { *out = len_of_num(arg.data._u64,isHex); } return res;
        case _type_void_ptr: { *out = len_of_num((uint64_t)arg.data._vptr,true); } return res;
    }
    if(num < 0 && !isHex) { count++; num = -num; }
    *out = len_of_num(num,isHex) + count;
    return res;
}

fc_error_t __printf_size
(def_slice_t fmt, fc_args_t args, uint32_t* out)
{
    uint32_t i = 0;
    uint32_t arg_i = 0;
    uint32_t count = 0;
    uint32_t _out = 0;
    fc_error_t res = fce_success;
    if(!fmt.base || (!args.args && args.count) || !out) { return fce_printf_nullptr; }
    *out = 0;
    for(;i < fmt.count - 1; ++i) {
        if(fmt.base[i] != '%') { count++; continue; }
        if(fmt.base[i + 1] == '%') { count++; i++; continue; }
        bool isHex = false;
        if(fmt.base[i + 1] == 'x' || fmt.base[i + 1] == 'X') { isHex = true; i++;}
        if(arg_i >= args.count) { return fce_printf_need_more_args; }
        if((res = parse_arg_count(args.args[arg_i++],isHex,&_out))) { return res; }
        count += _out;
    }
    if(fmt.base[i] != '%') {
        count++;
    } else {
        if(arg_i >= args.count) { return fce_printf_need_more_args; }
        if((res = parse_arg_count(args.args[arg_i++],false,&_out))) { return res; }
        count += _out;
    }
    if(arg_i != args.count) { return fce_printf_need_less_args; }
    *out = count;
    return fce_success;
}

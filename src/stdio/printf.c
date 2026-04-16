#include "stdio.h"
#include "error.h"
#include "stdtypes.h"
#include "memory.h"
#include "stdarg.h"
#include "syscall.h"

static inline void write_number_to_buf
(uint64_t i,char* tmp,uint32_t* count)
{
    if(i == 0) { tmp[(*count)++] = '0'; }
    while(i) {
        tmp[(*count)++] = '0' + (i % 10);
        i /= 10;
    };
}

static inline void write_hex_to_buf
(uint64_t i,char* tmp,uint32_t* count)
{
    char hexDigits[] = "0123456789ABCDEF";
    if(i == 0) { tmp[(*count)++] = '0'; }
    while(i) {
        tmp[(*count)++] = hexDigits[i % 16];
        i /= 16;
    };
    tmp[(*count)++] = 'x';
    tmp[(*count)++] = '0';
}

static inline fc_error_t alloc_new_buf_ifneeded
(uint32_t idx,uint32_t count,uint32_t* max,char** buf,char* startptr)
{
    fc_error_t res = fce_success;
    if(idx + count < *max ) return res;
    uint32_t news = 2*(idx + count);
    char* ptr = 0;
    if((res = fc_malloc(news,(void**)&ptr))) { return res; }
    if((res = fc_memcpy((def_slice_t){(byte_t*)ptr,news},(def_slice_t){(byte_t*)*buf,idx})))
    { return res; }
    if(*buf != startptr) { if((res = fc_free((void**)buf))) { return res; } }
    *max = news;
    *buf = ptr;
    return res;
}

static inline void write_to_buf
(uint64_t i,char* tmp,uint32_t* count,bool isHex)
{
    if(isHex) {
        write_hex_to_buf(i,tmp,count);
    } else {
        write_number_to_buf(i,tmp,count);
    }
}

fc_error_t parse_arg
(char** buf,uint32_t* idx,uint32_t* max,fc_arg_t arg,char* startptr,bool isHex)
{
    char tmp[64] = {0};
    int64_t num = 0;
    uint32_t count = 0;
    fc_error_t res = fce_success;
    switch (arg.type) {
        default: case _type_unknown: {
            return fce_printf_unknown;
        };
        case _type_char: {
            tmp[count++] = arg.data._char;
        } break;
        case _type_i8:  { num = arg.data._i8;  } break;
        case _type_u8:  { num = arg.data._u8;  } break;
        case _type_i16: { num = arg.data._i16; } break;
        case _type_u16: { num = arg.data._u16; } break;
        case _type_i32: { num = arg.data._i32; } break;
        case _type_u32: { num = arg.data._u32; } break;
        case _type_i64: { num = arg.data._i64; } break;
        case _type_u64: { write_to_buf(arg.data._u64,tmp,&count,isHex); } break;
        case _type_char_ptr: {
            char* str = arg.data._cptr;
            while(*str) {
                if((res = alloc_new_buf_ifneeded(*idx,count,max,buf,startptr)))
                { return res; }
                (*buf)[*idx + count++] = *str;
                str++;
            };
            *idx += count;
            return fce_success;
        }
        case _type_void_ptr: { write_to_buf((uint64_t)arg.data._vptr,tmp,&count,true); } break;
    }

    if (arg.type != _type_u64 && arg.type != _type_char && arg.type != _type_void_ptr) {
        bool sign = false;
        if(num < 0 && !isHex)  { sign = true; num = -num; }
        write_to_buf((uint64_t)num,tmp,&count,isHex);
        if(sign) { tmp[count++] = '-'; }
    }
    if((res = alloc_new_buf_ifneeded(*idx,count,max,buf,startptr))) { return res; }

    for(uint32_t i = 0;i < count;i++) { (*buf)[*idx + i] = tmp[count - 1 - i]; }
    *idx += count;

    return fce_success;
}

fc_error_t __printf
(def_slice_t fmt, fc_arg_t* args, uint32_t count)
{
    (void)args;
    (void)count;
    char buf[FLIBC_STACK_THRESHOLD] = {0};
    uint32_t max = FLIBC_STACK_THRESHOLD;
    uint32_t idx = 0;
    uint32_t arg_i = 0;
    char* tmp = buf;
    uint32_t i = 0;
    fc_error_t res = fce_success;
    for(;i < fmt.len-1;++i) {
        if(fmt.base[i] != '%') { tmp[idx++] = fmt.base[i]; continue; }
        if(fmt.base[i+1] == '%') { tmp[idx++] = '%'; i++; continue; }
        bool isHex = false;
        if(fmt.base[i+1] == 'x' || fmt.base[i+1] == 'X') { i++; isHex = true; }

        if(arg_i >= count) { return fce_printf_need_more_args; }
        if((res = parse_arg(&tmp,&idx,&max,args[arg_i++],buf,isHex))) { return res; }
    }
    if(fmt.base[i] != '%') {
        tmp[idx++] = fmt.base[i];
    } else {
        if(arg_i >= count) { return fce_printf_need_more_args; }
        if((res = parse_arg(&tmp,&idx,&max,args[arg_i++],buf,false))) { return res; }
    }
    syscall_3(syscall_write,UNIX_STDOUT,tmp,idx);
    if(tmp != buf) { if((res = fc_free((void**)&tmp))) { return res; } }
    return fce_success;
}

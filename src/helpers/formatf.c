#include "helpers.h"

/* Its located in string header but we dont need any other things
 * so we only cstreq and cstrlen from the linker
 */
extern bool cstr_eq(const char* l, const char* r);
extern usz cstr_len(const char* str);

enum base_e {
    base_oct = 8,
    base_dec = 10,
    base_hex = 16
};

typedef enum base_e base_t;

static void __format_uint
(u8* buf, usz* count, u64 num, base_t base)
{
    static const char hex[] = "0123456789ABCDEF";
    u32 len = 0, j = 0;
    u8 tmp[64];
    u8 *b = nullptr;

    do {
        tmp[len++] = (u8)hex[num % base];
        num /= base;
    } while(num);

    if(base == base_hex) {
        tmp[len++] = '0';
        tmp[len++] = 'x';
    }

    *count += len;
    if(!buf) { return; }

    b = buf + *count - len;

    for(j = 0; j < len; ++j) {
        b[j] = tmp[len - 1 - j];
    }
}

error_t formatf
(sl_u8_t buf, sl_u8_t fmt, usz* out_len, ...)
{
    /* Init variables */
    va_list ap;
    error_t res = success;

    /* Start and end va and format string */
    va_start(ap, out_len);
    res = __formatf(buf, fmt, out_len, ap);
    va_end(ap);

    return res;
}

error_t __formatf
(sl_u8_t buf, sl_u8_t fmt, usz* out_len, va_list va)
{
    /* Init variables */
    usz count = 0, i = 0;
    bool long_num = false;
    u64 cur_u64 = 0;
    i64 cur_i64 = 0;
    char* cur_cstr = 0;
    sl_u8_t cur_vec = {0}, buf_sl = {0}, *cur_vec_ptr = 0;
    va_list ap;

    /* Check input */
    if(!fmt.items || !out_len) { return null_pointer; }

    va_copy(ap, va);

    *out_len = 0;

    for(;i < fmt.count; ++i) {

        /* Check for first '%' */
        if(fmt.items[i] != '%') {
            count++;
            if(buf.items) { buf.items[count - 1] = fmt.items[i]; }
            continue;
        }
        ++i;
        long_num = false;

        /* Check for long numbers */
        if(fmt.items[i] == 'l') { ++i; long_num = true; }
        if(fmt.items[i] == 'l') { ++i; long_num = true; }

        switch(fmt.items[i]) {
            /* Check for '%%' */
            case '%':{
                count++;
                /* Check for wrong instruction '%ll% / '%l%' */
                if(long_num) { va_end(ap); return formatf_unknown_format; }
                if(buf.items) { buf.items[count - 1] = '%'; }
            } break;

            /* Check for '%c' */
            case 'c': {
                count++;
                /* Check for wrong instruction '%llc / '%lc' */
                if(long_num) { va_end(ap); return formatf_unknown_format; }
                /* Char promotes to int while passing it */
                cur_u64 = (u64)va_arg(ap, int);
                if(buf.items) { buf.items[count - 1] = (u8)cur_u64; }
            } break;

            /* Handle %llx / %lx / %x or %llX / %llX / %X unsigned hexadecimal integer */
	    case 'x': case 'X': {
                if(long_num) { cur_u64 = va_arg(ap, u64);}
	        else { cur_u64 = va_arg(ap, u32);}
                __format_uint(buf.items, &count, cur_u64, base_hex);
            } break;

            /* Handle %lld / %ld / %d or %lli / %li / %i for signed decimal integers */
	    case 'd': case 'i': {
	        if(long_num) { cur_i64 = va_arg(ap, i64);}
	        else { cur_i64 = va_arg(ap, i32); }

                /* Check for negative */
	        if(cur_i64 < 0) {
                    count++; cur_i64 = -cur_i64;
                    if(buf.items) { buf.items[count - 1] = '-';}
                }
	        __format_uint(buf.items, &count, (u64)cur_i64, base_dec);
	    } break;

            /* Handle %llu / %lu / %u for unsigned decimal integers */
	    case 'u': {
	        if(long_num) { cur_u64 = va_arg(ap, u64);}
	        else { cur_u64 = va_arg(ap, u32); }
	        __format_uint(buf.items, &count, cur_u64, base_dec);
	    } break;

            /* Handle %llo / %lo / %o for unsigned decimal integers */
            case 'o': {
                if(long_num) { cur_u64 = va_arg(ap, u64);}
	        else { cur_u64 = va_arg(ap, u32);}
                __format_uint(buf.items, &count, cur_u64, base_oct);
            } break;

            /* Handle %p it will write as hexadecimal */
	    case 'p': {
	        cur_u64 = va_arg(ap, uintptr_t);
                __format_uint(buf.items, &count, cur_u64, base_hex);
	    } break;

            /* Handle %s it will write a cstr */
            case 's': {
                cur_cstr = va_arg(ap, char*);
                slice_set_cstr(&cur_vec, cur_cstr);
                if(buf.items) {
                    slice_set(&buf_sl, &buf.items[count], cur_vec.count);
                    mem_cpy(&buf_sl, &cur_vec);
                }
                count += cur_vec.count;
            } break;

            /* Handle %v it will use sl_u8_t* and it is not a structure its a pointer */
            case 'v': {
                cur_vec_ptr = va_arg(ap, sl_u8_t*);
                if(buf.items) {
                    slice_set(&buf_sl, &buf.items[count], buf.count - count);
                    if(mem_cpy(&buf_sl, cur_vec_ptr)) { va_end(ap); return small_buffer; }
                }
                count += cur_vec_ptr->count;
            } break;

            default: { va_end(ap); return formatf_unknown_format; }
        }
    }

    *out_len = count;
    va_end(ap);
    return success;
}

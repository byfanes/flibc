#include "helpers.h"

INTERNAL void hex_format
(u8* buf, u32* count, u64 num)
{
    /* Init variables */
    u32 times = 0, i = 0;
    u8 ptr[128];
    const char hexDigits[] = "0123456789ABCDEF";

    /* Check for zero case*/
    if(num == 0) { ptr[times++] = '0'; }

    /* Iterate until it becomes zero */
    while(num) {
	ptr[times++] = (u8)hexDigits[num % 16];
	num /= 16;
    };

    /* Write it in reverse order to buffer if buffer exits */
    for(;buf && i < times; ++i) { buf[i + *count] = ptr[times - i - 1]; }

    *count += times;
}

INTERNAL void decimal_format
(u8* buf, u32* count, u64 num)
{
    /* Init variables */
    u32 times = 0, i = 0;
    u8 ptr[128];

    /* Check for zero case*/
    if(num == 0) { ptr[times++] = '0'; }

    /* Iterate until it becomes zero */
    while(num) {
	ptr[times++] = (u8)('0' + (num % 10));
	num /= 10;
    };

    /* Write it in reverse order to buffer if buffer exits */
    for(;buf && i < times; ++i) { buf[i + *count] = ptr[times - i - 1]; }

    *count += times;
}

INTERNAL void octal_format
(u8* buf, u32* count, u64 num)
{
    /* Init variables */
    u32 times = 0, i = 0;
    u8 ptr[128];

    /* Check for zero case*/
    if(num == 0) { ptr[times++] = '0'; }

    /* Iterate until it becomes zero */
    while(num) {
	ptr[times++] = (u8)('0' + (num % 8));
	num /= 8;
    };

    /* Write it in reverse order to buffer if buffer exits */
    if(buf) {
        for(;i < times; ++i) { buf[i + *count] = ptr[times - i - 1]; }
    }

    *count += times;
}

error_t formatf
(slice(u8) buf, slice(u8) fmt, usize_t* out_len, ...)
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
(slice(u8) buf, slice(u8) fmt, usize_t* out_len, va_list va)
{
    /* Init variables */
    u32 count = 0, i = 0, len = 0;
    bool long_num = false;
    u64 cur_u64 = 0;
    i64 cur_i64 = 0;
    char* cur_cstr = 0;
    slice(u8) cur_vec = {0}, buf_sl = {0}, *cur_vec_ptr = 0;
    va_list ap;

    /* Copy va list to make users' va_list still usable */
    va_copy(ap, va);

    /* Check input */
    if(!fmt.base || !out_len) { return null_pointer; }

    *out_len = 0;

    for(;i < fmt.count; ++i) {

        /* Check for first '%' */
        if(fmt.base[i] != '%') {
            count++;
            if(buf.base) { buf.base[count - 1] = fmt.base[i]; }
            continue;
        }
        ++i;
        long_num = false;

        /* Check for long numbers */
        if(fmt.base[i] == 'l') { ++i; long_num = true; }
        if(fmt.base[i] == 'l') { ++i; long_num = true; }

        /* Check for '%%' */
        if(fmt.base[i] == '%') {
            count++;
            /* Check for wrong instruction '%ll% / '%l%' */
            if(long_num) { return formatf_unknown_format; }
            if(buf.base) { buf.base[count - 1] = '%'; }
        }

        /* Check for '%c' */
        else if(fmt.base[i] == 'c') {
            count++;
            /* Check for wrong instruction '%llc / '%lc' */
            if(long_num) { return formatf_unknown_format; }
            /* Char promotes to int while passing it */
            cur_u64 = (u64)va_arg(ap, int);
            if(buf.base) { buf.base[count - 1] = (u8)cur_u64; }
        }

        /* Handle %llx / %lx / %x or %llX / %llX / %X unsigned hexadecimal integer */
	else if(fmt.base[i] == 'x' || fmt.base[i] == 'X') {
            if(long_num) { cur_u64 = va_arg(ap, u64);}
	    else { cur_u64 = va_arg(ap, u32);}
            hex_format(buf.base, &count, cur_u64);
        }

        /* Handle %lld / %ld / %d or %lli / %li / %i for signed decimal integers */
	else if(fmt.base[i] == 'd' || fmt.base[i] == 'i') {
	    if(long_num) { cur_i64 = va_arg(ap, i64);}
	    else { cur_i64 = va_arg(ap, i32); }

            /* Check for negative */
	    if(cur_i64 < 0) {
                count++; cur_i64 = -cur_i64;
                if(buf.base) { buf.base[count - 1] = '-';}
            }
	    decimal_format(buf.base, &count, (u64)cur_i64);
	}

        /* Handle %llu / %lu / %u for unsigned decimal integers */
	else if(fmt.base[i] == 'u') {
	    if(long_num) { cur_u64 = va_arg(ap, u64);}
	    else { cur_u64 = (u32)va_arg(ap, u32); }
	    decimal_format(buf.base, &count, cur_u64);
	}

        /* Handle %llo / %lo / %o for unsigned decimal integers */
        else if(fmt.base[i] == 'o') {
            if(long_num) { cur_u64 = va_arg(ap, u64);}
	    else { cur_u64 = va_arg(ap, u32);}
            octal_format(buf.base, &count, cur_u64);
        }

        /* Handle %p it will write as hexadecimal */
	else if(fmt.base[i] == 'p') {
	    cur_u64 = (u64)va_arg(ap, void*);
            if(buf.base) {
                buf.base[count] = '0';
                buf.base[count + 1] = 'x';
            }
            count++;
            count++;
            hex_format(buf.base, &count, cur_u64);
	}

        /* Handle %s it will write a cstr */
        else if(fmt.base[i] == 's') {
            cur_cstr = va_arg(ap, char*);
            len = strlen(cur_cstr);
            set_slice(&cur_vec, cur_cstr, len);
            if(buf.base) {
                set_slice(&buf_sl, &buf.base[count], len);
                memcpy(&buf_sl, &cur_vec);
            }
            count += len;
        }

        /* Handle %v it will use *slice(u8) and it is not a structure its a pointer */
        else if(fmt.base[i] == 'v') {
            cur_vec_ptr = va_arg(ap, slice(u8)*);
            if(buf.base) {
                set_slice(&buf_sl, &buf.base[count], buf.count - len);
                if(memcpy(&buf_sl, cur_vec_ptr)) { return small_buffer; }
            }
            count += (u32)cur_vec_ptr->count;
        }

        else {
            return formatf_unknown_format;
        }
    }

    *out_len = count;
    return success;
}

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
    u32 count = 0, i = 0, len = 0;
    bool long_num = false;
    u64 cur_u64 = 0;
    i64 cur_i64 = 0;
    char* cur_cstr = 0;
    sl_u8_t cur_vec = {0}, buf_sl = {0}, *cur_vec_ptr = 0;
    va_list ap;

    /* Copy va list to make users' va_list still usable */
    va_copy(ap, va);

    /* Check input */
    if(!fmt.items || !out_len) { return null_pointer; }

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

        /* Check for '%%' */
        if(fmt.items[i] == '%') {
            count++;
            /* Check for wrong instruction '%ll% / '%l%' */
            if(long_num) { return formatf_unknown_format; }
            if(buf.items) { buf.items[count - 1] = '%'; }
        }

        /* Check for '%c' */
        else if(fmt.items[i] == 'c') {
            count++;
            /* Check for wrong instruction '%llc / '%lc' */
            if(long_num) { return formatf_unknown_format; }
            /* Char promotes to int while passing it */
            cur_u64 = (u64)va_arg(ap, int);
            if(buf.items) { buf.items[count - 1] = (u8)cur_u64; }
        }

        /* Handle %llx / %lx / %x or %llX / %llX / %X unsigned hexadecimal integer */
	else if(fmt.items[i] == 'x' || fmt.items[i] == 'X') {
            if(long_num) { cur_u64 = va_arg(ap, u64);}
	    else { cur_u64 = va_arg(ap, u32);}
            hex_format(buf.items, &count, cur_u64);
        }

        /* Handle %lld / %ld / %d or %lli / %li / %i for signed decimal integers */
	else if(fmt.items[i] == 'd' || fmt.items[i] == 'i') {
	    if(long_num) { cur_i64 = va_arg(ap, i64);}
	    else { cur_i64 = va_arg(ap, i32); }

            /* Check for negative */
	    if(cur_i64 < 0) {
                count++; cur_i64 = -cur_i64;
                if(buf.items) { buf.items[count - 1] = '-';}
            }
	    decimal_format(buf.items, &count, (u64)cur_i64);
	}

        /* Handle %llu / %lu / %u for unsigned decimal integers */
	else if(fmt.items[i] == 'u') {
	    if(long_num) { cur_u64 = va_arg(ap, u64);}
	    else { cur_u64 = (u32)va_arg(ap, u32); }
	    decimal_format(buf.items, &count, cur_u64);
	}

        /* Handle %llo / %lo / %o for unsigned decimal integers */
        else if(fmt.items[i] == 'o') {
            if(long_num) { cur_u64 = va_arg(ap, u64);}
	    else { cur_u64 = va_arg(ap, u32);}
            octal_format(buf.items, &count, cur_u64);
        }

        /* Handle %p it will write as hexadecimal */
	else if(fmt.items[i] == 'p') {
	    cur_u64 = (u64)va_arg(ap, void*);
            if(buf.items) {
                buf.items[count] = '0';
                buf.items[count + 1] = 'x';
            }
            count++;
            count++;
            hex_format(buf.items, &count, cur_u64);
	}

        /* Handle %s it will write a cstr */
        else if(fmt.items[i] == 's') {
            cur_cstr = va_arg(ap, char*);
            len = strlen(cur_cstr);
            set_slice(&cur_vec, cur_cstr, len);
            if(buf.items) {
                set_slice(&buf_sl, &buf.items[count], len);
                memcpy(&buf_sl, &cur_vec);
            }
            count += len;
        }

        /* Handle %v it will use sl_u8_t* and it is not a structure its a pointer */
        else if(fmt.items[i] == 'v') {
            cur_vec_ptr = va_arg(ap, sl_u8_t*);
            if(buf.items) {
                set_slice(&buf_sl, &buf.items[count], buf.count - len);
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

#include "stdio_private.h"

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
    for(;buf && i < times; ++i) { buf[i] = ptr[times - i - 1]; }

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
    for(;buf && i < times; ++i) { buf[i] = ptr[times - i - 1]; }

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


fc_error_t formatf
(slice_t buf, slice_t fmt, va_list ap, u32* out_len)
{
    /* Init variables */
    u32 count = 0, i = 0;
    bool long_num = false;
    u64 cur_u64 = 0;
    i64 cur_i64 = 0;
    
    /* Check input */
    if(!fmt.base) return fce_formatf_fmt_null;
    if(!out_len) return fce_formatf_out_null;

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
            if(long_num) { return fce_formatf_unknown; }
            if(buf.base) { buf.base[count - 1] = '%'; }
        }

        /* Check for '%c' */
        else if(fmt.base[i] == 'c') {
            count++;
            /* Check for wrong instruction '%llc / '%lc' */
            if(long_num) { return fce_formatf_unknown; }
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
	    cur_u64 = va_arg(ap, void*);
            buf.base[count++] = '0';
            buf.base[count++] = 'x';
            hex_format(buf.base, &count, cur_u64);
	}

        else {
            #include "stdlib.h"
            exit(fmt.base[i]);
            return fce_formatf_unknown;
        }
    }

    *out_len = count;
    return fce_success;
}

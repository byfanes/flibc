#include "crt.h"
#include "da.h"
#include "string.h"

error_t write_list(file_t* fptr, da(str_t)* list);

error_t write_list
(file_t* fptr, da(str_t)* list)
{
    error_t res = success;
    u32 i = 0;

    for(; i < list->count; ++i) {
        str_add_shadow_null(&list->items[i]);

        if((res = fprintf(fptr, "List element[%d]: %s\n", i, list->items[i].items)))
        { return res; }

        if((fflush(fptr))) { return res; }
    }

    return res;
}

error_t main
(std_t std)
{
    error_t res = success;
    u32 read_count = 0;
    u8 buf[128] = {0};
    slice(u8) buf_sl = {0};
    slice(u8) write_sl = {0};
    da(str_t) list = {0};
    str_t tmp = {0};
    u32 i = 0;

    /* Set the buffer slice */
    set_slice(&buf_sl, buf, sizeof(buf));

    /* Set da */
    if((res = da_init(std.alloc, &list, 32))) { return res; }

    for(;;) {
        res = fread(std.io.in, buf_sl, &read_count);
        if(res && res != io_partial) { return res; }

        /* If we see an '!' just stop the program */
        if(buf_sl.base[0] == '!') { break; }

        /* If we see an '?' just write the list */
        if(buf_sl.base[0] == '?') {
            if((res = write_list(std.io.out,  &list))) { return res; }
            continue;
        }

        /* Add new item to list -1 is for removing new line*/
        set_slice(&write_sl, buf, read_count - 1);
        if((res = str_init(std.alloc, &tmp, read_count))) { return res; }
        if((res = strcat_sl(&tmp, write_sl))) { return res; }
        if((res = da_insert(&list, &tmp, 0))) { return res; }

    }

    /* Free memory back */
    /* If you want to test memory leak system you can switch
     * from true to false it will leak memory and will
     */
    if (true) {
        for(; i < list.count; ++i) {
            str_deinit(&list.items[i]);
        }
        da_deinit(&list);
    }

    return res;
}

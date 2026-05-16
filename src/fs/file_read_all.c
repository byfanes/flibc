#include "fs_private.h"
#include "stdio.h"

error_t file_read_all
(allocator_t* alloc, path_t* path, da(u8)* out)
{
    /* Init variables */
    usize_t size = 0;
    slice(u8) buf = {0};
    error_t res = success;
    file_t* file = 0;
    
    /* Check inputs */
    if(!alloc || !path || !path->items || !path->count || !out)
    { return null_pointer; }

    /* Get size of the file */
    if((res = path_size(path, &size))) { return res; }
    if((res = da_init(alloc, out, size))) { return res; }

    /* Add shadow byte to make cstr, set buffer, open file and read it */
    str_add_shadow_null(path);
    if((res = fopen(alloc, (char*)path->items, &file, file_read))) { return res; }
    set_slice(&buf, out->items, size);
    if((res = fread(file, buf, nullptr)))
    if((res = fclose(&file))) { return res; }

    return success;
}

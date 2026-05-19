#include "fs_private.h"
#include "stdio.h"
#include "memory.h"

error_t file_copy
(allocator_t* alloc, path_t* from, path_t* to)
{
    /* Init variables */
    usize_t size = 0;
    file_t* file = 0;
    slice(u8) buf = {0};
    void* ptr = 0;
    error_t res = success;
    
    /* Check inputs */
    if(!alloc || !from || !from->items || !from->count || !to || !to->items || !to->count)
    { return null_pointer; }

    /* Get size of the file */
    if((res = path_size(from, &size))) { return res; }

    /* Add shadow byte to make cstr, set buffer, open file and read it */
    str_add_shadow_null(from);
    if((res = fopen(alloc, (char*)from->items, &file, file_read))) { return res; }
    if((res = malloc(alloc, size, &ptr))) { return res; }
    set_slice(&buf, ptr, size);
    if((res = fread(file, buf, nullptr))) { return res; }
    if((res = fclose(&file))) { return res; }

    /* Add shadow byte to make cstr, read buffer, close new file and free memory*/
    str_add_shadow_null(to);
    if((res = fopen(alloc, (char*)to->items, &file, file_write))) { return res; }
    if((res = fwrite(file, buf))) { return res; }
    if((res = fclose(&file))) { return res; }
    if((res = free(&ptr))) { return res; }
    
    return success;
}

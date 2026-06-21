#include "fs_private.h"
#include "io.h"
#include "memory.h"

error_t file_copy
(allocator_t* alloc, path_t* from, path_t* to)
{
    /* Init variables */
    usz size = 0;
    file_t* file = 0;
    sl_u8_t buf = {0};
    void* ptr = 0;
    error_t res = success;
    
    /* Check inputs */
    if(!alloc || !from || !from->items || !from->count || !to || !to->items || !to->count)
    { return null_pointer; }

    /* Get size of the file */
    if((res = path_size(from, &size))) { return res; }

    /* Add shadow byte to make cstr, set buffer, open file and read it */
    str_add_shadow_null(from);
    if((res = io_open(alloc, (char*)from->items, &file, file_read))) { return res; }
    if((res = mem_alloc(alloc, &ptr, size))) { return res; }
    slice_set(&buf, ptr, size);
    if((res = io_read(file, &buf, nullptr))) { return res; }
    if((res = io_close(&file))) { return res; }

    /* Add shadow byte to make cstr, read buffer, close new file and free memory*/
    str_add_shadow_null(to);
    if((res = io_open(alloc, (char*)to->items, &file, file_write))) { return res; }
    if((res = io_write(file, &buf))) { return res; }
    if((res = io_close(&file))) { return res; }
    if((res = mem_free(&ptr))) { return res; }
    
    return success;
}

#include "fs_private.h"
#include "stdio.h"

error_t file_read_all
(allocator_t* alloc, path_t* path, da_u8_t* out)
{
    /* Init variables */
    usize_t size = 0;
    sl_u8_t buf = {0};
    error_t res = success, res2 = success;
    file_t *file = 0;
    def_da_t *def = (void*)out;

    /* Check inputs */
    if(!alloc || !path || !path->items || !path->count || !out)
    { return null_pointer; }

    /* Get size of the file */
    if((res = path_size(path, &size))) { return res; }
    if((res = da_init(alloc, out, size))) { return res; }

    /* Add shadow byte to make cstr, set buffer, open file and read it */
    str_add_shadow_null(path);
    if((res = fopen(alloc, (char*)path->items, &file, file_read))) { return res; }

    /* This could be better when we move to slice pointers */
    /* Set slice and read file to buffer then set count */
    set_slice(&buf, out->items, size);
    res = fread(file, &buf, nullptr);
    def->count = buf.count;

    /* First close the file because other wise it will leak then check read */
    if((res2 = fclose(&file))) { return res2; }
    /* We expect it to read same as file size so in this case we check io_partial too */
    if(res) { return res; }

    return success;
}

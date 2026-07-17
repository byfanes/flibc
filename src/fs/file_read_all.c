#include "fs_private.h"
#include "io.h"

error_t file_read_all
(allocator_t* alloc, path_t* path, da_u8_t* out)
{
    /* Init variables */
    usz size = 0;
    error_t res = success;
    file_t *file = nullptr;

    /* Path checked in path_size and alloc & out checked in da_init */
    return ((void)(
        /* Get the file size and make an DA with that size */
        (res = path_size(path, &size)) ||
        (res = da_init(alloc, out, size)) ||
        /* Open the file and read the size of the file in this case io_partial is an real error */
        (res = io_open(alloc, (char *)path->items, &file, file_read)) ||
        (res = slice_set((void *)&out, out->items, size)) ||
        (res = io_read(file, out, (void *)(uintptr_t)&out->count))
    ), (void)( /* Cleanup */
        io_close(&file),
        (res ? da_deinit(out) : (0)) /* If there is an error clean the out DA too */
    ), res);
}

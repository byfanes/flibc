#include "memory_private.h"

error_t allocator_deinit
(allocator_t** set)
{
    /* Init variables */
    allocator_t *alloc = 0;
    ssize_t res = 0;
    usize_t i = 0;
    bool bit = 0;
    heap_header_t *header = 0;
    /* sizeof buf might be a problem in the future but i dont think
     * there will be a file which will exceed this limit right now
     */
    u8 buf[8192] = {0};
    slice(u8) buf_sl = {0};
    usize_t len = 0;

    /* Check user input */
    if(!set) { return null_pointer; }
    alloc = *set;
    if(!alloc) { return null_pointer; }

    set_slice(&buf_sl, buf, sizeof(buf));

    for(;i < CHUNK_MAX; ++i) {
        if(!alloc->free_bits[i / 8]) { i += 7; continue; }
        bit = (alloc->free_bits[i / 8] >>  i % 8) & 1;
        if(!bit) { continue; }
        /* Leaked memory */
        header = (heap_header_t*)(uintptr_t)((u8*)(alloc + 1) + i * CHUNK_SIZE);
        formatf(buf_sl,
            cstr_to_u8sl("Memory Leak: %u bytes from %s:%d is not freed\n"),
            &len, header->req_alloced, header->file_name, header->line);

        syscall_3(syscall_write, UNIX_STDERR, buf_sl.base, (ssize_t)len);
        i += header->raw_alloced / CHUNK_SIZE - 1;
    }

    /* Give back the memory to os */
    res = syscall_2(syscall_munmap, (ssize_t)alloc, RAW_ALLOCATION_SIZE);

    /* Check free syscall */
    if(res != 0) { return memory_error; }

    *set = 0;
    return success;
}

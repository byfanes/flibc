#include "memory_private.h"

error_t allocator_deinit
(allocator_t** set)
{
    /* Init variables */
    error_t res = success;
    allocator_t *alloc = 0;
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

    /* Check if the allocator needs to do leak detection or not */
    if(!(alloc->flags & allocator_dont_check_leaks)) {
        set_slice(&buf_sl, buf, sizeof(buf));

        /* Check for the chunks in allocator */
        for(i = 0;i < CHUNK_MAX; ++i) {
            /* Check current byte if it has any ones in it and locate it */
            if(!alloc->free_bits[i / 8]) { i += 7; continue; }
            bit = (alloc->free_bits[i / 8] >>  i % 8) & 1;
            if(!bit) { continue; }
            /* Leaked memory */
            header = (heap_header_t*)(uintptr_t)((u8*)(alloc + 1) + i * CHUNK_SIZE);
            formatf(buf_sl,
                cstr_to_u8sl("Memory Leak: %u bytes from %s:%d is not freed\n"),
                &len, header->req_alloced, header->file_name, header->line);

            /* Write directly to standard error */
            /* Ignore its fail state because it is not deinit's main goal */
            syscall_3_linux(syscall_write, UNIX_STDERR, buf_sl.base, (ssize_t)len);
            i += header->raw_alloced / CHUNK_SIZE - 1;
        }

        /* Check for the nodes in allocator */
        for(i = 0; i < ALLOCATOR_NODE_COUNT; ++i) {
            switch(alloc->nodes[i].type) {
                case heap_node_empty: continue;

                default: {
                    /* TODO: Maybe we can return an error but it does not effect the function */
                } continue;

                case raw_chunk_allocation: {
                    header = (heap_header_t*)(uintptr_t)alloc->nodes[i].start;
                    formatf(buf_sl,
                    cstr_to_u8sl("Memory Leak: %u bytes from %s:%d is not freed\n"),
                    &len, header->req_alloced, header->file_name, header->line);

                   /* Write directly to standard error */
                   /* Ignore its fail state because it is not deinit's main goal */
                   syscall_3_linux(syscall_write, UNIX_STDERR, buf_sl.base, (ssize_t)len);
                } break;
            }
        }

    }

    /* If there is another allocator deinit it too */
    if(alloc->next) {
        if((res = allocator_deinit(&alloc->next))) { return res; }
    }

    for(i = 0; i < ALLOCATOR_NODE_COUNT; ++i) {
        switch(alloc->nodes[i].type) {
            case heap_node_empty: continue;

            default: {
                /* TODO: Maybe we can return an error but it does not effect the function */
            } continue;

            case raw_chunk_allocation: {
                header = (heap_header_t*)(uintptr_t)alloc->nodes[i].start;
                /* If we cant free any memory just stop and return an error no future freeing */
                if(0 != syscall_2_linux(syscall_munmap, header, header->raw_alloced))
                { return memory_error; }

                alloc->nodes[i].type = heap_node_empty;
                alloc->nodes[i].start = nullptr;
            } break;
        }
    }

    /* Give back the memory to os */
    if(0 != syscall_2_linux(syscall_munmap, (ssize_t)alloc, RAW_ALLOCATION_SIZE))
    { return memory_error; }

    *set = 0;
    return success;
}

#include "memory_private.h"

static void __print_leak_dummy
(heap_header_t* header)
{
    (void)header;
}

static void __print_leak
(heap_header_t* header)
{
    u8 buf[8192] = {0};
    sl_u8_t buf_sl = {0};
    usz len = 0;
    os_fid_t handle = OS_INVALID_FILE_HANDLE;
    const sl_u8_t msg = ccstr_to_u8(
    "Warning in allocator %p:\n"
    "Memory Leak: Allocation in %s:%d for %u bytes has been leaked!\n");

    slice_set(&buf_sl, buf, sizeof(buf));
    formatf(buf_sl, msg, &len, header->alloc, header->file_name, header->line, header->wanted_alloc);

    __os_file_get_std(&handle, os_file_stderr);
    /* Write directly to standard error */
    /* Ignore its fail state because it is not deinit's main goal */
    __os_file_write(handle, buf_sl.items, len);
}

error_t allocator_deinit
(allocator_t** set)
{
    /* Init variables */
    error_t res = success;
    allocator_t *alloc = 0;
    usz i = 0;
    bool bit = 0;
    heap_header_t *header = 0;
    u32 raw = 0;
    void (*print_leak)(heap_header_t*) = nullptr;

    /* Check user input */
    if(!set) { return null_pointer; }
    alloc = *set;
    if(!alloc) { return success; }

    mutex_lock(&alloc->meta.mutex);

    print_leak = (alloc->meta.flags & allocator_dont_check_leaks)
               ? __print_leak_dummy : __print_leak;

    /* Check if the allocator needs to do leak detection or not */
    if(!(alloc->meta.flags & allocator_dont_check_leaks)) {

        /* Check for the chunks in allocator */
        for(i = 0; i < CHUNK_MAX; ++i) {
            /* Check current byte if it has any ones in it and locate it */
            if(!alloc->free_bits[i / 8]) { i += 7; continue; }
            bit = (alloc->free_bits[i / 8] >>  i % 8) & 1;
            if(!bit) { continue; }
            /* Leaked memory */
            header = (heap_header_t*)(uintptr_t)((u8*)(alloc + 1) + i * CHUNK_SIZE);

            print_leak(header);

            raw = ALIGN_64(header->wanted_alloc + ADDITIONAL_HEADER_SIZE);
            i += raw / CHUNK_SIZE - 1;
        }
    }

    for(i = 0; i < ALLOCATOR_HEADER_COUNT; ++i) {
        header = alloc->headers[i];
        if(!header) { continue; }
        raw = ALIGN_64(header->wanted_alloc + ADDITIONAL_HEADER_SIZE);

        print_leak(header);

        /* If we cant free any memory just stop and return an error no future freeing */
        if((res = __os_memory_free(alloc->headers + i, (ssz)raw))) { return res; }
    }

    /* If there is another allocator deinit it too */
    if(alloc->meta.next) {
        if((res = allocator_deinit(&alloc->meta.next))) { return res; }
    }

    mutex_unlock(&alloc->meta.mutex);

    /* Give back the memory to os */
    return __os_memory_free(set, RAW_ALLOCATION_SIZE);
}

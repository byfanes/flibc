#include "memory_private.h"

noreturn allocator_overflow
(allocator_t* alloc, heap_header_t* header)
{
    usz len = 0;
    u8 buf[8192] = {0};
    sl_u8_t buf_sl = {0};
    const sl_u8_t msg = ccstr_to_u8(
    "Error in allocator %p:\n"
    "Overflow detected: Allocation in %s:%d for %u bytes has overflow!\n");

    slice_set(&buf_sl, buf, sizeof(buf));
    formatf(buf_sl, msg, &len, alloc, header->file_name, header->line, header->wanted_alloc);
    __panic_len(buf_sl.items, len);
}

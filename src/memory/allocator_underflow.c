#include "memory_private.h"

noreturn allocator_underflow
(allocator_t* alloc, heap_header_t* header)
{
    use_fmt_ctx;
    usz len = 0;
    u8 buf[8192] = {0};

    (void)fmt_buf_wrote_nl(buf, sizeof(buf), len, "Error in allocator " arg_ptr(alloc)
    "\nOverflow deteced: Allocation in " arg_cstr(header->file_name) ":" arg_udec(header->line)
    " for " arg_udec(header->wanted_alloc) " bytes has underflow!");

    __panic_len(buf, len);
}

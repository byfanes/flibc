#include "memory_private.h"

void allocator_underflow
(allocator_t* alloc, heap_header_t* header)
{
    usz len = 0;
    u8 buf[8192] = {0};
    sl_u8_t buf_sl = {0};
    sl_u8_t msg =
        ccstr_to_u8("Underrflow detected: Allocation in %s:%d for %u bytes has underflow!\n");
    set_slice(&buf_sl, buf, sizeof(buf));

    (void)alloc;
    
    formatf(buf_sl, msg, &len, header->file_name, header->line, header->wanted_alloc);
    syscall_3_linux(syscall_write, UNIX_STDERR, (ssz)buf_sl.items, (ssz)len);

}

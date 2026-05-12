#include "minitest.h"
#include "stdio.h"
#include "error.h"
#include "memory.h"

int main(allocator_t*, stdio_t, slice_u8, slice(slice_u8));
int main
(allocator_t* alloc, stdio_t stdio, slice_u8 exe, slice(slice_u8) args)
{
    u8 buffer[128] = {0};
    usize_t wrote = 0;
    fc_error_t res = fce_success;
    slice(u8) buf_sl = {0};

    set_slice(&buf_sl, buffer, 128);
    (void)alloc;
    (void)exe;
    (void)args;

    res = sprintf(buf_sl, &wrote, cstr_to_u8sl("Testing %d"), 42);
    fprintf(stdio.out,cstr_to_u8sl("This is from stdio test res:%d\n"),res);
    fflush(stdio.out);
    ASSERT_OK(sprintf(buf_sl, &wrote, cstr_to_u8sl("Testing %d"), 42));
    ASSERT(wrote > 0);
    ASSERT_EQ(buffer[0], 'T');

    return 0;
}

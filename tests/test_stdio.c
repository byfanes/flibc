#include "minitest.h"
#include "crt.h"

error_t main
(std_t std)
{
    u8 buffer[128] = {0};
    usize_t wrote = 0;
    error_t res = success;
    slice(u8) buf_sl = {0};

    set_slice(&buf_sl, buffer, 128);

    res = sprintf(buf_sl, &wrote, cstr_to_u8sl("Testing %d"), 42);
    fprintf(std.io.out,cstr_to_u8sl("This is from stdio test res:%d\n"),res);
    fflush(std.io.out);
    ASSERT_OK(sprintf(buf_sl, &wrote, cstr_to_u8sl("Testing %d"), 42));
    ASSERT(wrote > 0);
    ASSERT_EQ(buffer[0], 'T');

    return 0;
}

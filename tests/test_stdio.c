#include "minitest.h"
#include "stdio.h"
#include "error.h"

int main(stdio_t stdio) {
    u8 buffer[128] = {0};
    u32 wrote = 0;
    fc_error_t res = fce_success;
    slice_t buf_sl = {0};

    set_slice(&buf_sl, buffer, 128);

    TEST_START("sprintf");
    res = sprintf(buf_sl, &wrote, cstr_to_def("Testing %d"), 42);
    fprintf(stdio.out,cstr_to_def("%d"),res);
    fflush(stdio.out);
    ASSERT_OK(sprintf(buf_sl, &wrote, cstr_to_def("Testing %d"), 42));
    return 0;
    ASSERT(wrote > 0);
    ASSERT_EQ(buffer[0], 'T');
    TEST_PASS();

    return 0;
}

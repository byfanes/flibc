#include "minitest.h"
#include "memory.h"
#include "error.h"

int main(void) {
    /* Variable declarations first (C89) */
    u8 buf1[10] = {0};
    u8 buf2[10] = {0};
    u32 i;
    bool cmp_res = false;

    /* Brace initialization for const fields */
    slice_t sl_buf1  = { nullptr, 10 };
    slice_t sl_buf2  = { nullptr, 10 };
    slice_t sl_half1 = { nullptr, 5 };
    slice_t sl_half2 = { nullptr, 5 }; /* Overlaps with half1 */

    sl_buf1.base = (void*)buf1;
    sl_buf2.base = (void*)buf2;
    sl_half1.base =(void*)buf1;
    sl_half2.base =(void*)(buf1 + 2);

    TEST_START("memset");
    ASSERT_OK(memset(sl_buf1, 42));
    for(i = 0; i < 10; ++i) { ASSERT_EQ(buf1[i], 42); }
    TEST_PASS();

    TEST_START("memcpy");
    buf1[0] = 99; buf1[1] = 88;
    ASSERT_OK(memcpy(sl_buf2, sl_buf1));
    ASSERT_EQ(buf2[0], 99);
    ASSERT_EQ(buf2[1], 88);
    ASSERT_EQ(buf2[9], 42);
    TEST_PASS();

    TEST_START("memcmp");
    ASSERT_OK(memcmp(sl_buf1, sl_buf2, &cmp_res));
    ASSERT(cmp_res == true);
    buf2[9] = 13; /* Change one byte */
    ASSERT_OK(memcmp(sl_buf1, sl_buf2, &cmp_res));
    ASSERT(cmp_res == false);
    TEST_PASS();

    TEST_START("memmove (overlapping)");
    for(i = 0; i < 10; ++i) buf1[i] = (u8)i; /* 0 1 2 3 4 5 6 7 8 9 */
    ASSERT_OK(memmove(sl_half2, sl_half1));
    /* Should be: 0 1 0 1 2 3 4 7 8 9 */
    ASSERT_EQ(buf1[2], 0);
    ASSERT_EQ(buf1[3], 1);
    ASSERT_EQ(buf1[6], 4);
    TEST_PASS();

    return 0;
}

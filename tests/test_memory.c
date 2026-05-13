#include "minitest.h"
#include "crt.h"
#include "memory.h"

int main
(std_t std)
{
    /* Variable declarations first (C89) */
    u8 buf1[10] = {0};
    u8 buf2[10] = {0};
    u32 i = 0;
    bool cmp_res = false;

    /* Brace initialization for const fields */
    slice(u8) sl_buf1  = { 0 };
    slice(u8) sl_buf2  = { 0 };
    slice(u8) sl_half1 = { 0 };
    slice(u8) sl_half2 = { 0 };

    (void)std;

    set_slice(&sl_buf1, buf1, 10);
    set_slice(&sl_buf2, buf2, 10);
    set_slice(&sl_half1, buf1, 5);
    set_slice(&sl_half2, (buf1 + 2), 5);

    ASSERT_OK(memset(&sl_buf1, 42));
    for(i = 0; i < 10; ++i) { ASSERT_EQ(buf1[i], 42); }

    buf1[0] = 99; buf1[1] = 88;
    ASSERT_OK(memcpy(&sl_buf2, &sl_buf1));
    ASSERT_EQ(buf2[0], 99);
    ASSERT_EQ(buf2[1], 88);
    ASSERT_EQ(buf2[9], 42);

    ASSERT_OK(memcmp(&sl_buf1, &sl_buf2, &cmp_res));
    ASSERT(cmp_res == true);
    buf2[9] = 13; /* Change one byte */
    ASSERT_OK(memcmp(&sl_buf1, &sl_buf2, &cmp_res));
    ASSERT(cmp_res == false);

    for(i = 0; i < 10; ++i) buf1[i] = (u8)i; /* 0 1 2 3 4 5 6 7 8 9 */
    ASSERT_OK(memmove(&sl_half2, &sl_half1));
    /* Should be: 0 1 0 1 2 3 4 7 8 9 */
    ASSERT_EQ(buf1[2], 0);
    ASSERT_EQ(buf1[3], 1);
    ASSERT_EQ(buf1[6], 4);

    return 0;
}

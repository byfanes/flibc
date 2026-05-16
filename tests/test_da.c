#include "minitest.h"
#include "crt.h"
#include "da.h"

error_t main
(std_t std)
{
    u32 val = 42;
    u32 val2 = 99;
    u32 out = 0;
    da(u32) arr = {0};

    ASSERT_OK(da_init(std.alloc, &arr, 10));
    ASSERT(arr.items != NULL);
    ASSERT(arr.capacity >= 10);
    ASSERT(arr.count == 0);

    ASSERT_OK(da_insert(&arr, &val, 0));
    ASSERT_EQ(arr.count, 1);
    ASSERT_EQ(arr.items[0], 42);

    ASSERT_OK(da_insert(&arr, &val2, 1));
    ASSERT_EQ(arr.count, 2);
    ASSERT_EQ(arr.items[1], 99);

    ASSERT_OK(da_pop_last(&arr, &out));
    ASSERT_EQ(out, 99);
    ASSERT_EQ(arr.count, 1);

    ASSERT_OK(da_remove(&arr, 0));
    ASSERT_EQ(arr.count, 0);

    ASSERT_OK(da_deinit(&arr));
    return 0;
}

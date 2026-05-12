#include "minitest.h"
#include "da.h"
#include "stdio.h"
#include "memory.h"
#include "error.h"

int main(allocator_t*, stdio_t, slice_u8, slice(slice_u8));
int main
(allocator_t* alloc, stdio_t stdio, slice_u8 exe, slice(slice_u8) args)
{
    u32 val = 42;
    u32 val2 = 99;
    u32 out = 0;
    da(u32) arr = {0};

    (void)stdio;
    (void)exe;
    (void)args;

    ASSERT_OK(da_init(alloc, &arr, 10));
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
    return 0;
}

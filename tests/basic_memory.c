#include "memory.h"
#include "stdlib.h"

#define FAIL(msg) do { \
    exit(1); \
} while(0)

#define CHECK_OK(expr) do { \
    if ((expr) != fce_success) FAIL(#expr); \
} while(0)

#define CHECK_TRUE(expr) do { \
    if (!(expr)) FAIL(#expr); \
} while(0)

#define CHECK_FALSE(expr) do { \
    if ((expr)) FAIL(#expr); \
} while(0)

static void test_malloc_free(void);
static void test_malloc_free(void) {
    void* ptr = NULL;

    CHECK_OK(malloc(64, &ptr));
    if (ptr == NULL) FAIL("malloc returned NULL");

    CHECK_OK(free(&ptr));
}

static void test_calloc(void);
static void test_calloc(void) {
    uint8_t* ptr = NULL;

    CHECK_OK(calloc(16, &ptr));
    if (ptr == NULL) FAIL("calloc returned NULL");

    for (int i = 0; i < 16; i++) {
        if (ptr[i] != 0) FAIL("calloc not zeroed");
    }

    CHECK_OK(free(&ptr));
}

static void test_realloc(void);
static void test_realloc(void) {
    uint8_t* ptr = NULL;

    CHECK_OK(malloc(8, &ptr));

    for (uint8_t i = 0; i < 8; i++) ptr[i] = i;

    CHECK_OK(realloc(16, &ptr));

    for (int i = 0; i < 8; i++) {
        if (ptr[i] != i) FAIL("realloc did not preserve data");
    }

    CHECK_OK(free(&ptr));
}

static void test_memset(void);
static void test_memset(void) {
    uint8_t buffer[10];
    slice_t slice = { buffer, 10 };

    CHECK_OK(memset(slice, 0xAA));

    for (int i = 0; i < 10; i++) {
        if (buffer[i] != 0xAA) FAIL("memset failed");
    }
}

static void test_memcpy(void);
static void test_memcpy(void) {
    uint8_t src_buf[5] = {1,2,3,4,5};
    uint8_t dst_buf[5] = {0};

    slice_t src = { src_buf, 5 };
    slice_t dst = { dst_buf, 5 };

    CHECK_OK(memcpy(dst, src));

    for (int i = 0; i < 5; i++) {
        if (dst_buf[i] != src_buf[i]) FAIL("memcpy mismatch");
    }
}

static void test_memmove_overlap(void);
static void test_memmove_overlap(void) {
    uint8_t buf[10] = {0,1,2,3,4,5,6,7,8,9};

    slice_t src = { buf, 5 };
    slice_t dst = { buf + 2, 5 };

    CHECK_OK(memmove(dst, src));

    if (buf[2] != 0) FAIL("memmove overlap failed at 2");
    if (buf[3] != 1) FAIL("memmove overlap failed at 3");
    if (buf[4] != 2) FAIL("memmove overlap failed at 4");
}

static void test_memcmp(void);
static void test_memcmp(void) {
    uint8_t a[4] = {1,2,3,4};
    uint8_t b[4] = {1,2,3,4};
    uint8_t c[4] = {1,2,3,5};

    slice_t sa = { a, 4 };
    slice_t sb = { b, 4 };
    slice_t sc = { c, 4 };

    bool res = false;

    CHECK_OK(memcmp(sa, sb, &res));
    CHECK_TRUE(res);

    CHECK_OK(memcmp(sa, sc, &res));
    CHECK_FALSE(res);
}

static void test_memswap(void);
static void test_memswap(void) {
    uint8_t a[3] = {1,2,3};
    uint8_t b[3] = {4,5,6};

    slice_t sa = { a, 3 };
    slice_t sb = { b, 3 };

    CHECK_OK(memswap(sa, sb));

    if (!(a[0] == 4 && a[1] == 5 && a[2] == 6))
        FAIL("memswap failed for a");

    if (!(b[0] == 1 && b[1] == 2 && b[2] == 3))
        FAIL("memswap failed for b");
}

static void test_memcmp_min(void);
static void test_memcmp_min(void) {
    uint8_t a[5] = {1,2,3,4,5};
    uint8_t b[3] = {1,2,3};

    slice_t sa = { a, 5 };
    slice_t sb = { b, 3 };

    bool res = false;

    CHECK_OK(memcmp_min(sa, sb, &res));
    CHECK_TRUE(res);
}

int main(void);

int main(void) {

    test_malloc_free();
    test_calloc();
    test_realloc();
    test_memset();
    test_memcpy();
    test_memmove_overlap();
    test_memcmp();
    test_memswap();
    test_memcmp_min();

    return 0;
}

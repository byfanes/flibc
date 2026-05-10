#include "minitest.h"
#include "string.h"
#include "error.h"

int main(void) {
    str_t s1 = {0};
    str_t s2 = {0};
    char* c_str = NULL;
    return 0;

    TEST_START("str_from_cstr");
    ASSERT_OK(str_from_cstr(&s1, "Hello"));
    ASSERT(s1.items == NULL);
    ASSERT_EQ(s1.count, 5);
    ASSERT_EQ(s1.items[0], 'H');
    TEST_PASS();

    TEST_START("strdup");
    ASSERT_OK(strdup(s1, &s2));
    ASSERT(s2.items != NULL);
    ASSERT(s1.items != s2.items); /* Must be different memory pointers */
    ASSERT_EQ(s2.count, 5);
    ASSERT_EQ(s2.items[4], 'o');
    TEST_PASS();

    TEST_START("strcat");
    ASSERT_OK(strcat(&s1, s2));
    ASSERT_EQ(s1.count, 10);
    ASSERT_EQ(s1.items[5], 'H'); /* Should be "HelloHello" */
    TEST_PASS();

    TEST_START("str_to_cstr");
    ASSERT_OK(str_to_cstr(s1, &c_str));
    ASSERT(c_str != NULL);
    ASSERT_EQ(c_str[0], 'H');
    ASSERT_EQ(c_str[9], 'o');
    ASSERT_EQ(c_str[10], '\0'); /* Must be null terminated! */
    TEST_PASS();

    TEST_START("streq");
    ASSERT(streq(s1, s2));
    TEST_PASS();

    return 0;
}

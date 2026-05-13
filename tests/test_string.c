#include "minitest.h"
#include "crt.h"
#include "string.h"

int main
(std_t std)
{
    str_t s1 = {0};
    str_t s2 = {0};
    char* c_str = NULL;

    ASSERT_OK(str_from_cstr(std.alloc, &s1, "Hello"));
    ASSERT(s1.items != NULL);
    ASSERT_EQ(s1.count, 5);
    ASSERT_EQ(s1.items[0], 'H');

    ASSERT_OK(strdup(std.alloc, &s1, &s2));
    ASSERT(s2.items != NULL);
    ASSERT(s1.items != s2.items); /* Must be different memory pointers */
    ASSERT_EQ(s2.count, 5);
    ASSERT_EQ(s2.items[4], 'o');

    ASSERT_OK(strcat(&s1, &s2));
    ASSERT_EQ(s1.count, 10);
    ASSERT_EQ(s1.items[5], 'H'); /* Should be "HelloHello" */

    ASSERT_OK(str_to_cstr(std.alloc, &s1, &c_str));
    ASSERT(c_str != NULL);
    ASSERT_EQ(c_str[0], 'H');
    ASSERT_EQ(c_str[9], 'o');
    ASSERT_EQ(c_str[10], '\0'); /* Must be null terminated! */

    ASSERT(streq(&s1, &s2) == false);

    return 0;
}

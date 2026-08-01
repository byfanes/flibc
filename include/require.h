#ifndef __FLIBC_REQUIRE_H__
#define __FLIBC_REQUIRE_H__

/* Do not put macros to group things such as
 * (void)sizeof(x) to #define comp_check(x)
 * it will be bad for compiler errors messages
 */

/* This header allow user to check mostly void* for compatibility for the types
 * and being generic at same time and those checks are done in compile time and not
 * effecting the run time
 */

/* Note: Use incom for incomplete types because C does not allow to do pointer
 * arithmetic on incomplete types and the reason why the one with subtract and
 * one with comparing because of the standard subtraction is strictier than comparing
 * because of that using subtraction is better
 */

/* Direct ptr checks */
#define require_defereable(x) ((void)sizeof(*(x)))
#define require_typed_ptr(x, type) (void)sizeof((x) - ((type *)0))
#define require_typed_incom_ptr(x, type) (void)sizeof((x) == ((type *)0))
#define require_writable_ptr(x) ((void)sizeof(*(x) = *(x)))
#define require_member_ptr(x, member) ((void)sizeof((x)->member))
#define require_same_ptr(x, y) ((void)sizeof((x) - (y)))
#define require_same_incom_ptr(x, y) ((void)sizeof((x) == (y)))

/* Value type checks */
#define require_comparable(x, y) ((void)sizeof((x) == (y)))
#define require_member(x, member) ((void)sizeof((x).member))
#define require_integer(x) ((void)sizeof(~(x)))
#define require_arithmetic(x) ((void)sizeof((x) * 1))
#define require_lvalue(x) ((void)sizeof((x) = (x)))
#define require_scalar(x) ((void)sizeof((x) ? 1 : 0))
#define require_orderable(x, y) ((void)sizeof((x) < (y)))
#define require_addressable(x) ((void)sizeof(&(x)))

#endif /* __FLIBC_REQUIRE_H__ */

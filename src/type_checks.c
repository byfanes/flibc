#include "base.h"
#include "memory/memory_private.h"
#include "da/da_private.h"
#include "fs/fs_private.h"
#include "socket/socket_private.h"

/* This file acts as a centralized validation suite for compile-time structural checks.
 * It verifies type sizes, ensures offset compatibility between interchangeable structs
 * (like slices and dynamic arrays), and strictly pins the memory layout of baked-in
 * structs to prevent compiler padding issues.
 *
 * We separate these checks into a dedicated .c file to explicitly control all critical
 * structs in one place. This prevents header bloat and avoids noisy, redundant
 * compilation errors across multiple files.
 */

/* Two downsides of this approach:
 * First, we rely on negative array sizes ([-1]) and the -Werror=overflow compiler flag
 * to trigger static assertion failures. If compiler support becomes an issue later,
 * this can be converted to the 1 / 0 divide-by-zero trick.
 *
 * Second, we rely on the compiler's constant folding in __flibc_struct_member_check_function.
 * Because sizeof and offsetof are integer constant expressions, the compiler inherently
 * evaluates them at compile-time even with -O0. Calling this function does nothing, but
 * it does expose a harmless, empty label to the global namespace.
 */

can_be_slice(u8 , __type_test_slice);
can_be_da(u8 , __type_test_da);

#define VALID_VALUE 1
#define INVALID_VALUE 256

#define _type_check(t1, t2, m)\
     (!!(sizeof(&(((t1*)0)->m) == &((t2*)0)->m)))

#define _offset_check(t1, t2, m) \
     (offsetof(t1, m) == offsetof(t2, m))

#define _size_check(t1, t2, m) \
     (sizeof(((t1*)0)->m) == sizeof(((t2*)0)->m))

#define _struct_member_check(t1, t2, m) \
{ \
    const u8 __struct_member_check__##t1_##t2_##m = \
    ( _type_check(t1, t2, m) && _offset_check(t1, t2, m) && _size_check(t1, t2, m)) \
    ? VALID_VALUE : INVALID_VALUE; \
    (void)__struct_member_check__##t1_##t2_##m; \
}

#define _struct_member_baked(type, mem, mem_type, exp) \
{ \
    mem_type __useles_val__; \
    const u8 __struct_member_baked__##type_##mem = \
    ((offsetof(type, mem) == exp) && \
    !!(sizeof(&((type*)0)->mem == &__useles_val__))) \
    ? VALID_VALUE : INVALID_VALUE; \
    (void)__struct_member_baked__##type_##mem; \
}

#define _struct_array_baked(type, mem, mem_type, mem_size, exp) \
{ \
    mem_type __useles_val__[mem_size]; \
    const u8 __struct_member_baked__##type_##mem = \
    ((offsetof(type, mem) == exp) && \
    !!(sizeof(((type*)0)->mem == __useles_val__)) && \
    (ARRAY_LEN(__useles_val__) == ARRAY_LEN(((type*)0)->mem)) \
    ) \
    ? VALID_VALUE : INVALID_VALUE; \
    (void)__struct_member_baked__##type_##mem; \
}

#define _static_assert(expr, name) \
    typedef u8 __static_assert__##name[((expr)) ? 1 : -1]

_static_assert(sizeof(u8) == 1, u8_must_be_1byte);
_static_assert(sizeof(u16) == 2, u16_must_be_2bytes);
_static_assert(sizeof(u32) == 4, u32_must_be_4bytes);
_static_assert(sizeof(u64) == 8, u64_must_be_8bytes);

#ifdef SIZE_IS_64BITS
_static_assert(sizeof(void*) == 8, pointer_size_must_be_8bytes);
#else
_static_assert(sizeof(void*) == 4, pointer_size_must_be_4bytes);
#endif
_static_assert(sizeof(usz) == sizeof(void*), usize_must_match_pointer_size);
_static_assert(sizeof(ssz) == sizeof(void*), ssize_must_match_pointer_size);

_static_assert(4096 == PAGE_SIZE, a_page_must_4kb);
_static_assert(sizeof(allocator_t) == PAGE_SIZE, allocator_must_fit_to_a_page);
_static_assert(
    ARRAY_LEN(((allocator_t*)0)->free_bits) == ALLOCATOR_NEEDED_BITS,
    free_bits_should_be_equal_to_allocator_need_bits);
_static_assert(
    ARRAY_LEN(((allocator_t*)0)->headers) == ALLOCATOR_HEADER_COUNT,
    headers_size_check);

_static_assert(sizeof(sock_addr_in_t) == 16, sock_addr_in_should_be_16bytes);

/* Its aligned to 24 from 20 */
_static_assert(sizeof(linux_dirent64_t) == 24, linux_dirent64_should_be_20bytes);

_static_assert(sizeof(heap_header_t) % 16 == 0, heap_header_t_must_align_to_16bytes);

_static_assert(sizeof(fs_stat_t) % 16 == 0, fs_stat_t_must_align_to_16bytes);
_static_assert(sizeof(fs_stat_t) == ((sizeof(void*) == 8) ? 18*8 : 4*20), fs_stat_t_size_check);

_static_assert(sizeof(thread_ctrl_t) % 16 == 0, thread_ctrl_t_must_align_to_16bytes);
_static_assert(sizeof(thread_ctrl_t) == 16, thread_ctrl_t_must_be_16_bytes);

_static_assert(sizeof(sock_addr_t) % 16 == 0, sock_addr_t_must_align_to_16bytes);
_static_assert(sizeof(sock_addr_t) == 16, sock_addr_t_must_be_16_bytes);

_static_assert(sizeof(time_t) % 16 == 0, time_t_must_align_to_16bytes);
_static_assert(sizeof(time_t) == 16, time_t_must_be_16_bytes);

_static_assert(sizeof(__type_test_slice) == 16, slices_are_same_with_iovecs_size_should_be_same);

_static_assert(success == 0, success_must_be_zero);
_static_assert(success == false, success_must_equal_to_false);

void __flibc_struct_member_check_function(void);
void __flibc_struct_member_check_function(void)
{
    /* Checking for def_da_t with can_be_da types */
    _struct_member_check(def_da_t, __type_test_da, items);
    _struct_member_check(def_da_t, __type_test_da, count);
    _struct_member_check(def_da_t, __type_test_da, capacity);

    /* Checking for def_da_t with slice_dummy_t */
    _struct_member_check(def_da_t, slice_dummy_t, items);
    _struct_member_check(def_da_t, slice_dummy_t, count);

    /* Checking for slice_dummy_t with can_be_slice types */
    _struct_member_check(slice_dummy_t, __type_test_slice, items);
    _struct_member_check(slice_dummy_t, __type_test_slice, count);

    /* sock_addr_in_t's members should never change its baked so */
    _struct_member_baked(sock_addr_in_t, family, u16, 0);
    _struct_member_baked(sock_addr_in_t, port, u16, 2);
    _struct_member_baked(sock_addr_in_t, addr, u32, 4);
    _struct_array_baked(sock_addr_in_t, zeros, u8, 8, 8);

    /* linux_dirent64_t's members should never change its baked so */
    _struct_member_baked(linux_dirent64_t, d_ino, u64, 0);
    _struct_member_baked(linux_dirent64_t, d_off, i64, 8);
    _struct_member_baked(linux_dirent64_t, d_reclen, u16, 16);
    _struct_member_baked(linux_dirent64_t, d_type, u8, 18);
    _struct_array_baked(linux_dirent64_t, d_name, char, 1, 19);

    /* fs_stat_t's members should never change its baked so */
    _struct_member_baked(fs_stat_t, st_dev, usz, 0);
    _struct_member_baked(fs_stat_t, st_ino, usz, 1*sizeof(usz));
    _struct_member_baked(fs_stat_t, st_nlink, usz, 2*sizeof(usz));
    _struct_member_baked(fs_stat_t, st_mode, u32, 3*sizeof(usz));
    _struct_member_baked(fs_stat_t, st_uid, u32, 3*sizeof(usz) + 1*sizeof(u32));
    _struct_member_baked(fs_stat_t, st_gid, u32, 3*sizeof(usz) + 2*sizeof(u32));
    _struct_member_baked(fs_stat_t, __pad0, u32, 3*sizeof(usz) + 3*sizeof(u32));
    _struct_member_baked(fs_stat_t, st_rdev, usz, 3*sizeof(usz) + 4*sizeof(u32));
    _struct_member_baked(fs_stat_t, st_size, ssz, 4*sizeof(usz) + 4*sizeof(u32));
    _struct_member_baked(fs_stat_t, st_blksize, ssz, 5*sizeof(usz) + 4*sizeof(u32));
    _struct_member_baked(fs_stat_t, st_blocks, ssz, 6*sizeof(usz) + 4*sizeof(u32));
    _struct_member_baked(fs_stat_t, st_atime, usz, 7*sizeof(usz) + 4*sizeof(u32));
    _struct_member_baked(fs_stat_t, st_atime_nsec, usz, 8*sizeof(usz) + 4*sizeof(u32));
    _struct_member_baked(fs_stat_t, st_mtime, usz, 9*sizeof(usz) + 4*sizeof(u32));
    _struct_member_baked(fs_stat_t, st_mtime_nsec, usz, 10*sizeof(usz) + 4*sizeof(u32));
    _struct_member_baked(fs_stat_t, st_ctime, usz, 11*sizeof(usz) + 4*sizeof(u32));
    _struct_member_baked(fs_stat_t, st_ctime_nsec, usz, 12*sizeof(usz) + 4*sizeof(u32));
    _struct_array_baked(fs_stat_t, __unused, ssz, 3, 13*sizeof(usz) + 4*sizeof(u32));

    /* thread_ctrl_t used in assembly so we need to check them too */
    _struct_member_baked(thread_ctrl_t, done, volatile ssz, 0);
    _struct_member_baked(thread_ctrl_t, ret_val, volatile ssz, sizeof(u64));

    /* sock_addr_t's members should never change its baked so */
    _struct_member_baked(sock_addr_t, family, u16, 0);
    _struct_array_baked(sock_addr_t, data, u8, 14, 2);

    /* time_t's members should never change its baked so */
    _struct_member_baked(time_t, sec, u64, 0);
    _struct_member_baked(time_t, nsec, u64, 8);

}

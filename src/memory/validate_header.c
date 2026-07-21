#include "memory_private.h"

error_t __validate_header
(heap_header_t* header)
{
    error_t res = success;
    usz null = 0;
    bool is_null = false, are_same = false;

    return ((void)(
        /* Check null case */
        (res = (header) ? success : invalid_pointer) ||
        /* We give aligned pointer so we expect aligned pointer */
        (res = (header->alloc && ((uintptr_t)header % 16 == 0)) ? success : invalid_pointer) ||
        /* Check the safety string */
        (res = mem_cmp_raw(header->safety, __FLIBC_MEMORY_HEADER_SAFETY,
                           sizeof(header->safety), &are_same)) ||
            ((!are_same || (header->first_null != 0)) /* should be dead end - underflow case */
                ? (header->alloc->meta.underflow(header->alloc, header), res = heap_underflow)
                : (res = success)) ||
        /* Check the last null - Used mem_cmp_raw to avoid alignment issues */
        (res = mem_cmp_raw(((u8*)(header + 1) + header->wanted_alloc), &null, sizeof(null), &is_null)) ||
            ((!is_null) /* should be dead end - overflow case*/
                ? (header->alloc->meta.overflow(header->alloc, header), res = heap_overflow)
                : (res = success))
    ), res);
}

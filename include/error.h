#ifndef __FLIBC_ERROR_H__
#define __FLIBC_ERROR_H__

enum fc_error_e {
    fce_success = 0,

    fce_mem_malloc_zero,
    fce_mem_malloc_nullptr,
    fce_mem_malloc_mmap_failed,

    fce_mem_free_munmap_failed,

    fce_mem_memset_nullptr,

    fce_mem_memcmp_nullptr,

    fce_mem_memcpy_smaller,
    fce_mem_memcpy_nullptr,

    fce_mem_memmove_smaller,
    fce_mem_memmove_nullptr,

    fce_mem_realloc_nullptr,
    fce_mem_realloc_invalid,

    fce_mem_memswap_nullptr,
    fce_mem_memswap_diffsize,

    fce_mem_throw_to_heap_out_nullptr,
    fce_mem_throw_to_heap_in_nullptr,
    fce_mem_throw_to_heap_zero_size,

    fce_da_reserve_nullptr,
    fce_da_reserve_zero_nsize,
    fce_da_reserve_zero_amount,

    fce_da_unordered_remove_nullptr,
    fce_da_unordered_remove_zero_nsize,
    fce_da_unordered_remove_out_of_bounds,

    fce_da_swap_nullptr,
    fce_da_swap_zero_nsize,
    fce_da_swap_lhs_out_of_bounds,
    fce_da_swap_rhs_out_of_bounds,

    fce_da_insert_da_nullptr,
    fce_da_insert_in_nullptr,
    fce_da_insert_zero_nsize,
    fce_da_insert_out_of_bounds,

    fce_da_remove_nullptr,
    fce_da_remove_zero_nsize,
    fce_da_remove_out_of_bounds,

    fce_da_pop_nullptr,
    fce_da_pop_zero_nsize,
    fce_da_pop_out_of_bounds,

    fce_ssp_fail
};

typedef enum fc_error_e fc_error_t;

#endif /* __FLIBC_ERROR_H__ */

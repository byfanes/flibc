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

    fce_fopen_failed,
    fce_fopen_name_nullptr,
    fce_fopen_out_nullptr,
    fce_fopen_invalid_type,

    fce_fflush_partial,
    fce_fflush_nullptr,
    fce_fflush_failed,
    fce_fflush_got_read_file,

    fce_fwrite_nullptr,
    fce_fwrite_got_read_file,

    fce_fread_file_nullptr,
    fce_fread_buf_nullptr,
    fce_fread_failed,
    fce_fread_partial,
    fce_fread_got_unreadable_file,

    fce_fclose_nullptr,
    fce_fclose_failed,

    fce_formatf_unknown,
    fce_formatf_fmt_null,
    fce_formatf_out_null,

    fce_sprintf_small_buffer,

    fce_fseek_failed,
    fce_fseek_nullptr,
    fce_fseek_invalid_type,

    fce_str_from_cstr_out_null,
    fce_str_from_cstr_cstr_null,

    fce_str_to_cstr_out_null,

    fce_strdup_out_null,
    fce_strdup_base_null,

    fce_strcat_base_null,
    fce_strcat_extend_null,

    fce_strcat_sl_not_utf8,
    fce_strcat_sl_base_null,

    fce_is_utf8_sl_out_null,

    fce_streq_out_null,

    fce_str_utf8len_out_null,

    fce_sl_utf8len_invalid_utf8,

    fce_ssp_fail
};

typedef enum fc_error_e fc_error_t;

#endif /* __FLIBC_ERROR_H__ */

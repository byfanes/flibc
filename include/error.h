#ifndef __FLIBC_ERROR_H__
#define __FLIBC_ERROR_H__

enum fc_error_e {
    fce_success = 0,
    
    fce_mem_malloc_zero,
    fce_mem_malloc_nullptr,
    fce_mem_malloc_mmap_failed,

    fce_mem_free_munmap_failed,

    fce_mem_memset_nullptr,

    fce_mem_memcmp_diffsize,
    fce_mem_memcmp_nullptr,

    fce_mem_memcpy_smaller,
    fce_mem_memcpy_nullptr,

    fce_mem_memmove_smaller,
    fce_mem_memmove_nullptr,

    fce_mem_realloc_nullptr,
    fce_mem_realloc_shrink,

    fce_da_truncate_nullptr,
    fce_da_zeroed_nullptr,

    fce_da_get_outofbounds,
    fce_da_get_nullptr,
};

typedef enum fc_error_e fc_error_t;

#endif /* __FLIBC_ERROR_H__ */

#ifndef __FLIBC_ERROR_H__
#define __FLIBC_ERROR_H__

#ifdef __cplusplus
extern "C" {
#endif

enum fc_error_e {
    /* Default value which is success and set to zero */
    fce_success = 0,

    /* Generic Error Values */
    fce_null_pointer,
    fce_invalid_pointer,
    fce_invalid_argument,
    fce_out_of_bounds,
    fce_small_buffer,
    fce_invalid_utf8,
    fce_elsize_zero,

    /* Specific Errors */
    fce_invalid_realloc,
    fce_memswap_diffsize,
    fce_invalid_slice_assignment,
    fce_formatf_unknown_format,

    /* System Errors */
    fce_memory_error,
    fce_time_error,
    fce_io_error,
    fce_io_partial,
    fce_io_invalid_op,

    /* Fatal Errors */
    fce_ssp_fail
};

typedef enum fc_error_e fc_error_t;

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_ERROR_H__ */

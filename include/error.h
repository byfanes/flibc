#ifndef __FLIBC_ERROR_H__
#define __FLIBC_ERROR_H__

#ifdef __cplusplus
extern "C" {
#endif

enum error_e {
    /* Default value which is success and set to zero */
    success = 0,

    /* Generic Error Values */
    null_pointer,
    heap_overflow,
    heap_underflow,
    invalid_pointer,
    invalid_argument,
    invalid_address,
    out_of_bounds,
    small_buffer,
    invalid_utf8,
    elsize_zero,

    /* Specific Errors */
    invalid_realloc,
    memswap_diffsize,
    invalid_slice_assignment,
    formatf_unknown_format,
    does_not_exist,
    exceeding_memory_allocation,

    /* System Errors */
    memory_error,
    process_error,
    proc_child_failed,
    time_error,
    fs_error,
    socket_error,
    io_error,
    io_partial,
    io_invalid_op,
    thread_failed,
    mutex_error,
    connection_closed,

    /* Fatal Errors */
    ssp_fail,

    /* This is for users to inherit the error_t
     * for example:
     * enum user_error_e {
     *     success = 0
     *     __start_of_user_error = __flibc_error_count
     *     my_error,
     *     my_other_error,
     * }
     */
    __flibc_error_count
};

typedef enum error_e error_t;

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_ERROR_H__ */

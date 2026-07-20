#ifndef __OS_PRIVATE_H__
#define __OS_PRIVATE_H__

/* Note: All function in here assumed to be only used internally so
 * no argument checks done here
 */

/* In this current version everything design for linux syscalls so
 * when we are implementing windows or any other os layer those function
 * apis may change
 */

#include "error.h"
#include "os.h"

#define MAX_TRY_COUNT 16

#if (SYS_OS == SYS_OS_LINUX) && (SYS_ARCH == SYS_ARCH_X86_64)
#include "os_table_linux_x86_64.h"
#endif /* SYS_OS == SYS_OS_LINUX && SYS_ARCH == SYS_ARCH_X86_64 */

enum os_file_std_type_e {
    os_file_stdin = 0,
    os_file_stdout = 1,
    os_file_stderr = 2
};

/* Private types */
typedef enum os_file_std_type_e os_file_std_type_t;
typedef struct sl_cstr_s os_slcstr_t;

/* Use the same types from the public layer to avoid duplication */
typedef enum file_type_e os_file_type_t;
typedef enum seek_type_e os_seek_type_t;
typedef struct sock_addr_s os_saddr_t;
typedef struct time_s os_time_t;

typedef void*       os_outptr_t;
typedef const void* os_inptr_t;
typedef ccstr_t     os_cstr_t;
typedef cstr_t      os_outcstr_t;

struct std_s;

/* TODO: Add tls */
struct os_thread_s {
    volatile void* ret_val;
    volatile i32 tid;

    union {
        f_std_thread_func with;
        f_thread_func without;
    } std_funcs;

    struct std_s *std;
    void *arg;
};

/* This function will differ for each operating system */
/* It takes the normal value without the negative sign */
error_t __os_error_map(ssz code);

noreturn __os_exit(ssz code);

/* Set will be zeroed in case of fail */
error_t __os_memory_alloc(void *set, usz alloc_size);
error_t __os_memory_free(void *set, usz free_size);
/* TODO: __os_memory_protect */

error_t __os_file_write(os_fid_t fid, os_inptr_t buf, usz count);
error_t __os_file_read(os_fid_t fid, os_outptr_t buf, usz count, usz *read_count);
error_t __os_file_seek(os_fid_t fid, usz off, os_seek_type_t type, usz *out);
/* Set will be set to invalid handle in case of fail */
error_t __os_file_open(os_fid_t *set, os_cstr_t path, os_file_type_t type);
error_t __os_file_get_std(os_fid_t *set, os_file_std_type_t type);
error_t __os_file_close(os_fid_t *set);

error_t __os_file_remove(os_cstr_t path);

error_t __os_cwd_set(os_cstr_t path);
error_t __os_cwd_get(os_outcstr_t path, usz size, usz *wrote);

error_t __os_dir_list_dir(os_slcstr_t* path,
 void (*callback)(os_slcstr_t *path, os_slcstr_t *name, bool is_dir, void* arg),
 void* arg);

error_t __os_dir_create(os_cstr_t path);
error_t __os_dir_remove(os_cstr_t path);

error_t __os_path_rename(os_cstr_t from, os_cstr_t to);
error_t __os_path_exists(os_cstr_t path, bool *out);

error_t __os_time_now(os_time_t *out);
error_t __os_time_sleep_ms(u64 ms);

/* For consistency and error chaining purposes they are returning an error */
error_t __os_addr_wait_i32(volatile i32 *addr, i32 expected);
error_t __os_addr_wait_u32(volatile u32 *addr, u32 expected);
error_t __os_addr_wake_i32(volatile i32 *addr);
error_t __os_addr_wake_all_u32(volatile u32 *addr);
error_t __os_thread_cond_signal(volatile u32 *addr);
error_t __os_thread_yield(void);
error_t __os_thread_join(os_tid_t *set, void **ret_val);
/* TODO: Use clone3 in linux instead */
error_t __os_thread_new
(os_tid_t *set, f_std_thread_func func, struct std_s *std, void *arg);

noreturn __os_thread_dispatcher(os_tid_t thread);

error_t __os_system_exec(os_cstr_t cmd, os_cstr_t *envp);
error_t __os_process_run(os_cstr_t cmd, os_cstr_t *env, ssz *exit_code);
error_t __os_process_spawn(os_cstr_t cmd, os_cstr_t *env, os_pid_t *out);
error_t __os_process_wait(os_pid_t pid, ssz *exit_code);
error_t __os_process_wait_any_on_list(const os_pid_t *list, usz count, const os_pid_t **found, ssz *code);

error_t __os_socket_close(os_sid_t *sid);
error_t __os_socket_create(os_sid_t *sid, u16 family, u16 type, u32 protocol);
error_t __os_socket_listen(os_sid_t sid, usz count);
error_t __os_socket_connect(os_sid_t sid, os_saddr_t *addr);
error_t __os_socket_accept(os_sid_t sid, os_pid_t *out, os_saddr_t *addr);
error_t __os_socket_bind(os_sid_t sid, os_saddr_t *addr);
error_t __os_socket_read(os_sid_t sid, os_outptr_t buf, usz count, usz *read_count);
error_t __os_socket_write(os_sid_t sid, os_inptr_t buf, usz count);

#endif /* __OS_PRIVATE_H___H__ */

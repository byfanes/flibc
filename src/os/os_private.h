#ifndef __OS_PRIVATE_H__
#define __OS_PRIVATE_H__

/* Right now this module is an internal modules so it does not
 * have a public header however we still use private naming here
 * both for consistency and for the case if we need to make a public
 * header in the future
 */

/* Note: All function in here assumed to be only used internally so
 * no argument checks done here
 */

/* In this current version everything design for linux syscalls so 
 * when we are implementing windows or any other os layer those function
 * apis may change
 */
 
#include "error.h"
#include "base.h"
#include "syscall.h"

#define MAX_TRY_COUNT 16

#if SYS_OS == SYS_OS_LINUX

typedef ssz os_fid_t;
typedef ssz os_pid_t;
typedef ssz os_sid_t;

#endif/* SYS_OS == SYS_OS_LINUX */

#define OS_INVALID_FILE_HANDLE ((os_fid_t)(-1))

#if (SYS_OS == SYS_OS_LINUX) && (SYS_ARCH == SYS_ARCH_X86_64)
#include "os_table_linux_x86_64.h"
#endif /* SYS_OS == SYS_OS_LINUX && SYS_ARCH == SYS_ARCH_X86_64 */

/* Note: This should be same as io.h file_type enum we are duplicating it
 * to avoid a new public header or a dependcy in os layer this enum is
 * checked inside the type_checks.c to be safe
 */
enum os_file_type_e {
    os_file_read,
    os_file_write,
    os_file_append,
    os_file_read_plus,
    os_file_write_plus,
    os_file_append_plus
};

enum os_seek_type_e {
    os_seek_set = 0,
    os_seek_cur = 1,
    os_seek_end = 2
};

enum os_file_std_type_e {
    os_file_stdin = 0,
    os_file_stdout = 1,
    os_file_stderr = 2
};

typedef enum os_file_type_e os_file_type_t;
typedef enum os_seek_type_e os_seek_type_t;
typedef enum os_file_std_type_e os_file_std_type_t;
typedef struct os_time_s os_time_t;
typedef struct thread_ctrl_s thread_ctrl_t;
typedef struct os_slu8_s os_slu8_t;
typedef struct os_saddr_s os_saddr_t;

struct std_s;

struct os_saddr_s {
    /* family is sock_family_t but because of the alignment we use u16 here */
    u16 family;
    u8 data[14];
};

struct os_slu8_s {
    char *items;
    usz count;
};

struct os_time_s {
    u64 sec;
    u64 nsec;
};

/* We use ssz for both variables for alignment */
struct thread_ctrl_s {
    volatile ssz done;
    volatile ssz ret_val;
};

/* This function will differ for each operating system */
/* It takes the normal value without the negative sign */
error_t __os_error_map(ssz code);

noreturn __os_exit(ssz code);

/* Set will be zeroed in case of fail */
error_t __os_memory_alloc(void *set, usz alloc_size);
error_t __os_memory_free(void *set, usz free_size);
/* TODO: __os_memory_protect */

error_t __os_file_write(os_fid_t handle, const void *buf, usz count);
error_t __os_file_read(os_fid_t handle, void *buf, usz count, usz *read_count);
error_t __os_file_seek(os_fid_t handle, usz off, os_seek_type_t type, usz *out);
/* Set will be set to invalid handle in case of fail */
error_t __os_file_open(os_fid_t *set, const char *path, os_file_type_t type);
error_t __os_file_get_std(os_fid_t *set, os_file_std_type_t type);
error_t __os_file_close(os_fid_t *set);

error_t __os_file_remove(const void *path);

error_t __os_cwd_set(const void *path);
error_t __os_cwd_get(void *path, usz size, usz *wrote);

error_t __os_dir_list_dir(os_slu8_t* path,
 void (*callback)(os_slu8_t *path, os_slu8_t *name, bool is_dir, void* arg),
 void* arg);

error_t __os_dir_create(const void *path);
error_t __os_dir_remove(const void *path);

error_t __os_path_rename(const void *from, const void *to);
error_t __os_path_exists(const void *path, bool *out);

error_t __os_time_now(os_time_t *out);
error_t __os_time_sleep_ms(u64 ms);

/* For consistency and error chaining purposes they are returning an error */
error_t __os_addr_wait_i32(volatile i32 *addr, i32 expected);
error_t __os_addr_wait_u32(volatile u32 *addr, u32 expected);
error_t __os_addr_wake_i32(volatile i32 *addr);
error_t __os_addr_wake_all_u32(volatile u32 *addr);
error_t __os_thread_cond_signal(volatile u32 *addr);
error_t __os_thread_yield(void);
error_t __os_thread_join(void **thread_handle, void **ret_val);
error_t __os_thread_new
(void **thread_handle, void *(*func)(struct std_s *, void *), struct std_s *std, void *arg);

error_t __os_system_exec(const char *cmd, const char **envp);
error_t __os_process_run(const char *cmd, const char **env, ssz *exit_code);
error_t __os_process_spawn(const char *cmd, const char **env, os_pid_t *out);
error_t __os_process_wait(os_pid_t pid, ssz *exit_code);
error_t __os_process_wait_any_on_list(const os_pid_t *list, usz count, const os_pid_t **found, ssz *code);

error_t __os_socket_close(os_sid_t *sid);
error_t __os_socket_create(os_sid_t *sid, u16 family, u16 type, u32 protocol);
error_t __os_socket_listen(os_sid_t sid, usz count);
error_t __os_socket_connect(os_sid_t sid, os_saddr_t *addr);
error_t __os_socket_accept(os_sid_t sid, os_pid_t *out, os_saddr_t *addr);
error_t __os_socket_bind(os_sid_t sid, os_saddr_t *addr);
error_t __os_socket_read(os_sid_t sid, void *buf, usz count, usz *read_count);
error_t __os_socket_write(os_sid_t sid, const void *buf, usz count);

#endif /* __OS_PRIVATE_H___H__ */

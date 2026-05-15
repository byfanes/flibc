#ifndef __FLIBC_FS_H__
#define __FLIBC_FS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "memory.h"
#include "string.h"
#include "time.h"
#include "da.h"

typedef str_t path_t;
typedef struct fs_stat_s fs_stat_t;
can_be_da(str_t);

/* TODO: This is not cross-platform like other functions
 * This struct has been stolen from linux kernel
 */
struct fs_stat_s {
    u16 st_dev;
    u16 st_ino;
    u16 st_mode;
    u16 st_nlink;
    u16 st_uid;
    u16 st_gid;
    u16 st_rdev;
    u32 st_size;
    u32 st_atime;
    u32 st_mtime;
    u32 st_ctime;
};

fc_error_t path_exists(path_t* p, bool* out);
fc_error_t path_rename(path_t* from, path_t* to);
fc_error_t path_cwd_set(path_t* p);
fc_error_t path_cwd_get(allocator_t* alloc, path_t* p);

fc_error_t path_size(path_t* p, usize_t* out);
fc_error_t path_mtime(path_t* p, time_t* out);
fc_error_t path_stat(path_t* p, fs_stat_t* out);

fc_error_t path_is_absolute(path_t* p, bool* out);
fc_error_t path_is_relative(path_t* p, bool* out);
fc_error_t path_is_dir(path_t* p, bool* out);
fc_error_t path_is_file(path_t* p, bool* out);

fc_error_t dir_remove(path_t* path);
fc_error_t dir_exists(path_t* path, bool* out);
fc_error_t dir_mkdir(path_t* path);
fc_error_t dir_mkdir_ifnot_exists(path_t* path);

fc_error_t file_remove(path_t* path);
fc_error_t file_exists(path_t* path, bool* out);

fc_error_t file_copy(allocator_t* alloc, path_t* from, path_t* to);
fc_error_t file_read_all(allocator_t* alloc, path_t* path, da(u8)* out);

/* TBD
 * fc_error_t file_read_lines(allocator_t* alloc, path_t* path, da(str_t)* out);
 * fc_error_t path_dirname(path_t* p, path_t* out);
 * fc_error_t path_basename(path_t* p, path_t* out);
 * fc_error_t dir_list_dir(path_t* path, void (*callback)(const char*, bool, void*), void* arg);
 * fc_error_t dir_remove_recursive(path_t* path);
 */
 
#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_FS_H__ */

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

can_be_da(path_t);

/* TODO: This is not cross-platform like other functions
 * This struct has been stolen from linux kernel
 */
struct fs_stat_s {
    usize_t st_dev;
    usize_t st_ino;
    usize_t st_nlink;
    u32     st_mode;
    u32     st_uid;
    u32     st_gid;
    u32     __pad0;
    usize_t st_rdev;
    ssize_t st_size;
    ssize_t st_blksize;
    ssize_t st_blocks;

    usize_t st_atime;
    usize_t st_atime_nsec;
    usize_t st_mtime;
    usize_t st_mtime_nsec;
    usize_t st_ctime;
    usize_t st_ctime_nsec;

    ssize_t __unused[3];
};

error_t path_exists(path_t* p, bool* out);
error_t path_rename(path_t* from, path_t* to);
error_t path_cwd_set(path_t* p);
error_t path_cwd_get(allocator_t* alloc, path_t* p);

error_t path_size(path_t* p, usize_t* out);
error_t path_mtime(path_t* p, time_t* out);
error_t path_stat(path_t* p, fs_stat_t* out);

error_t path_join(path_t* path, slice(u8)* extend);
error_t path_change_ext(path_t* path, slice(u8)* ext);

error_t is_path_absolute(path_t* p, bool* out);
error_t is_path_relative(path_t* p, bool* out);
error_t is_path_dir(path_t* p, bool* out);
error_t is_path_file(path_t* p, bool* out);

error_t dir_remove(path_t* path);
error_t dir_exists(path_t* path, bool* out);
error_t dir_mkdir(path_t* path);
error_t dir_mkdir_ifnot_exists(path_t* path);

error_t file_remove(path_t* path);
error_t file_exists(path_t* path, bool* out);

error_t file_copy(allocator_t* alloc, path_t* from, path_t* to);
error_t file_read_all(allocator_t* alloc, path_t* path, da(u8)* out);

error_t path_ext(path_t* base, path_t* out);
error_t path_basename(path_t* base, path_t* out);

/* TODO: This is bad and inefficient */
error_t path_get_all_files(path_t* p, da(path_t)* out);
error_t dir_list_dir(path_t* path,
   void (*callback)(sl_cstr_t* path, sl_cstr_t name, bool is_dir, void* arg), void* arg);

/* TBD
 * error_t file_read_lines(allocator_t* alloc, path_t* path, da(str_t)* out);
 * error_t path_dirname(path_t* p, path_t* out);
 * error_t dir_remove_recursive(path_t* path);
 */

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_FS_H__ */

#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX && SYS_ARCH == SYS_ARCH_X86_64

static u32 __os__helper_linux_file_type
(u32 mode)
{
    switch (mode & S_IFMT) {
    case S_IFREG:  return fs_file_regular;
    case S_IFDIR:  return fs_file_directory;
    case S_IFLNK:  return fs_file_symlink;
    case S_IFCHR:  return fs_file_char_device;
    case S_IFBLK:  return fs_file_block_device;
    case S_IFIFO:  return fs_file_fifo;
    case S_IFSOCK: return fs_file_socket;
    default:       return fs_file_unknown;
    }
}

static u32 __os__helper_linux_file_perm
(u32 mode)
{
    u32 out = 0;

    if (mode & S_IRUSR) out |= FS_STAT_MODE_UR;
    if (mode & S_IWUSR) out |= FS_STAT_MODE_UW;
    if (mode & S_IXUSR) out |= FS_STAT_MODE_UX;

    if (mode & S_IRGRP) out |= FS_STAT_MODE_GR;
    if (mode & S_IWGRP) out |= FS_STAT_MODE_GW;
    if (mode & S_IXGRP) out |= FS_STAT_MODE_GX;

    if (mode & S_IROTH) out |= FS_STAT_MODE_OR;
    if (mode & S_IWOTH) out |= FS_STAT_MODE_OW;
    if (mode & S_IXOTH) out |= FS_STAT_MODE_OX;

    return out;
}

error_t __os_path_stat
(os_cstr_t path, os_stat_generic_t *out)
{
    /* Init variables */
    ssz ret = 0;
    linux_stat64_t stat = {0};

    /* Note: Out expected to be already zeroed */

    ret = syscall_2_linux(syscall_stat, (ssz)path, (ssz)&stat);
    /* Check the return */
    if (ret < 0 && ret >= -MAX_ERRNO)
    { return __os_error_map(ret); }

    /* Set the generic struct */
    out->dev    = stat.st_dev;
    out->ino    = stat.st_ino;
    out->nlink  = stat.st_nlink;

    out->type = __os__helper_linux_file_type(stat.st_mode);
    out->perm = __os__helper_linux_file_perm(stat.st_mode);

    out->uid = stat.st_uid;
    out->gid = stat.st_gid;

    out->rdev = stat.st_rdev;

    out->size    = stat.st_size;
    out->blksize = stat.st_blksize;
    out->blocks  = stat.st_blocks;

    out->atime.sec  = stat.st_atime;
    out->atime.nsec = stat.st_atime_nsec;

    out->mtime.sec  = stat.st_mtime;
    out->mtime.nsec = stat.st_mtime_nsec;

    out->ctime.sec  = stat.st_ctime;
    out->ctime.nsec = stat.st_ctime_nsec;

    /* Traditional stat() doesn't provide birth time */
    out->btime.sec  = 0;
    out->btime.nsec = 0;

    /* Set valid data */
    out->valid =
        FS_STAT_VALID_TYPE   |
        FS_STAT_VALID_UID    |
        FS_STAT_VALID_GID    |
        FS_STAT_VALID_PERM   |
        FS_STAT_VALID_RDEV   |
        FS_STAT_VALID_BLOCKS |
        FS_STAT_VALID_BLKSIZE |
        FS_STAT_VALID_CTIME;

    return success;
}

#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */

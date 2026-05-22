#include "fs_private.h"

/* TODO: This is not cross-platform like other functions
 * This struct has been stolen from linux kernel
 */
typedef struct linux_dirent64_s linux_dirent64_t;
struct linux_dirent64_s {
    u64 d_ino;
    i64 d_off;
    u16 d_reclen;
    u8 d_type;
    char d_name[1];
};

error_t dir_list_dir
(path_t* path, void (*callback)(const char* name, bool is_dir, void* arg), void* arg)
{
    /* Init variables */
    ssize_t fd = 0, nread = 0, bpos = 0;
    error_t res = success;
    u8 buf[FLIBC_STACK_THRESHOLD] = {0};
    char *name = 0;
    linux_dirent64_t *d = 0;

    /* Check inputs */
    if(!callback) { return null_pointer; }
    if((res = str_add_shadow_null(path))) { return res; }

    /* Open directory via syscall */
    fd = syscall_4_linux(syscall_openat,
        AT_FDCWD, path->items, O_RDONLY | O_DIRECTORY, 0);

    /* Check return of the syscall */
    if(fd < 0) { return fs_error; }

    /* Iterate over the directory until its finished */
    for(;;) {

        /* Get information from the syscall */
        nread = syscall_3_linux(syscall_getdents64, fd, (ssize_t)buf, sizeof(buf));
        /* Check for error and end */
        if(nread == 0) { res = success; goto end; }
        if(nread < 0) { res = fs_error; goto end; }

        /* Start again */
        bpos = 0;

        /* Iterate */
        while(bpos < nread) {
            /* Set dirent and set name */
            d = (linux_dirent64_t*)(buf + bpos);
            /* C89 does not support flexible arrays so we cast it
             * from char[1] to null terminated cstr
             */
            name = d->d_name;

            /* Ignore linux's default previous and current directories */
            if(cstreq(name, ".") || cstreq(name, ".."))
            { bpos += d->d_reclen; continue; }

            /* Call back to users function */
            callback(name, (d->d_type == DT_DIR), arg);

            /* Skip to next part */
            bpos += d->d_reclen;
        }
    }

end:
    /* Close the directory and finish */
    syscall_1_linux(syscall_close, fd);
    return res;
}


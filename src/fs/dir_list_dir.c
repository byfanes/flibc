#include "fs_private.h"

/* Update the callback*/
error_t dir_list_dir
(path_t* path,
 void (*callback)(sl_cstr_t* path, sl_cstr_t* name, bool is_dir, void* arg),
 void* arg)
{
    /* Init variables */
    ssz fd = 0, nread = 0, bpos = 0;
    error_t res = success;
    u8 buf[FLIBC_STACK_THRESHOLD] = {0};
    char *name = nullptr;
    linux_dirent64_t *d = nullptr;
    sl_u8_t name_sl = {0};

    /* Check inputs */
    if(!callback) { return null_pointer; }
    if((res = str_add_shadow_null(path))) { return res; }

    /* Open directory via syscall */
    fd = syscall_4_linux(syscall_openat,
        AT_FDCWD, (ssz)path->items, O_RDONLY | O_DIRECTORY, 0);

    /* Check return of the syscall */
    if(fd < 0) { return fs_error; }

    /* Iterate over the directory until its finished */
    for(;;) {

        /* Get information from the syscall */
        nread = syscall_3_linux(syscall_getdents64, fd, (ssz)buf, sizeof(buf));
        /* Check for error and end */
        if(nread == 0) { res = success; goto end; }
        if(nread < 0) { res = fs_error; goto end; }

        /* Start again */
        bpos = 0;

        /* Iterate */
        while(bpos < nread) {
            /* Set dirent and set name */
            d = (linux_dirent64_t*)(uintptr_t)(buf + bpos);
            /* C89 does not support flexible arrays so we cast it
             * from char[1] to null terminated cstr
             */
            name = d->d_name;

            /* Ignore linux's default previous and current directories */
            if(cstr_eq(name, ".") || cstr_eq(name, ".."))
            { bpos += d->d_reclen; continue; }

            slice_set_cstr(&name_sl, name);

            /* Call back to users function */
            callback((sl_cstr_t*)path, &name_sl, (d->d_type == DT_DIR), arg);

            /* Skip to next part */
            bpos += d->d_reclen;
        }
    }

end:
    /* Close the directory and finish */
    syscall_1_linux(syscall_close, fd);
    return res;
}

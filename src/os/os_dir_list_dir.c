#include "os_private.h"

#if SYS_OS == SYS_OS_LINUX

extern error_t slice_set_cstr(void* sl, const char* str);
extern bool cstr_eq(const char* l, const char* r);

error_t __os_dir_list_dir
(os_slcstr_t *path,
 void (*callback)(os_slcstr_t *path, os_slcstr_t *name, bool is_dir, void* arg),
 void* arg)
{
    ssz dd = 0, nread = 0, bpos = 0;
    u8 buf[MAX_PATH] = {0};
    linux_dirent64_t *d = nullptr;
    error_t res = success;
    char *name = nullptr;
    os_slcstr_t name_sl = {0};
    
    /* Open directory via syscall */
    dd = syscall_4_linux(syscall_openat, AT_FDCWD, (ssz)path->items, O_RDONLY | O_DIRECTORY, 0);

    /* Check the return */
    if(0 > dd && dd >= -MAX_ERRNO) { return __os_error_map(dd); }

    for(;;) {
        /* Get information from the syscall */
        nread = syscall_3_linux(syscall_getdents64, dd, (ssz)buf, sizeof(buf));

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
            callback(path, &name_sl, (d->d_type == DT_DIR), arg);

            /* Skip to next part */
            bpos += d->d_reclen;
        }
        
    }

end:
    /* Close the directory and finish */
    syscall_1_linux(syscall_close, dd);
    return res;
}


#else /* End - SYS_OS_LINUX */
#error "The current platform does not have a backend yet!"
#endif /* SYS_OS */

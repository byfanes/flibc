#ifndef __FLIBC_PROCESS_H__
#define __FLIBC_PROCESS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "da.h"
#include "fs.h"
#include "crt.h"

typedef str_t cmd_t;
typedef struct proc_s proc_t;

/* We might need to add new things here so making it a struct is better */
struct proc_s {
    ssize_t handle;
};

can_be_da(proc_t, da_proc_t);

/* Those functions expect null terminated string */
error_t system_run_cstr_envp(const char* cmd, char** envp);
error_t system_run_cstr(const char* cmd);

error_t system_run_env(cmd_t cmd, env_t env);
error_t system_run(cmd_t cmd);

error_t proc_run(cmd_t cmd, env_t env);
error_t proc_spawn(cmd_t cmd, env_t env, da_proc_t* procs);
error_t proc_spawn_fixed(cmd_t cmd, env_t env, da_proc_t* procs);
error_t proc_wait(da_proc_t* procs);

error_t cmd_append(cmd_t* cmd, sl_u8_t* sl);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_PROCESS_H__ */

#ifndef __FLIBC_PROCESS_H__
#define __FLIBC_PROCESS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "da.h"
#include "fs.h"
#include "std.h"
#include "os.h"

typedef str_t cmd_t;
typedef os_pid_t proc_t;

can_be_da(os_pid_t, da_proc_t);

/* Those functions expect null terminated string */
error_t system_run_cstr_envp(const char* cmd, const char** envp);
error_t system_run_cstr(const char* cmd);

error_t system_run_env(cmd_t* cmd, env_t* env);
error_t system_run(cmd_t* cmd);

error_t proc_run(cmd_t* cmd, env_t* env, ssz *code);
error_t proc_spawn(cmd_t* cmd, env_t* env, da_proc_t* procs);
error_t proc_spawn_fixed(cmd_t* cmd, env_t* env, da_proc_t* procs, ssz *code);
error_t proc_wait(da_proc_t* procs, da_ssz_t *codes);

error_t cmd_append(cmd_t* cmd, sl_u8_t* sl);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_PROCESS_H__ */

#ifndef __FLIBC_THREADS_H__
#define __FLIBC_THREADS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"
#include "memory.h"
#include "atomics.h"
#include "std.h"

typedef struct thread_cond_s thread_cond_t;
typedef struct thread_s thread_t;
typedef struct mutex_s mutex_t;

/* TODO: We might add stack data structure */
/* TODO: We should add block data struct to keeping the same addres while growing the list */

can_be_da(thread_t, da_thread_t);
can_be_da(void*, da_retval_t);

error_t thread_cond_wait(thread_cond_t* cond, mutex_t* mutex);
error_t thread_cond_signal(thread_cond_t* cond);
error_t thread_cond_broadcast(thread_cond_t* cond);

error_t mutex_lock(mutex_t* mutex);
error_t mutex_unlock(mutex_t* mutex);

void thread_yield(void);
error_t thread_create_std
(thread_t *thread, void *(*func)(std_t *, void *), std_t *std,  void  *arg);
error_t thread_create(thread_t *thread, void *(*func)(void *), void *arg);

error_t thread_spawn_std
(da_thread_t *threads, void *(*func)(std_t *, void *), std_t *std, void *arg);
error_t thread_spawn(da_thread_t *threads, void *(*func)(void *), void *arg);

error_t thread_join(thread_t *thread, void **_Nullable ret_val);
error_t thread_join_da(da_thread_t *threads, da_retval_t *ret_vals);

#ifdef __cplusplus
}
#endif

#endif /* __FLIBC_THREADS_H__ */

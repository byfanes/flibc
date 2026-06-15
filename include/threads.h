#ifndef __THREADS_H__
#define __THREADS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdtypes.h"
#include "features.h"
#include "memory.h"
#include "atomics.h"
#include "crt.h"

/* 2 MB */
#define THREAD_STACK_SIZE 1024*1024*2

typedef struct thread_ctrl_s thread_ctrl_t;
typedef struct thread_s thread_t;
typedef struct mutex_s mutex_t;

/* TODO: We might add stack data structure */
/* TODO: We should add block data struct to keeping the same addres while growing the list */

can_be_da(thread_t, da_thread_t);
can_be_da(void*, da_retval_t);

/* We use ssz for both variables for alignment */
struct thread_ctrl_s {
    volatile ssz done;
    volatile ssz ret_val;
};

struct thread_s {
    ssz tid;
    thread_ctrl_t* ctrl;
};

struct mutex_s {
    volatile i32 state;
};

error_t mutex_lock(mutex_t* mutex);
error_t mutex_unlock(mutex_t* mutex);

void thread_yield(void);
error_t thread_create_std(std_t* std, thread_t* thread, void*(*func)(std_t*, void*), void* _Nullable arg);
error_t thread_create(allocator_t* alloc, thread_t* thread, void*(*func)(void*), void* _Nullable arg);

error_t thread_spawn_std(std_t* std, da_thread_t* threads, void*(*func)(std_t*, void*), void* _Nullable arg);
error_t thread_spawn(allocator_t* alloc, da_thread_t* threads, void*(*func)(void*), void* _Nullable arg);

error_t thread_join(thread_t* thread, void** _Nullable ret_val);
error_t thread_join_da(da_thread_t* threads, da_retval_t* ret_vals);

#ifdef __cplusplus
}
#endif

#endif /* __THREADS_H__ */

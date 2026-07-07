#ifndef __THREADS_PRIVATE_H__
#define __THREADS_PRIVATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "threads.h"
#include "syscall.h"

error_t __thread_new
(u8* stack_ptr, thread_t* thread, void*(*func)(std_t*, void*), std_t* std, void* arg);

#ifdef __cplusplus
}
#endif

#endif /* __THREADS_PRIVATE_H__ */

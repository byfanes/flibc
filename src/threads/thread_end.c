#include "threads_private.h"

void __thread_end(thread_t* t, void* ret);

/* This function is used in assembly for setting the thread_t safetly because
 * if the struct thread_s changes we need to change assembly to so we can just
 * do it in C and let the compiler handle the offsets
 */
void __thread_end
(thread_t* t, void* ret)
{
    t->ctrl->done = true;
    t->ctrl->ret_val = ret;
}

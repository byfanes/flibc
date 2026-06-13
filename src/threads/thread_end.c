#include "threads_private.h"

void __thread_end(thread_ctrl_t* ctrl, void* ret);

/* This function is used in assembly for setting the thread_t safetly because
 * if the struct thread_s changes we need to change assembly to so we can just
 * do it in C and let the compiler handle the offsets
 */
void __thread_end
(thread_ctrl_t* ctrl, void* ret)
{
    atomic_xchg_u32(&ctrl->done, 1);
    ctrl->ret_val = ret;
}

#include "threads_private.h"

void __thread_end(thread_ctrl_t* ctrl, void* ret);

/* This function is used in assembly for setting the thread_t safetly because
 * if the struct thread_s changes we need to change assembly to so we can just
 * do it in C and let the compiler handle the offsets
 */
void __thread_end
(thread_ctrl_t* ctrl, void* ret)
{
    /* Order of the writings is important here because if we write done
     * before the ret_val other threads may read wrong value
     */
    atomic_xchg_ssz(&ctrl->ret_val, (ssz)(uintptr_t)ret);
    atomic_xchg_ssz(&ctrl->done, 1);
}

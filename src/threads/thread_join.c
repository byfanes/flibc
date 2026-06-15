#include "threads_private.h"

error_t thread_join
(thread_t* thread, void** _Nullable ret_val)
{
    /* Init variables */
    error_t res = success;
    u8* ptr = 0;

    /* Check thread pointer */
    if(!thread) { return null_pointer; }

    /* Right now we rely on volatile behaviour but we might switch to atomics later */
    /* Check the cpu if its finished if not pass cpu back to os */
    while(!atomic_load_ssz(&thread->ctrl->done))
    { thread_yield(); }

    /* If user give a return value postion set it */
    if(ret_val) { *ret_val = (void*)(uintptr_t)thread->ctrl->ret_val; }

    ptr = (u8*)(thread->ctrl + 1) - THREAD_STACK_SIZE;

    /* Free the stack memory */
    if((res = free(&ptr))) { return res; }

    /* Zero the thread to avoid use after free */
    thread->tid = 0;
    thread->ctrl = nullptr;

    return success;
}

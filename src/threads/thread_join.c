#include "threads_private.h"

error_t thread_join
(thread_t* thread, void** _Nullable ret_val)
{
    /* Init variables */
    error_t res = success;

    /* Check thread pointer */
    if(!thread) { return null_pointer; }

    /* Right now we rely on volatile behaviour but we might switch to atomics later */
    /* Check the cpu if its finished if not pass cpu back to os */
    while(!thread->ctrl->done)
    { thread_yield(); }

    /* If user give a return value postion set it */
    if(ret_val) { *ret_val = (void*)thread->ctrl->ret_val; }

    /* Free the stack memory */
    if((res = free(&thread->stack))) { return res; }

    /* Zero the thread to avoid use after free */
    thread->tid = 0;
    thread->ctrl = nullptr;

    return success;
}

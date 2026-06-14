#include "threads_private.h"

/* This is a internal function so we dont check inputs */
error_t __thread_new
(u8* stack_ptr, thread_t* thread, void*(*func)(std_t*, void*), std_t* std, void* arg)
{
    /* Init variables */
    ssize_t ret = 0;

    /* Set thread control postion to retrive retval and done flags later */
    thread->ctrl = (thread_ctrl_t*)(uintptr_t)(stack_ptr + THREAD_STACK_SIZE - sizeof(thread_ctrl_t));

    /* Set thread control to defaults */
    thread->ctrl->done = false;
    thread->ctrl->ret_val = nullptr;

    /* Create the new thread */
    ret = thread_clone_linux(THREAD_FLAGS, stack_ptr + THREAD_STACK_SIZE - sizeof(thread_ctrl_t),
        func, std, arg);

    /* Check if its a error */
    if(ret < 0) {
        /* Set it back to zero */
        free(&stack_ptr);
        thread->ctrl = nullptr;
        thread->tid = 0;
        return thread_failed;
    }

    /* Set the thread id */
    thread->tid = ret;
    return success;
}

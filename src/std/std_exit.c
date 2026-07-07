#include "std_private.h"

_Noreturn void std_exit
(std_t* std, ssz code)
{
    /* Init variables */
    usz i = 0;

    /* Slice pointers are constant so we cast to void* to avoid compiler errors and normaly
    * slices should not be used for holding pointers in heap
    */
    /* TODO: Use malloc_sl and free_sl */
    if(mem_free((void*)(uintptr_t)&std->args.items))
    { __std_early_panic("STD Exit Panic: Could not free the args slice!\n"); }

    /* Free the env variables */
    for(i = 0; i < std->env.vars.count; ++i) {
        if(str_deinit(&std->env.vars.items[i].continues))
        { __std_early_panic("STD Exit Panic: Could not free an environment variable!\n"); }
    }

    /* Deinit environment variables */
    if(da_deinit(&std->env.vars))
    { __std_early_panic("STD Exit Panic: Could not free the environment variable dynamic array!\n"); }
    if(da_deinit(&std->env.list))
    { __std_early_panic("STD Exit Panic: Could not free the environment variable list!\n"); }

    /* Close the standard files */
    if(io_close(&std->io.in))
    { __std_early_panic("STD Exit Panic: Could not close standard input file!\n"); }
    if(io_close(&std->io.out))
    { __std_early_panic("STD Exit Panic: Could not close standard output file!\n"); }
    if(io_close(&std->io.err))
    { __std_early_panic("STD Exit Panic: Could not close standard error file!\n"); }

    /* Free default allocator */
    if(allocator_deinit(&std->alloc))
    { __std_early_panic("STD Exit Panic: Could not free the allocator!\n"); }

    /* Exit from the program */
    syscall_1_linux(syscall_exit, code);
    __unreachable();
}

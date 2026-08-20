#include "std_private.h"

void std_deinit
(std_t *std)
{
    /* Init variables */
    usz i = 0;

    /* If its a nullptr return */
    if(!std) { return; }

    /* Free the slice list */
    if(mem_free_sl(&std->args))
    { __helper_panic("STD Exit Panic: Could not free the args slice!\n"); }

    /* Free the env variables */
    for(i = 0; i < std->env.vars.count; ++i) {
        if(str_deinit(&std->env.vars.items[i].continues))
        { __helper_panic("STD Exit Panic: Could not free an environment variable!\n"); }
    }

    /* Deinit environment variables */
    if(da_deinit(&std->env.vars))
    { __helper_panic("STD Exit Panic: Could not free the environment variable dynamic array!\n"); }
    if(da_deinit(&std->env.list))
    { __helper_panic("STD Exit Panic: Could not free the environment variable list!\n"); }

    /* Close the standard files */
    if(io_close(&std->io.in))
    { __helper_panic("STD Exit Panic: Could not close standard input file!\n"); }
    if(io_close(&std->io.out))
    { __helper_panic("STD Exit Panic: Could not close standard output file!\n"); }
    if(io_close(&std->io.err))
    { __helper_panic("STD Exit Panic: Could not close standard error file!\n"); }

    /* Free default allocator */
    if(allocator_deinit(&std->alloc))
    { __helper_panic("STD Exit Panic: Could not free the allocator!\n"); }

    return;
}

#include "std_private.h"

noreturn std_exit
(std_t* std, ssz code)
{
    /* Init variables */
    usz i = 0;

    /* Free the slice list */
    /* TODO: This will be a bug because in a normal startup we use stack rather than heap */
    /* TODO: It is closed because of that */
    if(0 && mem_free_sl(&std->args))
    { __panic("STD Exit Panic: Could not free the args slice!\n"); }

    /* Free the env variables */
    for(i = 0; i < std->env.vars.count; ++i) {
        if(str_deinit(&std->env.vars.items[i].continues))
        { __panic("STD Exit Panic: Could not free an environment variable!\n"); }
    }

    /* Deinit environment variables */
    if(da_deinit(&std->env.vars))
    { __panic("STD Exit Panic: Could not free the environment variable dynamic array!\n"); }
    if(da_deinit(&std->env.list))
    { __panic("STD Exit Panic: Could not free the environment variable list!\n"); }

    /* Close the standard files */
    if(io_close(&std->io.in))
    { __panic("STD Exit Panic: Could not close standard input file!\n"); }
    if(io_close(&std->io.out))
    { __panic("STD Exit Panic: Could not close standard output file!\n"); }
    if(io_close(&std->io.err))
    { __panic("STD Exit Panic: Could not close standard error file!\n"); }

    /* Free default allocator */
    if(allocator_deinit(&std->alloc))
    { __panic("STD Exit Panic: Could not free the allocator!\n"); }

    /* Exit from the program */
    __os_exit(code);
}

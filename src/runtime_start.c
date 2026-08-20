#include "std.h"
#include "base.h"
#include "helpers/helpers.h"
#include "std/std_private.h"

/* Declared in ssp.c used here */
extern void __flibc_stack_chk_init(s32 argc, char **argv);

/* This function will be called from assembly */
noreturn __flibc_runtime_start(s32 argc, char** argv);
noreturn __flibc_runtime_start
(s32 argc, char** argv)
{
    /* Init variables */
    error_t ret = 0;
    std_t std = {0};

    /* Set the stack check variable */
    __flibc_stack_chk_init(argc, argv);

    /* Setup std things like in/out/err and args & env variables */
    /* TODO: Even though we use out entry we allocate the
     *       argv list in heap which can be slow
     */
    std_from_args(&std, argc, argv);

    /* Call the main function and execute the user program */
    ret = main(&std);

    /* Exit from the program and close all std variables */
    std_exit(&std, ret);
}

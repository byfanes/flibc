#include "std.h"
#include "base.h"
#include "syscall.h"
#include "helpers/helpers.h"
#include "std/std_private.h"

/* This function will be called from assembly */
noreturn __flibc_runtime_start(i32 argc, char** argv);
noreturn __flibc_runtime_start
(i32 argc, char** argv)
{
    /* Init variables */
    error_t ret = 0;
    std_t std = {0};
    sl_u8_t args[MAX_ARGS_COUNT] = {0};

    /* Setup std things like in/out/err and args & env variables */
    __std_from_args(&std, argc, argv, args);

    /* Call the main function and execute the user program */
    ret = main(&std);

    /* Exit from the program and close all std variables */
    std_exit(&std, ret);
}

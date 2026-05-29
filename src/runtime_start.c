#include "crt.h"
#include "features.h"
#include "stdlib.h"
#include "syscall.h"
#include "stdtypes.h"
#include "helpers/helpers.h"

/* Linux start */
void _start(void);

#define MAX_ARGS_COUNT 256

static void early_panic
(const char* msg)
{
    /* Ignore its failure because we will close the program after it */
    syscall_3_linux(syscall_write, UNIX_STDERR, (ssize_t)msg, (ssize_t)strlen(msg));
    exit(255);
}

/* This function will be called from assembly */
void runtime_start(usize_t argc, char** argv);
void runtime_start
(usize_t argc, char** argv)
{
    /* Init variables */
    error_t ret = 0;
    usize_t i = 0;
    sl_u8_t args[MAX_ARGS_COUNT] = {0}, *args_ptr = 0;
    std_t std = {0};
    char **envp = 0, *env_cstr = 0;
    u32 envc = 0, eq_idx = 0;
    sl_u8_t val_sl = {0}, key_sl = {0};

    /* Check argc and get first of them which is path to executable */
    if(argc > 0) {
        set_slice(&std.exe, argv[0], strlen(argv[0]));
        argv++; argc--;
    }

    /* Set default allocator */
    if(allocator_init(&std.alloc))
    { early_panic("CTR Panic: Allocator failed to init!\n"); }

    /* Check for if its needed to allocate memory or not */
    if(argc > MAX_ARGS_COUNT) {
        if(malloc(std.alloc, sizeof(sl_u8_t) * (u32)argc, &args_ptr))
        { early_panic("CTR Panic: Could not allocate memory for args slice list!\n"); }
    } else {
        args_ptr = args;
    }

    /* Open standard files */
    if(fopen_stdin(std.alloc, &std.io.in))
    { early_panic("CTR Panic: Could not open standard input file!\n"); }
    if(fopen_stdout(std.alloc, &std.io.out))
    { early_panic("CTR Panic: Could not open standard output file!\n"); }
    if(fopen_stderr(std.alloc, &std.io.err))
    { early_panic("CTR Panic: Could not open standard error file!\n"); }

    /* Set slice for _args to parse now */
    set_slice(&std.args, args_ptr, (u32)argc);

    /* Set all of the arguments one by one */
    for(i = 0; i < argc; ++i) {
        set_slice(&std.args.items[i], argv[i], strlen(argv[i]));
    }

    /* Find how many environment variables passed 1 for skiping argv's last null */
    envp = (argv + 1 + argc);
    while(*envp) { envc++; envp++; }

    /* Init environment variables da with known size */
    if(da_init(std.alloc, &std.env.vars, envc))
    { early_panic("CRT Panic: Could not initialize environment variable dynamic array!\n"); }

    /* Init environment variable list which is like envp pointer which comes after stack */
    if(da_init(std.alloc, &std.env.list, envc))
    { early_panic("CRT Panic: Could not initialize environment variable list!\n"); }

    /* Start iterating over 1 for skiping argv's last null */
    envp = (argv + 1 + argc);
    envc = 0;
    while(*envp) {
        /* Set variables for loop */
        env_cstr = *envp;
        eq_idx = 0;

        /* Split string to corresponding pieces */
        /* TODO: We don’t support variables that are not assigned with “=” or separated by commas */
        while(env_cstr[eq_idx] && env_cstr[eq_idx] != '=') { eq_idx++; }
        set_slice(&key_sl, env_cstr, eq_idx);
        set_slice(&val_sl, &env_cstr[eq_idx + 1], strlen(env_cstr) - eq_idx);

        /* Add the new variable */
        if(env_add_var(std.alloc, &std.env, &key_sl, &val_sl))
        { early_panic("CRT Panic: Could not append an environment variable to dynamic array!\n"); }

        /* Shift to new variable for setting */
        envc++; envp++;
    }

    /* Call the main function and execute the user program */
    ret = main(std);

    /* Free if its needed */
    if(argc > MAX_ARGS_COUNT) {
        if(free(&args_ptr))
        { early_panic("CTR Panic: Could not free the args slice!\n"); }
    }

    for(i = 0; i < std.env.vars.count; ++i) {
        if(str_deinit(&std.env.vars.items[i].continues))
        { early_panic("CTR Panic: Could not free an environment variable!\n"); }
    }

    /* Deinit environment variables */
    if(da_deinit(&std.env.vars))
    { early_panic("CTR Panic: Could not free the environment variable dynamic array!\n"); }
    if(da_deinit(&std.env.list))
    { early_panic("CTR Panic: Could not free the environment variable list!\n"); }

    /* Close the standard files */
    if(fclose(&std.io.in))
    { early_panic("CTR Panic: Could not close standard input file!\n"); }
    if(fclose(&std.io.out))
    { early_panic("CTR Panic: Could not close standard output file!\n"); }
    if(fclose(&std.io.err))
    { early_panic("CTR Panic: Could not close standard error file!\n"); }

    /* Free default allocator */
    if(allocator_deinit(&std.alloc))
    { early_panic("CTR Panic: Could not free the allocator!\n"); }

    /* Exit from the program */
    exit(ret);
}

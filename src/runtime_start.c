#include "crt.h"
#include "features.h"
#include "stdlib.h"
#include "syscall.h"
#include "stdtypes.h"
#include "helpers/helpers.h"

/* Linux start */
void _start(void);

#define MAX_ARGS_COUNT 256
#define MAX_ENV_COUNT 256

static void early_panic
(slice_u8 msg)
{
    syscall_3(syscall_write, UNIX_STDERR, msg.base, (ssize_t)msg.count);
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
    slice(u8) args[MAX_ARGS_COUNT] = {0}, *args_ptr = 0, envps[MAX_ENV_COUNT] = {0};
    std_t std = {0};
    char** envp = 0;
    u32 envc = 0;

    /* Check argc and get first of them which is path to executable */
    if(argc > 0) {
        set_slice(&std.exe, argv[0], strlen(argv[0]));
        argv++; argc--;
    }

    /* Set default allocator */
    if(allocator_init(&std.alloc))
    { early_panic(cstr_to_u8sl("CTR Panic: Allocator failed to init!\n")); }

    /* Check for if its needed to allocate memory or not */
    if(argc > MAX_ARGS_COUNT) {
        if(malloc(std.alloc, sizeof(slice(u8)) * (u32)argc, &args_ptr))
        { early_panic(cstr_to_u8sl("CTR Panic: Could not allocate memory for args slice list!\n")); }
    } else {
        args_ptr = args;
    }

    /* Open standard files */
    if(fopen_stdin(std.alloc, &std.io.in))
    { early_panic(cstr_to_u8sl("CTR Panic: Could not open standard input file!\n")); }
    if(fopen_stdout(std.alloc, &std.io.out))
    { early_panic(cstr_to_u8sl("CTR Panic: Could not open standard output file!\n")); }
    if(fopen_stderr(std.alloc, &std.io.err))
    { early_panic(cstr_to_u8sl("CTR Panic: Could not open standard error file!\n")); }

    /* Set slice for _args to parse now */
    set_slice(&std.args, args_ptr, (u32)argc);

    /* Set all of the arguments one by one */
    for(; i < argc; ++i) {
        set_slice(&std.args.base[i], argv[i], strlen(argv[i]));
    }

    /* Skip null and start taking env */
    envp = (argv + 1);
    std.env.continues = envp;
    while(*envp) {
        set_slice(&envps[envc++], *envp, strlen(*envp));
        envp++;
    }
    set_slice(&std.env.items, envps, envc);

    /* Call the main function and execute the user program */
    ret = main(std);

    /* Free if its needed */
    if(argc > MAX_ARGS_COUNT) {
        if(free(&args_ptr))
        { early_panic(cstr_to_u8sl("CTR Panic: Could not free the args slice!\n")); }
    }

    /* Close the standard files */
    if(fclose(&std.io.in))
    { early_panic(cstr_to_u8sl("CTR Panic: Could not close standard input file!\n")); }
    if(fclose(&std.io.out))
    { early_panic(cstr_to_u8sl("CTR Panic: Could not close standard output file!\n")); }
    if(fclose(&std.io.err))
    { early_panic(cstr_to_u8sl("CTR Panic: Could not close standard error file!\n")); }

    /* Free default allocator */
    if(allocator_deinit(&std.alloc))
    { early_panic(cstr_to_u8sl("CTR Panic: Could not free the allocator!\n")); }

    /* Exit from the program */
    exit(ret);
}

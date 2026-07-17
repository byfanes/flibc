#include "std_private.h"

/* For stds which are different than __flibc_runtime_start's use heap memory */
void std_from_args
(std_t* std, i32 argc, char** argv)
{
    __std_from_args(std, argc, argv, nullptr);
}

/* args_ptr expected to be a nullptr or a valid sl_u8_t[MAX_ARGS_COUNT] */
void __std_from_args
(std_t* std, i32 argc, char** argv, sl_u8_t *args_ptr)
{
    /* Init varaibles */
    i32 i = 0;
    u32 envc = 0, eq_idx = 0;
    char **envp = nullptr, *env_cstr = nullptr;
    sl_u8_t key_sl = {0}, val_sl = {0};

    /* Check argc and get first of them which is path to executable */
    if(argc > 0) {
        slice_set(&std->exe, argv[0], cstr_len(argv[0]));
        argv++; argc--;
    }

    /* Set default allocator */
    if(allocator_init(&std->alloc))
    { __panic("STD Init Panic: Allocator failed to init!\n"); }

    /* TODO: Use malloc_sl and free_sl */
    /* Check for if its needed to allocate memory or not */
    if(args_ptr) {
        if(mem_alloc(std->alloc, &args_ptr, sizeof(sl_u8_t) * (u32)argc))
        { __panic("STD Init Panic: Could not allocate memory for args slice list!\n"); }
    }

    /* Open standard files */
    if(io_open_stdin(std->alloc, &std->io.in))
    { __panic("STD Init Panic: Could not open standard input file!\n"); }
    if(io_open_stdout(std->alloc, &std->io.out))
    { __panic("STD Init Panic: Could not open standard output file!\n"); }
    if(io_open_stderr(std->alloc, &std->io.err))
    { __panic("STD Init Panic: Could not open standard error file!\n"); }

    /* Set slice for _args to parse now */
    slice_set(&std->args, args_ptr, (u32)argc);

    /* Set all of the arguments one by one */
    for(i = 0; i < argc; ++i) {
        slice_set(&std->args.items[i], argv[i], cstr_len(argv[i]));
    }

    /* Find how many environment variables passed 1 for skiping argv's last null */
    envp = (argv + 1 + argc);
    while(*envp) { envc++; envp++; }

    /* Init environment variables da with known size */
    if(da_init(std->alloc, &std->env.vars, envc))
    { __panic("STD Init Panic: Could not initialize environment variable dynamic array!\n"); }

    /* Init environment variable list which is like envp pointer which comes after stack */
    if(da_init(std->alloc, &std->env.list, envc))
    { __panic("STD Init Panic: Could not initialize environment variable list!\n"); }

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
        slice_set(&key_sl, env_cstr, eq_idx);
        slice_set(&val_sl, &env_cstr[eq_idx + 1], cstr_len(env_cstr) - eq_idx);

        /* Add the new variable */
        if(env_add_var(std->alloc, &std->env, &key_sl, &val_sl)) {
            __panic(
                "STD Init Panic: Could not append an environment variable to dynamic array!\n"
            );
        }

        /* Shift to new variable for setting */
        envc++; envp++;
    }
}

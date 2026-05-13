#include "crt.h"
#include "features.h"

void _start(void);

INTERNAL u32 strlen
(const char* s)
{
    u32 i = 0;
    while(s[i++]) {}
    return i - 1;
}

#define MAX_ARGS_COUNT 256

void runtime_start(long *stack);
void runtime_start(long *stack)
{
    /* Init variables */
    int ret = 0;
    long i = 0, argc = stack[0];
    char **argv = (char **)(stack + 1);
    slice(u8) args[MAX_ARGS_COUNT] = {0}, *args_ptr = 0;
    std_t std = {0};

    /* Check argc and get first of them which is path to executable */
    if(argc > 0) {
        set_slice(&std.exe, argv[0], strlen(argv[0]));
        argv++; argc--;
    }

    /* Set default allocator */
    if(allocator_init(&std.alloc)) { exit(2); }

    /* Check for if its needed to allocate memory or not */
    if(argc > MAX_ARGS_COUNT) {
        if(malloc(std.alloc, sizeof(slice(u8)) * (u32)argc, &args_ptr)) { exit(3); }
    } else {
        args_ptr = args;
    }

    /* Open standard files */
    if(fopen_stdin(std.alloc, &std.io.in)) { exit(4); }
    if(fopen_stdout(std.alloc, &std.io.out)) { exit(5); }
    if(fopen_stderr(std.alloc, &std.io.err)) { exit(6); }

    /* Set slice for _args to parse now */
    set_slice(&std.args, args_ptr, (u32)argc);

    /* Set all of the arguments one by one */
    for(; i < argc; ++i) {
        set_slice(&std.args.base[i], argv[i], strlen(argv[i]));
    }

    /* Call the main function and execute the user program */
    ret = main(std);

    /* Free if its needed */
    if(argc > MAX_ARGS_COUNT) {
        if(free(&args_ptr)) { exit(7); }
    }

    /* Close the standard files */
    fclose(&std.io.in);
    fclose(&std.io.out);
    fclose(&std.io.err);

    /* Free default allocator */
    if(allocator_deinit(&std.alloc)) { exit(8); }

    /* Exit from the program */
    exit(ret);
}

__attribute__((naked, noreturn))
void _start(void)
{
    __asm__ volatile(
        "xor %rbp, %rbp\n"
        "mov %rsp, %rdi\n"
        "and $-16, %rsp\n"
        "call runtime_start\n"
        "hlt\n"
    );
}

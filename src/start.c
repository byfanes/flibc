#include "stdlib.h"
#include "stdio.h"
#include "memory/memory_private.h"

extern int main(stdio_t, slice_t, slice(slice_t));
void _start(void);

static u32 strlen
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
    slice_t args[MAX_ARGS_COUNT] = {0}, *args_ptr = 0, ext = {0};
    slice(slice_t) _args = {0};
    stdio_t stdio = {0};

    /* Check argc and get first of them which is path to executable */
    if(argc > 0) {
        set_slice(&ext, argv[0], strlen(argv[0]));
        argv++; argc--;
    }

    /* Check for if its needed to allocate memory or not */
    if(argc > MAX_ARGS_COUNT) {
        if(malloc(sizeof(slice_t) * (u32)argc, &args_ptr)) { exit(255); }
    } else {
        args_ptr = args;
    }

    /* Open standard files */
    if(fopen_stdin(&stdio.in)) { exit(255); }
    if(fopen_stdout(&stdio.out)) { exit(255); }
    if(fopen_stderr(&stdio.err)) { exit(255); }

    /* Set slice for _args to parse now */
    set_slice(&_args, args_ptr, (u32)argc);

    /* Set all of the arguments one by one */
    for(; i < argc; ++i) {
        set_slice(&args[i], argv[i], strlen(argv[i]));
    }

    /* Call the main function and execute the user program */
    ret = main(stdio, ext, _args);

    /* Free if its needed */
    if(argc > MAX_ARGS_COUNT) {
        if(free(&args_ptr)) { exit(255); }
    }
    
    /* Close the standard files */
    fclose(&stdio.in);
    fclose(&stdio.out);
    fclose(&stdio.err);

    /* Exit from the program */
    exit(ret);
}

__attribute__((naked, noreturn))
void _start(void)
{
    __asm__ volatile(
        "mov %rsp, %rdi\n"
        "call runtime_start\n"
    );
}

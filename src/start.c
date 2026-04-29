#include "stdlib.h"
#include "memory/memory_private.h"

extern int main(slice_t, slice(slice_t));
void _start(void);

static uint32_t strlen
(const char* s)
{
    uint32_t i = 0;
    while(s[i++]) {}
    return i - 1;
}

#define MAX_ARGS_COUNT 256

void runtime_start(long *stack);
void runtime_start(long *stack)
{
    long i = 0, argc = stack[0];
    char **argv = (char **)(stack + 1);
    
    slice(char) ext = {
        .base = (void*)argv[0],
        .count = strlen(argv[0])
    };
    argv++; argc--;

    slice_t args[MAX_ARGS_COUNT] = {0};
    slice_t* args_ptr = 0;
    
    if(argc > MAX_ARGS_COUNT) {
        if(malloc(sizeof(slice_t) * (uint32_t)argc, &args_ptr)) { exit(255); }
    } else {
        args_ptr = args;
    }
    slice(slice_t) _args = { args_ptr, (uint32_t)argc};
    
    for(; i < argc; ++i) {
        char* a = argv[i];
        args[i].base = a;
        __set_slice_count(args[i], strlen(a));
    }

    int ret = main(ext, _args);

    if(argc > MAX_ARGS_COUNT) {
        if(free(&args_ptr)) { exit(255); }
    }
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

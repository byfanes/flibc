#include "memory_private.h"
#include "error.h"
#include "syscall.h"

fc_error_t calloc
(uint32_t size, void* set)
{
    /* Init variables */
    fc_error_t res = fce_success;
    uint32_t i = 0; uint8_t *ptr = 0;
    
    /* Allocate memory - User input validation done here */
    if((res = malloc(size,set))) { return res; }

    /* Get the pointer back */
    ptr = *(void**)set;
    
    /* Zero-ed the memory */
    for(; i < size; ++i) { *(ptr++) = 0; }
    return res;
}

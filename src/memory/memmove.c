#include "memory.h"
#include "error.h"

fc_error_t memmove
(slice_t dst, slice_t src)
{
    /* Init variables */
    char *tmp = 0, *tmp2 = 0, buf[FLIBC_STACK_THRESHOLD] = {0};
    void *x_min, *x_max, *y_min, *y_max;
    fc_error_t res = fce_success;
    uint32_t i = 0;

    /* Validate user inputs */
    if(!dst.base || !src.base) { return fce_mem_memmove_nullptr; }
    if(src.count > dst.count) { return fce_mem_memmove_smaller; }

    /* Set colisions */
    x_min = dst.base;
    x_max = dst.base + dst.count;
    y_min = src.base;
    y_max = src.base + src.count;

    /* Use memcpy if the memories not over-lap each other */
    if(!(x_min <= y_max && x_max >= y_min)) { return memcpy(dst, src); }
    
    /* Allocate on stack (< 4KB) or heap (>= 4KB) */
    if(src.count <= FLIBC_STACK_THRESHOLD) { tmp = buf; }
    else { if((res = malloc(src.count,&tmp))) { return res; } }
    tmp2 = tmp;

    /* Allocate on stack (< 4KB) or heap (>= 4KB) */
    for(i = 0; i < src.count; ++i) { *(tmp++)  = *(src.base++); }
    for(i = 0; i < src.count; ++i) { *(dst.base++) = *(tmp2++); }

    /* Free the memory if its allocated */
    if(src.count > FLIBC_STACK_THRESHOLD) { return free(&tmp); }

    return fce_success;
}


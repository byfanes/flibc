#include "memory_private.h"
#include "error.h"

error_t __realloc
(allocator_t* alloc, usz n, void* set, TRACE_ARGS)
{
    /* Init variables */
    error_t res = success;
    heap_header_t *he = 0;
    u8 *ba = 0, *n_ba = 0;
    usz min = 0, i = 0, prev = 0;

    /* Validate user inputs */
    if(!set) { return null_pointer; }

    /* Get the pointer back */
    ba = *(void**)set;

    /* Act as free on new size is zero and has a pointer */
    if(ba && !n) { return free(set); }

    /* Validate user inputs */
    if(!n && !ba) { return invalid_realloc; }

    if(!ba) {
        /* set -> ptr(NULL) */
        return __malloc(alloc, n, set, USE_TRACE_ARGS);
    }
    /* set -> ptr(addr) -> data */
    he = (heap_header_t*)(void*)ba - 1;
    prev = he->wanted_alloc;

    /* Allocate new memory and set it*/
    if((res = __malloc(alloc, n, set, USE_TRACE_ARGS))) { return res; }

    /* Get the new pointer back */
    n_ba = *(void**)set;

    /* Get the min size for copying - shrinking */
    min = (prev > n) ? n : prev;

    /* Copy old data */
    for(; i < min; ++i ) { n_ba[i] = ba[i]; }

    /* Zero-ing the new part */
    for(; i < n; ++i ) { n_ba[i] = 0; }

    /* Free old part */
    return free(&ba);
 }

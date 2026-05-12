#include "memory_private.h"
#include "error.h"

fc_error_t realloc
(allocator_t* alloc, usize_t n, void* set)
{
    /* Init variables */
    fc_error_t res = fce_success;
    heap_header_t *he = 0;
    u8 *ba = 0, *n_ba = 0;
    usize_t min = 0, i = 0, prev = 0;

    /* Validate user inputs */
    if(!set) { return fce_null_pointer; }

    /* Get the pointer back */
    ba = *(void**)set;

    /* Act as free on new size is zero and has a pointer */
    if(ba && !n) { return free(set); }

    /* Validate user inputs */
    if(!n && !ba) { return fce_invalid_realloc; }

    if(!ba) {
        /* set -> ptr(NULL) */
        if((res = malloc(alloc, n, set))) { return res; }
        return res;
    }
    /* set -> ptr(addr) -> data */
    he = (heap_header_t*)(void*)ba - 1;
    prev = he->req_alloced;

    /* Allocate new memory and set it*/
    if((res = malloc(alloc, n, set))) { return res; }

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

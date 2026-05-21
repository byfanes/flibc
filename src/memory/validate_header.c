#include "memory_private.h"

bool __validate_header
(heap_header_t* header)
{
    if(!header) { return false; }
    
    /* Raw alloced is aligned to 64(CHUNK_SIZE) */
    if((header->raw_alloced & (CHUNK_SIZE - 1)) != 0)
    { return false; }

    /* align64(sum of req_alloc + header + usize_t(last_null)) should be
     * equal to raw because its calculated like that
     */
    if(ALIGN_64(header->req_alloced + sizeof(heap_header_t) + sizeof(usize_t)) != header->raw_alloced)
    { return false; }

    if(header->first_null != 0)
    { return false; }
    
    return true;
}

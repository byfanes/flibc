#include "memory.h"
#include "error.h"
#include "syscall.h"

fc_error_t fc_calloc
(uint32_t size, void** set)
{
    if(!size) { return fce_mem_malloc_zero; }
    if(!set) { return fce_mem_malloc_nullptr; }
    void* base = 0;
    heap_header_t header = {0};
    
    header.alloced = size;
    size += sizeof(header);
    size = (size + 7) & ~7;
    header.raw_alloced = size;

    base = (void*) syscall_6(syscall_mmap, 0, size, (PROT_READ|PROT_WRITE),
        (MAP_PRIVATE|MAP_ANONYMOUS), -1, 0);

    if(base == MMAP_FAILED)
    { return fce_mem_malloc_mmap_failed; }
    *(heap_header_t*)base = header;
    char* ptr = (char*)((heap_header_t*)base + 1);
    *set = ptr;
    for(uint32_t i = 0; i < size; ++i) {
        *(ptr++) = 0;
    }
    return fce_success;
}

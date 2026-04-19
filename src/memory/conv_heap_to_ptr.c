#include "memory.h"

void conv_heap_to_ptr
(void* ptr,def_slice_t* s)
{
    heap_header_t* head = 0;
    memcpy_sized(&head, ptr, sizeof(void*));
    memcpy_sized(&s->base, ptr, sizeof(void*));
    head--;
    memcpy_sized((void*)&s->count,&head->alloced,sizeof(s->count));
}

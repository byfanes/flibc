#ifndef __FLIBC_MEMORY_PRIVATE_H__
#define __FLIBC_MEMORY_PRIVATE_H__

#include "memory.h"
#include "syscall.h"
#include "../helpers/helpers.h"

#define ALIGN_64(n) ((n + 63) & (u64)(~63))

/* Every chunk is 64 bytes */
#define CHUNK_SIZE 64

/* 1 MB for allocation and header for allocatorx*/
#define ALLOCATION_SIZE (1024*1024)
#define RAW_ALLOCATION_SIZE (ALLOCATION_SIZE + sizeof(allocator_t))

#define CHUNK_MAX (ALLOCATION_SIZE / CHUNK_SIZE)

#define CHUNK_IDX_FAILED 0xFFFFFFFF

typedef struct heap_header_s heap_header_t;

/* To access 'allocator_t*' we can use chunk_idx for that because
 * every header is snap to grid and begins in new chunks' begining
 * this allows us to use less memory because we will add two null
 * bytes to start and end which ends up with sizeof(heap_header_t) + sizeof(u16)(last one)
 */
struct heap_header_s {
    const char* file_name;
    u32 req_alloced;
    u32 raw_alloced;
    u32 line;
    u16 chunk_idx;
    /* This should be last one */
    u16 first_null;
};

/* For the pointer to free use allocators' pointer not any other one and
 * for the user base pointer to give user some memory you can use this pointer again
 * but jumping 1 allocator ahead to access it then do all of the stuff
 */
struct allocator_s {
    /* Allocators' heap chunk size should be 1024*1024 = 1 MiB
     * So we should have 16384 chunks so we can store it in 16384 bit
     * That converts to 2048 bytes
     */
    u8 free_bits[CHUNK_MAX / 8];
};

/* A temporary structure for setting the const slices
 * the items order and size should be same with the other slices
 */
typedef struct slice_dummy_s slice_dummy_t;
struct slice_dummy_s {
    u8 *base;
    usize_t count;
};

/* We can make some function pointers in allocator_t via that
 * in fuctions like malloc/calloc etc we can use custom allocators too.
 */
fc_error_t allocator_get_from_ptr(void* ptr, allocator_t** set);
fc_error_t allocator_alloc_pointer
(allocator_t* alloc, usize_t n, void* set, const char* file_name, usize_t line);
fc_error_t allocator_free_pointer(allocator_t* alloc, void* set);

void __set_chunks_free(u8* bitmap_bytes, u32 start_bit, u32 n);
void __set_chunks_used(u8* bitmap_bytes, u32 start_bit, u32 n);
u32 __find_free_chunks(u8* bitmap_bytes, u32 total_bits, u32 n);
bool __validate_header(heap_header_t* header);

#endif /* __FLIBC_MEMORY_PRIVATE_H__ */

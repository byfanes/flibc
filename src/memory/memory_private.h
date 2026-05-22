#ifndef __FLIBC_MEMORY_PRIVATE_H__
#define __FLIBC_MEMORY_PRIVATE_H__

#include "memory.h"
#include "syscall.h"
#include "../helpers/helpers.h"

#define ALIGN_64(n) ((n + 63) & (u64)(~63))

/* Assuming a normal OS' page size is 4KB */
#define PAGE_SIZE (1024*4)

/* Every chunk is 64 bytes */
#define CHUNK_SIZE 64

/* 1 MB for allocation and header for allocator */
#define ALLOCATION_SIZE (1024*1024)
#define RAW_ALLOCATION_SIZE (ALLOCATION_SIZE + sizeof(allocator_t))

#define CHUNK_MAX (ALLOCATION_SIZE / CHUNK_SIZE)

/* We give it a big number so if we use it without
 * any checking we can segfault if it happens
 */
#define CHUNK_IDX_FAILED 0xFFFFFFFF

/* This calculation is for how many bits we need
 * to allocate so we can control over all the chunks
 * Allocators' heap chunk size should be 1024*1024 = 1 MiB
 * So we should have 16384 chunks so we can store it in 16384 bit
 * That converts to 2048 bytes
 */
#define ALLOCATOR_NEEDED_BITS (CHUNK_MAX / 8)

/* This calculation for needed node count we need to
 * update this calculation every time we change allocator struct
 * basicly we have a page(4KB) for the allocator struct we use
 * 5 pointers inside it (next - init - deinit - alloc_pointer - free_pointer)
 * functions and u32 (which is flags) and last one is check bits which is u8[ALLOCATOR_NEEDED_BITS]
 * and diveding this number with a node size gives use the amount usable nodes in an allocator
 */
#define ALLOCATOR_NODE_COUNT \
((PAGE_SIZE - (sizeof(void*)*5 + sizeof(u32) + sizeof(u8[ALLOCATOR_NEEDED_BITS]))) \
    / sizeof(heap_node_t))

typedef struct heap_header_s heap_header_t;

/* TODO: this struct can be compressed a little bit more */
struct heap_header_s {
    allocator_t* alloc;
    const char* file_name;
    bool is_raw_chunk;
    u32 req_alloced;
    u32 raw_alloced;
    u32 line;
    u16 chunk_idx;
    /* This should be last one */
    usize_t first_null;
};

/* We make this as an enum rather than bool because
 * we might need more types in the future
 */
enum heap_node_type_e {
    /* This is for checking a node is empty or not because
     * when we are creating we init all of them with 0
     */
    heap_node_empty,
    /* raw_chunk_allocation is used when user wants to do more than
     * (ALLOCATION_SIZE / 16) which is (1024*64) bytes of allocation
     */
    raw_chunk_allocation
};

typedef enum heap_node_type_e heap_node_type_t;
typedef struct heap_node_s heap_node_t;

struct heap_node_s {
    heap_node_type_t type;
    void* start;
};

/* Some typedefs to keep clean the struct definition */
typedef error_t (*f_allocator_alloc_pointer)
     (allocator_t* alloc, usize_t n, void* set, const char* file_name, usize_t line);

typedef error_t (*f_allocator_free_pointer)(allocator_t* alloc, void* set);
typedef error_t (*f_allocator_init)(allocator_t** set);
typedef error_t (*f_allocator_deinit)(allocator_t** set);

/* For the pointer to free use allocators' pointer not any other one and
 * for the user base pointer to give user some memory you can use this pointer again
 * but jumping 1 allocator ahead to access it then do all of the stuff
 */
/* Note: If the struct is change do not forget to update the calculations for
 * 'ALLOCATOR_NODE_COUNT' and 'ALLOCATOR_NEEDED_BITS'
 */
struct allocator_s {
    /* Next allocator for if current allocator fills up and we need more space
     * every allocator handled via its previous one
     */
    allocator_t* next;

    /* If user wants to implement their allocator they should add those functions and
     * set it in allocator
     */
    f_allocator_alloc_pointer alloc_pointer;
    f_allocator_free_pointer free_pointer;
    f_allocator_init init;
    f_allocator_deinit deinit;

    /* We can support up to 32 flags right now */
    u32 flags;

    /* We expect a OS should 4KB as page size its not mandatory but it aligns better
     * Look up for the 'ALLOCATOR_NODE_COUNT' calculation before modifying this array
     * since its a small sized array (167 - 253 (depending on arch)) we can iterate
     * over them because we indicate free nodes via 'heap_node_empty' which is zero
     */
    heap_node_t nodes[ALLOCATOR_NODE_COUNT];

    /* Look up for 'ALLOCATOR_NEEDED_BITS' before changing this array */
    u8 free_bits[ALLOCATOR_NEEDED_BITS];
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
error_t allocator_alloc_pointer
(allocator_t* alloc, usize_t n, void* set, const char* file_name, usize_t line);
error_t allocator_free_pointer(allocator_t* alloc, void* set);

void __set_chunks_free(u8* bitmap_bytes, u32 start_bit, u32 n);
void __set_chunks_used(u8* bitmap_bytes, u32 start_bit, u32 n);
u32 __find_free_chunks(u8* bitmap_bytes, u32 total_bits, u32 n);
bool __validate_header(heap_header_t* header);

#endif /* __FLIBC_MEMORY_PRIVATE_H__ */

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

#define CHUNK_IDX_FAILED 0xFFFFFFFF

#define MAX_NODE_COUNT \
    sizeof(((allocator_t*)(0))->nodes)/sizeof(((allocator_t*)(0))->nodes[0])

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

    /* For making nodes are whole numbers we need to pad it with architecture size and
     * we add up to 4KB which is a whole page and this memory can be used for different things 
     */
    ssize_t padding;
    
    u32 flags;

    /* Note: We can truncate it down to u8 because max size is 252(12 byte case) or 166(8 byte case)
     * which is enough to store in u8 right now we are not doing anything
     * with that memory so we just combined it with node_count to ensure padding
     */
    /* We use u32 explicitly because it maps better when we calculate the size
     * which left to nodes array which is 2016 bytes and its easy align to
     * 8(u32(enum) + ptr(u32)) or 12(u32(enum) + ptr(u64))
     * max count is for this number is 166(12 byte case) or 252(8 byte case)
     */
    u32 node_count;
     
    /* We expect a OS should 4KB as page size its not mandatory but it aligns better  
     * We use 2KB of that memory to free/use states of chunks 8 bytes to node_count
     * and the part which is left (2016(64 bit arch) or 1992(32 bit arch) bytes) used in nodes array
     */
    heap_node_t nodes[PAGE_SIZE - (sizeof(u8[CHUNK_MAX / 8]) + sizeof(u64)) / sizeof(heap_node_t)];
     
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
error_t allocator_alloc_pointer
(allocator_t* alloc, usize_t n, void* set, const char* file_name, usize_t line);
error_t allocator_free_pointer(allocator_t* alloc, void* set);

void __set_chunks_free(u8* bitmap_bytes, u32 start_bit, u32 n);
void __set_chunks_used(u8* bitmap_bytes, u32 start_bit, u32 n);
u32 __find_free_chunks(u8* bitmap_bytes, u32 total_bits, u32 n);
bool __validate_header(heap_header_t* header);

#endif /* __FLIBC_MEMORY_PRIVATE_H__ */

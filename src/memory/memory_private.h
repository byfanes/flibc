#ifndef __FLIBC_MEMORY_PRIVATE_H__
#define __FLIBC_MEMORY_PRIVATE_H__

#include "memory.h"
#include "threads.h"
#include "../helpers/helpers.h"
#include "../os/os_private.h"

#define ALIGN_64(n) ((n + 63) & (unsigned)(~63))

/* Every chunk is 64 bytes */
#define CHUNK_SIZE 64

/* 1 MB for allocation and header for allocator */
#define ALLOCATION_SIZE (1024*1024)
#define RAW_ALLOCATION_SIZE (ALLOCATION_SIZE + sizeof(allocator_t))

#define CHUNK_MAX (ALLOCATION_SIZE / CHUNK_SIZE)

#define RAW_ALLOCATION_THRESHOLD (ALLOCATION_SIZE / 16)
#define ADDITIONAL_HEADER_SIZE (sizeof(heap_header_t) + sizeof(usz))

/* We give it a big number so if we use it without
 * any checking we can segfault if it happens
 */
#define CHUNK_IDX_FULL ((u16)-1)

/* This calculation is for how many bits we need
 * to allocate so we can control over all the chunks
 * Allocators' heap chunk size should be 1024*1024 = 1 MiB
 * So we should have 16384 chunks so we can store it in 16384 bit
 * That converts to 2048 bytes
 */
#define ALLOCATOR_NEEDED_BITS (CHUNK_MAX / 8)

/* Allocators' meta data stored in a different struct so we can use that struct
 * and decouple somethings and make it little bit safer
 */
#define ALLOCATOR_HEADER_COUNT \
    ((PAGE_SIZE - sizeof(allocator_meta_t) - ALLOCATOR_NEEDED_BITS) \
    / sizeof(heap_header_t*))


typedef struct heap_header_s heap_header_t;
typedef struct allocator_meta_s allocator_meta_t;

/* For used chunk count use we can align wanted_alloc to (CHUNK_SIZE) and divide to (CHUNK_SIZE) */
/* For checking if its raw allocation we can either use wanted and compare
 * to THRESHOLD or we can check its allocator and look for the current
 * header's pointer in headers list
 */
/* Safety array is set to ABCDEF... for checking */
/* Note: If we need more elements in here we might truncate some bytes from safety */
struct heap_header_s {
    allocator_t* alloc;
    const char* file_name;
    u32 line;
    u32 wanted_alloc;
    u16 idx;

    u8 safety[sizeof(void*) + 6];
    /* This should be last one */
    usz first_null;
};

/* Some typedefs to keep clean the struct definition */
typedef error_t (*f_allocator_alloc_pointer)
     (allocator_t* alloc, usz n, void* set, const char* file_name, usz line);

typedef error_t (*f_allocator_free_pointer)(allocator_t* alloc, void* set);
typedef error_t (*f_allocator_init)(allocator_t** set);
typedef error_t (*f_allocator_deinit)(allocator_t** set);

typedef noreturn (*f_allocator_detect_underflow)(allocator_t* alloc, heap_header_t* header);
typedef noreturn (*f_allocator_detect_overflow)(allocator_t* alloc, heap_header_t* header);

/* TODO: We can make allocator faster via using allocated elements' headers
 * Every header has wanted_alloc which we can use to calculate chunk count allocated
 * by that header and skip to next part and if that is full too do something so on
 * so forth until we find new free chunks or we get to end of the allocator's heap
 * so continue with next allocator
 */

struct allocator_meta_s {
    /* Next allocator for if current allocator fills up and we need more space
     * every allocator handled via its previous one
     */
    allocator_t* next;

    u32 flags;

    /* TODO: Lock mutex for the whole allocation time this will slow the allocator a
     * lot because every operation uses same allocator and even if we move to
     * child allocator the parent allocator still be locked until
     * child allocator finishes
     */
    mutex_t mutex;

    /* If user wants to implement their allocator they should add those functions and
     * set it in allocator
     */
    f_allocator_alloc_pointer alloc_pointer;
    f_allocator_free_pointer free_pointer;
    f_allocator_init init;
    f_allocator_deinit deinit;

    /* They might be useless but we can detect it so might as well use it
     * Note: Those functions can yap a lot because used in both get and free
     * functions and which are called a lot in DAs
     */
    f_allocator_detect_overflow overflow;
    f_allocator_detect_underflow underflow;
 };

/* For the pointer to free use allocators' pointer not any other one and
 * for the user base pointer to give user some memory you can use this pointer again
 * but jumping 1 allocator ahead to access it then do all of the stuff
 */
/* Note: If the struct is change do not forget to update the calculations for
 * 'ALLOCATOR_HEADER_COUNT' and 'ALLOCATOR_NEEDED_BITS'
 */
struct allocator_s {
    allocator_meta_t meta;

    /* We expect a OS should 4KB as page size its not mandatory but it aligns better
     * Look up for the 'ALLOCATOR_HEADER_COUNT' calculation before modifying this array
     * since its a small sized array (248 - 503 (depending on arch)) we can iterate
     * over them because zero means its empty. This headers pointed because we can not
     * find them inside the data segment (allocated like this '[allocator][data]' ) so
     * we need to store their pointer to access later via allocator
     */
    heap_header_t* headers[ALLOCATOR_HEADER_COUNT];

    /* Look up for 'ALLOCATOR_NEEDED_BITS' before changing this array */
    u8 free_bits[ALLOCATOR_NEEDED_BITS];
};

/* A temporary structure for setting the const slices
 * the items order and size should be same with the other slices
 */
typedef struct slice_dummy_s slice_dummy_t;
struct slice_dummy_s {
    u8 *items;
    usz count;
};

/* We can make some function pointers in allocator_t via that
 * in fuctions like malloc/calloc etc we can use custom allocators too.
 */
error_t allocator_alloc_pointer
(allocator_t* alloc, usz n, void* set, const char* file_name, usz line);
error_t allocator_free_pointer(allocator_t* alloc, void* set);

noreturn allocator_overflow(allocator_t* alloc, heap_header_t* header);
noreturn allocator_underflow(allocator_t* alloc, heap_header_t* header);

void __set_chunks_free(u8* bitmap_bytes, u32 start_bit, u32 n);
void __set_chunks_used(u8* bitmap_bytes, u32 start_bit, u32 n);
u32 __find_free_chunks(u8* bitmap_bytes, u32 total_bits, u32 n);
error_t __validate_header(heap_header_t* header);

#endif /* __FLIBC_MEMORY_PRIVATE_H__ */

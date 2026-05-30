#include "memory_private.h"

/* Returns the starting chunk index, or CHUNK_IDX_FAILED if not enough space */
u32 __find_free_chunks
(u8* bitmap_bytes, u32 total_bits, u32 n)
{
    /* Cast the byte array to a 64-bit integer array for fast scanning */
    u64* bitmap = (u64*)(uintptr_t)bitmap_bytes;
    u32 total_words = total_bits / 64;

    u32 current_streak = 0;
    u32 start_bit = 0;
    u32 i, bit;

    for (i = 0; i < total_words; ++i) {
        u64 word = bitmap[i];

        /* FAST PATH 1: The entire 64-chunk block is full. Skip it instantly. */
        if (word == ~(u64)0) {
            current_streak = 0;
            continue;
        }

        /* FAST PATH 2: The entire 64-chunk block is completely empty! */
        if (word == (u64)0) {
            if (current_streak == 0) {
                start_bit = i * 64; /* Mark where our streak started */
            }
            current_streak += 64;

            if (current_streak >= n) {
                return start_bit;
            }
            continue;
        }

        /* SLOW PATH: The block is partially full. We must check bit-by-bit. */
        for (bit = 0; bit < 64; ++bit) {
            /* Check if the specific bit is 0 */
            if ((word & ((u64)1 << bit)) == 0) {
                if (current_streak == 0) {
                    start_bit = i * 64 + bit;
                }
                current_streak++;

                if (current_streak >= n) {
                    return start_bit;
                }
            } else {
                /* We hit a used chunk. The streak is broken! */
                current_streak = 0;
            }
        }
    }

    /* We searched the whole bitmap and couldn't find a streak big enough */
    return CHUNK_IDX_FULL;
}

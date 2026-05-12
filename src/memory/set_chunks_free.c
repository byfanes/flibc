#include "memory_private.h"

void __set_chunks_free
(u8* bitmap_bytes, u32 start_bit, u32 n)
{
    u32 i;
    for (i = 0; i < n; ++i) {
        u32 target_bit = start_bit + i;
        u32 byte_index = target_bit / 8;
        u32 bit_index  = target_bit % 8;

        /* The ~ operator flips the mask so we clear only that bit to 0 */
        bitmap_bytes[byte_index] &= (u8)~(1 << bit_index);
    }
}

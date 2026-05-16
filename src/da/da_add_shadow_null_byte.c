#include "da_private.h"

error_t __da_add_shadow_null_byte
(void* da, usize_t el_size)
{
    /* Init variables */
    def_da_t* def = da;
    u8* ptr = 0;

    /* Check input */
    if(!def || !def->items) { return null_pointer; }

    /* If count is less than capacity set ptr to end of the last item
     * and move one unit to set zero
     * otherwise its already full and pointing to last zero byte
     * which is set by the allocator
     */
    if(def->count != def->capacity) {
        ptr = (def->items + def->count * el_size) + 1;
        *ptr = 0;
    }

    return success;
}

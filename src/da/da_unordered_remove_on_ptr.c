#include "da_private.h"

error_t __da_unordered_remove_on_ptr
(void* da, usz el_size, void *ptr)
{
    /* Init variables */
    def_da_t *def = da;
    error_t res = success;
    u8 *uptr = ptr;

    return ((void)(
         /* Check user inputs */
         (res = (def && def->items && uptr) ? success : null_pointer) ||
         /* Check el_size if zero for explicit calls */
         (res = (el_size) ? success : elsize_zero) ||
         /* Check alignment */
         (res = ((uintptr_t)(uptr - def->items) % el_size == 0) ? success : not_aligned_pointer) ||
         /* Check out of bounds */
         (res = (def->items <= uptr) ? success : out_of_bounds) ||
         /* Check out of bounds */
         (res = (uptr < def->items + el_size * def->count) ? success : out_of_bounds) ||
         /* Move the data if its not the last element and decrase the count */
         (res = (uptr == def->items + (def->count - 1) * el_size) ? success
              : mem_move_raw(uptr, def->items + (def->count - 1) * el_size, el_size)) ||
         (def->count--, success)
    ), res);
}

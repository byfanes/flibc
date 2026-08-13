#include "std_private.h"

noreturn std_exit
(std_t* std, ssz code)
{
    /* We deinit the std but only cleared the pointer inside here since
     * the program going to terminate itself that is not a problem
     */
    std_deinit(&std);

    /* Exit from the program */
    __os_exit(code);
}

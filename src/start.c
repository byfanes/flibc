#include "stdlib.h"
#include "memory.h"

extern int main(int,char**);
void _start(void);

void _start(void)
{
    int ret = 0;
    ret = main(0,nullptr);
    exit(ret);
}

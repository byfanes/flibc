#include "stdlib.h"
#include "memory.h"
#include "stdio.h"

extern int main(int,char**);
extern void __fflush_stdio(void);

void _start()
{
    int ret = 0;
    ret = main(0,nullptr);
    __fflush_stdio();
    exit(ret);
}

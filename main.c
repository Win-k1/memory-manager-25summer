#include <stdio.h>
#include "mem.h"

int main()
{
    mem_init();
    void *p1 = mem_alloc(100);
    void *p2 = mem_alloc(200);
    mem_show();
    
    mem_free(p1);
    mem_show();
    
    mem_free(p2);
    mem_show();
    return 0;
}

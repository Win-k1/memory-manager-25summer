#ifndef MEM_H
#define MEM_H

#include <stdlib.h>

#define POOL_SIZE 4096

typedef struct BlockHeader
{
    size_t size;
    struct BlockHeader *next;
} BlockHeader;

void mem_init();
extern void *g_mem_pool;
extern BlockHeader *g_free_list;
void mem_free(void *ptr);

#endif

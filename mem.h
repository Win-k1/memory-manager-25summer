#ifndef MEM_H
#define MEM_H
#include <stdlib.h>
#include <stdio.h>

#define POOL_SIZE 4096

typedef struct BlockHeader
{
    size_t size;    
    struct BlockHeader *next;
} BlockHeader;

void mem_init();
void *mem_alloc(size_t size);
void mem_free(void *ptr);
void mem_show(void);

extern void *g_mem_pool;
extern BlockHeader *g_free_list;

#endif

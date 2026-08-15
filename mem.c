#include "mem.h"

void mem_init()
{
    g_mem_pool = malloc(POOL_SIZE);
    BlockHeader *block = (BlockHeader *)g_mem_pool;
    block->size = POOL_SIZE - sizeof(BlockHeader);
    block->next = NULL;
    g_free_list = block;
}

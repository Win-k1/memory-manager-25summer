#include "mem.h"

void mem_init()
{
    g_mem_pool = malloc(POOL_SIZE);
    BlockHeader *block = (BlockHeader *)g_mem_pool;
    block->size = POOL_SIZE - sizeof(BlockHeader);
    block->next = NULL;
    g_free_list = block;
}
void *mem_alloc (size_t size) {
BlockHeader current = g_free_list, prev = NULL;
while (current) {
if (current->size >= size) {
if (current->size - size > sizeof(BlockHeader)) {
BlockHeader split = (BlockHeader)((char)current + sizeof(BlockHeader) + size);
split->size = current->size - size - sizeof(BlockHeader);
split->next = current->next;
current->size = size;
current->next = split;
}
if (!prev) g_free_list = current->next;
else prev->next = current->next;
return (char)current + sizeof(BlockHeader);
}
prev = current;
current = current->next;
}
return NULL;
}

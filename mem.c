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

void mem_free(void *ptr)
{
    if (ptr == NULL)
    {
        return;
    }
    // 获取内存块头部
    BlockHeader *free_blk = (BlockHeader*)((char*)ptr - sizeof(BlockHeader));

    BlockHeader *cur = g_free_list;
    BlockHeader *pre = NULL;

    // 按地址顺序，找到插入位置
    while(cur != NULL && cur < free_blk)
    {
        pre = cur;
        cur = cur->next;
    }

    // 把释放的块插入空闲链表
    if(pre == NULL)
    {
        free_blk->next = g_free_list;
        g_free_list = free_blk;
    }
    else
    {
        free_blk->next = pre->next;
        pre->next = free_blk;
    }

    // 和后面相邻块合并
    if(free_blk->next != NULL)
    {
        char *end = (char*)free_blk + sizeof(BlockHeader) + free_blk->size;
        if(end == (char*)free_blk->next)
        {
            free_blk->size += sizeof(BlockHeader) + free_blk->next->size;
            free_blk->next = free_blk->next->next;
        }
    }

    // 和前面相邻块合并
    if(pre != NULL)
    {
        char *pre_end = (char*)pre + sizeof(BlockHeader) + pre->size;
        if(pre_end == (char*)free_blk)
        {
            pre->size += sizeof(BlockHeader) + free_blk->size;
            pre->next = free_blk->next;
        }
    }
}

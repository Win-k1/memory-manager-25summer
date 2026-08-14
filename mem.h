#ifndef MEM_H#define MEM_H
#include <stddef.h>
#ifndef MEM_H#define MEM_H#include <stddef.h>typedef struct MemBlock {int is_free;size_t size;struct MemBlock* next;} MemBlock;void mem_init ();void* mem_alloc (size_t size);void mem_free (void* ptr);#endif

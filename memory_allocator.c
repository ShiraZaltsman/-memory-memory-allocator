//
// Created by shira on 11/28/19.
//
#include <stddef.h>
#include "memory_allocator.h"

struct MemoryAllocator
{
    long *memory;
    size_t size;
};

MemoryAllocator memo;


/* memoryPool is a ptr to an already-existing large memory block */
MemoryAllocator *MemoryAllocator_init(void *memoryPool, size_t size) {
    memo.memory = memoryPool;
    memo.size = size;

    /* matadata: positive value: free and negative value: occupied */
    *memo.memory=(long)(size-8);
    return &memo;
}

/* Returns a ptr to the memoryPool */
void *MemoryAllocator_release(MemoryAllocator *allocator) {
    return memo.memory;
}

/* Allocate a memory chunk, return NULL  if fail*/
void *MemoryAllocator_allocate(MemoryAllocator *allocator, size_t size) {

    if (size == 0) {
        return NULL;
    }
    long *ptr = allocator->memory;
    while(ptr != (allocator->memory + allocator->size)){
        if(*ptr > 0) /* its a free block yay! */
        {
            long *free_start = ptr;
            long free_size= *ptr;
            /* its big  enough to allocate! */
            if(*ptr >= size)
            {
                long old_free_size = *ptr;
                *ptr = -size; /* update matedata to occupied */
                if (*ptr > size + ALIGN_SIZE)
                {
                    /* update next matedata to free */
                   *(ptr + size + ALIGN_SIZE) = old_free_size - size - ALIGN_SIZE;
                }
            }
            else
            {

            }
        }
    }
    if(*((long*)ptr) < size)
    {

    }
}
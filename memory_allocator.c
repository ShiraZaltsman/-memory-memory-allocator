//
// Created by shira on 11/28/19.
//
#include <stddef.h>
#include "memory_allocator.h"

struct MemoryAllocator {
    size_t *memory;
    size_t size;
};

size_t roundSize(size_t size);


/* memoryPool is a ptr to an already-existing large memory block */
MemoryAllocator *MemoryAllocator_init(void *memoryPool, size_t size) {
    MemoryAllocator *memo = malloc(sizeof(MemoryAllocator));
    if (memo == NULL)
        return NULL;

    // Set size, pointer  and return.

    memo->memory = memoryPool;
    memo->size = size;

    /* matadata: positive value: free and negative value: occupied */
    *(memo->memory) = (size - ALIGN_SIZE) / ALIGN_SIZE;
    return memo;
}

/* Returns a ptr to the memoryPool */
void *MemoryAllocator_release(MemoryAllocator *allocator) {
    void *ptr = allocator->memory;
    free(allocator);
    return ptr;
}

size_t *FindNextFreeBlock(size_t *ptr, size_t *end) {
    while (ptr < end && *ptr & 1) {
        ptr = ptr + (*ptr & -2);
    }
    if (ptr >= end)
        return NULL;
    return ptr;
}

/* Allocate a memory chunk, return NULL  if fail*/
void *MemoryAllocator_allocate(MemoryAllocator *allocator, size_t size) {
    if (size == 0) {
        return NULL;
    }
    size_t paddinglen = roundSize(size);
    size_t *ptr = allocator->memory;
    size_t *end = allocator->memory + allocator->size;

    while (*ptr < paddinglen) {

        /* finds first free place */
        ptr = FindNextFreeBlock(ptr, end);
        if (!ptr) {
            return NULL;
        }
        /* while dont have enough free space merge neighbor blocks if possible */
        while (MergeBlock(ptr));
        if(*ptr >= paddinglen){ /* its big enough*/
            AddBlock(ptr, paddinglen);
            break;
        }
        else
            ptr = ptr + *ptr;
    }
    if(ptr>= end)
        return NULL;
    return ptr + ALIGN_SIZE;
}

/* Merge the next adjacent block is free */
void MemoryAllocator_free(MemoryAllocator *allocator, void *ptr){
    *(size_t*)ptr = *(size_t*)ptr & -2; // mask the size as free by deleting the LSB
    while(MergeBlock(ptr));

}
void AddBlock(size_t *p, size_t len) {
    /* size_t newSize = ((len +1) >> 1) << 1; */
    size_t oldSize = *p; /*& -2;*/
    *p = len | 1;
    if (len < oldSize)
        *(p + len) = oldSize - len;
}

int MergeBlock(size_t *p) {
    size_t *nextPtr;
    nextPtr = p + *p;
    if ((*nextPtr & 1) == 0) {
        *p = *p + *nextPtr;
        return 1;
    }
    return 0;
}

size_t roundSize(size_t size) {
    while (size++ % ALIGN_SIZE != 0);
    return size;
}

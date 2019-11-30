//
// Created by shira on 11/28/19.
//

#ifndef MEMORY_MEMORY_ALLOCATOR_SHIRAZALTSMAN_MEMORY_ALLOCATOR_H
#define MEMORY_MEMORY_ALLOCATOR_SHIRAZALTSMAN_MEMORY_ALLOCATOR_H

#include <glob.h>
#include <stdlib.h>
#define ALIGN_SIZE 8

typedef struct MemoryAllocator MemoryAllocator;
typedef struct MetaData MetaData;

/* memoryPool is a ptr to an already-existing large memory block */
MemoryAllocator *MemoryAllocator_init(void *memoryPool,size_t size);

/* Returns a ptr to the memoryPool */
void *MemoryAllocator_release(MemoryAllocator *allocator);


void *MemoryAllocator_allocate(MemoryAllocator *allocator,size_t size);

/* Merge the next adjacent block is free */
void MemoryAllocator_free(MemoryAllocator *allocator, void *ptr);

/* Merges all adjacent free blocks, and returns the size of
largest free block */
size_t MemoryAllocator_optimize(MemoryAllocator *allocator);

void AddBlock(size_t *p, size_t len);

int MergeBlock(size_t *p);

size_t *FindNextFreeBlock(size_t *ptr, size_t *end);
#endif //MEMORY_MEMORY_ALLOCATOR_SHIRAZALTSMAN_MEMORY_ALLOCATOR_H

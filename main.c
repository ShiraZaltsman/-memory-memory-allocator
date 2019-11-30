#include <stdio.h>
#include <stdlib.h>
#include "memory_allocator.h"

int main() {
    void *p = malloc(512);
    int i;
    MemoryAllocator *MyHeap;
    if(p)
    {
        MyHeap = MemoryAllocator_init(p, 512);
        size_t *newP = MemoryAllocator_allocate(MyHeap, 16);
        if(newP){
            for (i = 0;  i< 16; ++i) {
              newP[i]=i;
            }
        }

        size_t *newP2 = MemoryAllocator_allocate(MyHeap, 16);
        if(newP2) {
            int i;
            for (i = 0; i < 16; ++i) {
                newP2[i] = i;
            }
        }
        for (i = 0;  i< 16; ++i) {
            printf("%lu ",newP[i]);
            printf("%lu ",newP2[i]);
        }

    }

    return 0;
}
#ifndef UTIL_H
#define UTIL_H

#define ALLOC_FAILED 1

// allocating memory and checking memory allocation
void *safeMalloc(size_t typeSize, int numOfElems);
// reallocing memory and checking memory allocation
void *safeRealloc(void *block, size_t typeSize, int numOfElems);
// Callocing memory and checking memory allocation
void *safeCalloc(size_t numOfElems, size_t typeSize);
// checking memory allocation
void  checkAlloc(void *ptr);

#endif
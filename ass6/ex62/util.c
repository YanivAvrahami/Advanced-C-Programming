#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "util.h"

void *safeMalloc(size_t typeSize, int numOfElems)
{
	void *res;
	res = malloc(typeSize * numOfElems);
	checkAlloc(res);
	return res;
}
void *safeRealloc(void *block, size_t typeSize, int numOfElems)
{
	void *res;
	res = realloc(block, typeSize * numOfElems);
	checkAlloc(res);
	return res;
}

void *safeCalloc(size_t numOfElems, size_t typeSize)
{
	void *res;
	res = calloc(numOfElems, typeSize);
	checkAlloc(res);
	return res;
}

void  checkAlloc(void *ptr)
{
	if (ptr == NULL)
	{
		fprintf(stderr, "FAILED TO ALLOCATE MEMORY!");
		exit(ALLOC_FAILED);
	}
}
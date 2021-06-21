#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "util.h"

void *safeMalloc(size_t typeSize, int numOfElems)
{
	void *res;
	res = malloc(typeSize * numOfElems);
	checkAlloc(res);
	return res;
}
void *safeRealloc(void *block , size_t typeSize, int numOfElems)
{
	void *res;
	res = realloc(block, typeSize * numOfElems);
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

void   printStrArr(char **strArr, int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%s\n", strArr[i]);
}
char  *removeUppercase(char *str)
{
	char *res;
	int numOfLowercase;
	int i, write = 0;

	numOfLowercase = countLowercase(str);
	res = safeMalloc(sizeof(char), numOfLowercase + 1);
	for (i = 0; str[i] != '\0'; i++)
	{
		if (islower(str[i]))
		{
			res[write] = str[i];
			write++;
		}
	}
	res[numOfLowercase] = '\0';
	return res;
}
int    countLowercase(char *str)
{
	int i, count = 0;
	for (i = 0; str[i] != '\0'; i++)
		if (islower(str[i]))
			count++;
	return count;
}
char **sortLexicographically(char **strArr, int size)
{
	int i;
	for (i = 0; i < size - 1; i++)
	{
		if (strcmp(strArr[i], strArr[i + 1]) > 0)
			swap(&strArr[i], &strArr[i + 1]);
	}
	return strArr;
}
void   swap(char **pa, char **pb)
{
	char *temp;
	temp = *pa;
	*pa = *pb;
	*pb = temp;
}

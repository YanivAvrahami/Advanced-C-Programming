#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALLOC_FAILED 1
#define SIZE 100
typedef unsigned char BYTE;

// generic binary search function
int binSearch(void *Arr, int Size, int ElemSize, void *Item, int (*compare)(void *, void *));
// binary search for ints function
int intBinSearch(int *intArr, int intSize, int item);
// binary search for strings function
int stringBinSearch(char **strings, int size, char *item);
// free memory of ints arr and strings arr
void freeMemory(int *intArr, int intSize, char **stringArr, int stringSize);
// gets an int array from user
int *getIntArr(int *psize);
// gets a string array from user
char **getStringArr(int *strArrSize);
// allocating memory and checking memory allocation
void *safeMalloc(size_t typeSize, int numOfElems);
// reallocing memory and checking memory allocation
void *safeRealloc(void *block, size_t typeSize, int numOfElems);
// checks if allocation was successful or not
void  checkAlloc(void *ptr);
// compares between two ints
int compareInts(void *a, void *b);
// compares between two strings
int compareStrings(void *a, void *b);

void main()
{
	int *intArr;
	int intSize, intToFind;
	char **stringArr, stringToFind[SIZE];
	int stringSize;
	int res;

	// The user will enter the number of integers followed by the integers.
	intArr = getIntArr(&intSize);

	// The user will enter the integer to find
	scanf("%d", &intToFind);

	//The function searches the array using binSearch()
	res = intBinSearch(intArr, intSize, intToFind);
	if (res == 1)
		printf("The number %d was found\n", intToFind);
	else
		printf("The number %d was not found\n", intToFind);

	// The user will enter the number of strings (lines) followed by the strings.
	// You may assume that each line contains up to 99 characters.
	stringArr = getStringArr(&stringSize);

	// The user will enter the string to find
	gets(stringToFind);

	//The function searches the array using binSearch()
	res = stringBinSearch(stringArr, stringSize, stringToFind);

	if (res == 1)
		printf("The string %s was found\n", stringToFind);
	else
		printf("The string %s was not found\n", stringToFind);

	freeMemory(intArr, intSize, stringArr, stringSize);
}


int binSearch(void *Arr, int Size, int ElemSize, void *Item, int (*compare)(void *, void *))
{
	int found;
	int left, right;
	int place;

	found = 0;
	left = 0;
	right = Size - 1;

	while ((left <= right) && !found)
	{
		place = ((left + right) / 2);

		if (compare((BYTE *)Arr + (place * ElemSize), (BYTE *)Item) == 0)
		{
			found = 1;
		}
		else if (compare((BYTE *)Arr + (place * ElemSize), (BYTE *)Item) < 0)
		{
			left = place + 1;
		}
		else
		{
			right = place - 1;
		}

	}
	return found;
}

int intBinSearch(int *intArr, int intSize, int item)
{
	return binSearch(intArr, intSize, sizeof(int), &item, compareInts);
}

int stringBinSearch(char **strings, int size, char *item)
{
	return binSearch(strings, size, sizeof(char *), &item, compareStrings);
}

void freeMemory(int *intArr, int intSize, char **stringArr, int stringSize)
{
	int i;

	for (i = 0; i < stringSize; i++)
		free(stringArr[i]);

	free(stringArr);
	free(intArr);
}

int *getIntArr(int *psize)
{
	int *res, size, i;

	scanf("%d", &size);

	res = (int *)safeMalloc(sizeof(int), size);

	for (i = 0; i < size; i++)
	{
		scanf("%d", &res[i]);
	}

	*psize = size;

	return res;
}

char **getStringArr(int *strArrSize)
{
	char **stringArr;
	char line[SIZE];
	int lineLength;
	int i;

	scanf("%d", strArrSize);
	getchar();
	stringArr = (char **)malloc((*strArrSize) * (sizeof(char *)));

	for (i = 0; i < (*strArrSize); i++)
	{
		gets(line);
		lineLength = strlen(line);
		stringArr[i] = (char *)malloc((lineLength + 1) * sizeof(char));
		strcpy(stringArr[i], line);
	}

	return stringArr;
}

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

void  checkAlloc(void *ptr)
{
	if (ptr == NULL)
	{
		fprintf(stderr, "FAILED TO ALLOCATE MEMORY!");
		exit(ALLOC_FAILED);
	}
}

int compareInts(void *a, void *b)
{
	int *elemA = (int *)a;
	int *elemB = (int *)b;
	return *elemA - *elemB;
}

int compareStrings(void *a, void *b)
{
	char **elemA = (char **)a;
	char **elemB = (char **)b;
	return strcmp(*elemA, *elemB);
}
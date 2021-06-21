#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "arr.h"

typedef unsigned char BYTE;

// scrambles a given array
void *scramble(void *arr, int ElemSize, int n, int *indArr);

// scrambles a given int array
int *scrambleInt(int *intArr, int size, int *indArr);

// scrambles a given string array
char **scrambleString(char **stringArr, int size, int *indArr);

// free the memory of the given arrays
void freeMemory(int *intArr, int *scrableIntArr, int intSize, char **strArr, char **scrambleStrArr, int stringSize);

void main()
{
	int *intArr, *scrambleIntArr;
	int intSize;
	char **stringArr, **scrambleStringArr;
	int stringSize, i;
	int indArr[SIZE];

	// The user will enter the number of integers followed by the integers.
	intArr = getIntArr(&intSize);

	// The user will enter the indices
	for (i = 0; i < intSize; i++)
		scanf("%d", &indArr[i]);

	//The function scrambles the array using scramble()
	scrambleIntArr = scrambleInt(intArr, intSize, indArr);

	printIntArr(scrambleIntArr, intSize);

	// The user will enter the number of strings (lines) followed by the strings.
	// You may assume that each line contains up to 99 characters.
	stringArr = getStringArr(&stringSize);

	// The user will enter the indices
	for (i = 0; i < stringSize; i++)
		scanf("%d", &indArr[i]);

	//The function scrambles the array using scramble()
	scrambleStringArr = scrambleString(stringArr, stringSize, indArr);

	printStringArr(scrambleStringArr, stringSize);
	freeMemory(intArr, scrambleIntArr, intSize, stringArr, scrambleStringArr, stringSize);
}

void freeMemory(int *intArr, int *scrableIntArr, int intSize, char **strArr, char **scrambleStrArr, int stringSize)
{
	int i;

	free(intArr);
	free(scrableIntArr);

	for (i = 0; i < stringSize; i++) 
	{
		free(scrambleStrArr[i]);
		free(strArr[i]);
	}
	
	free(scrambleStrArr);
	free(strArr);
}

void *scramble(void *arr, int ElemSize, int n, int *indArr)
{
	void *res;
	int i;

	res = malloc(n * ElemSize);

	for (i = 0; i < n; i++)
	{
		memcpy((BYTE *)res + i * ElemSize, (BYTE *)arr + indArr[i] * ElemSize, ElemSize);
	}

	return res;
}

int *scrambleInt(int *intArr, int size, int *indArr)
{
	return (int *)scramble(intArr, sizeof(int), size, indArr);
}

char **scrambleString(char **stringArr, int size, int *indArr)
{
	return (char **)scramble(dupStrArr(stringArr, size), sizeof(char *), size, indArr);
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "arr.h"
#include "util.h"
#include "arr.h"

void copyIntArr(int dest[], int src[], int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		dest[i] = src[i];
	}

}

void printIntArr(int *arr, int size)
{
	int i;

	for (i = 0; i < size; i++) 
	{
		printf("%d ", arr[i]);
	}
	
}

bool isEqualCharArr(char *arr1, char *arr2, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		if (arr1[i] != arr2[i]) 
		{
			return false;
		}	
	}

	return true;
}

int *getIntArr(int *psize)
{
	int *res, size, i;

	scanf("%d", &size);

	res = (int *)safeMalloc(sizeof(int), size);

	for (i = 0; i < size; i ++)
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

void printStringArr(char **strArr, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		printf("%s\n", strArr[i]);
	}

}

char **dupStrArr(char **strArr, int size)
{
	char **res;
	int i;

	res = (char **)safeMalloc(sizeof(char *), size);

	for (i = 0; i < size; i++)
		res[i] = strdup(strArr[i]);

	return res;
}
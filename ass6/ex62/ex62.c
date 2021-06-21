#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "bits.h"
#include "util.h"
#include "arr.h"

// gets an array which is a subset of the Numbers array with has 
// values corresponding to the xor of pred1 and pred2 bits array.
int *xorFilter(int *Numbers, int size, unsigned char *pred1, unsigned char *pred2, int *new_size);

// gets an array which is a subset of the Numbers array 
// with has values corresponding to pred bits array.
int *filter(int *Numbers, int size, unsigned char *pred, int *new_size);

void main()
{
	int i, pr, new_size, size;
	int *numbers;
	unsigned char *pred1, *pred2;
	int *some_numbers1;
	int *some_numbers2;

	printf("Please enter the number of numbers:\n");
	scanf("%d", &size);

	numbers = (int *)malloc(size * sizeof(int));
	pred1 = (char *)malloc(size / 8 * sizeof(char));
	pred2 = (char *)malloc(size / 8 * sizeof(char));

	printf("Please enter the numbers:\n");

	for (i = 0; i < size; i++)
		scanf("%d", &numbers[i]);

	printf("Please enter the first filter bits in hexa:\n");

	for (i = 0; i < size / 8; i++)
	{
		scanf("%x", &pr);
		pred1[i] = (char)pr;
	}

	some_numbers1 = filter(numbers, size, pred1, &new_size);

	printf("The numbers selected are:\n");

	for (i = 0; i < new_size; i++)
		printf("%d ", some_numbers1[i]);

	printf("Please enter the second filter bits in hexa:\n");

	for (i = 0; i < size / 8; i++)
	{
		scanf("%x", &pr);
		pred2[i] = (char)pr;
	}

	some_numbers2 = xorFilter(numbers, size, pred1, pred2, &new_size);

	printf("The numbers selected are:\n");

	for (i = 0; i < new_size; i++)
		printf("%d ", some_numbers2[i]);

	free(numbers);
	free(some_numbers1);
	free(pred1);
	free(some_numbers2);
	free(pred2);
}

int *xorFilter(int *Numbers, int size, unsigned char *pred1, unsigned char *pred2, int *new_size)
{
	int *res, resSize;
	int predSize;
	unsigned char *xorPred;
	int i;

	predSize = (int)ceil(size / 8.0);
	
	xorPred = createBitsArr(predSize);

	for (i = 0; i < predSize; i++)
	{
		xorPred[i] = pred1[i] ^ pred2[i];
	}

	res = filter(Numbers, size, xorPred, &resSize);

	free(xorPred);

	*new_size = resSize;
	return res;
}

int *filter(int *Numbers, int size, unsigned char *pred, int *new_size)
{
	int predSize; 
	int subArrSize;
	int *subArr;
	int i, j, k = 0;
	predSize = (int)ceil(size / 8.0);
	subArrSize = countSetBits(pred, predSize);

	subArr = (int *)safeMalloc(sizeof(int), subArrSize);

	for (i = 0; i < predSize; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if ((0x01 << j & pred[i]) != 0)
			{
				subArr[k] = Numbers[j + i * 8];
				k++;
			}
		}
	}

	*new_size = subArrSize;
	return subArr;
}
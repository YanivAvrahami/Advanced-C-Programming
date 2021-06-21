//Full Name: Yaniv Avrahami
//ID: 302374921

#define _CRT_SECURE_NO_WARNINGS
#define SIZE 100
#define ALLOCATION_ERROR -1
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Sorts a pointer array using mergeSort
void mergeSort(int** ptrs, unsigned int n);

// Merges two pointer arrays
void merge(int** dest, int** ptrs1, unsigned int n, int** ptrs2, unsigned int m);

// Sorts a pointer array using mergeSort ascending or descending
int** pointerSort(int* arr, unsigned int size, int ascend_flag);

// Reverse a given pointer array
void reversePointersArray(int** ptrs, unsigned int size);

// swaps between two pointers
void swap(int** ap, int** bp);

// Checks if allocation was successful or not.
void checkAllocation(void* pointer);

int main() 
{
	unsigned int size, i;

	int arr[SIZE];

	int** pointers;

	int ascend_flag;

	printf("Please enter the number of items:\n");

	scanf("%u", &size);

	for (i = 0; i < size; i++)
		scanf("%d", &arr[i]);

	scanf("%d", &ascend_flag);

	pointers = pointerSort(arr, size, ascend_flag);

	printf("The sorted array:\n"); //Print the sorted array

	for (i = 0; i < size; i++)
	{
		printf("%d\n", *pointers[i]);
	}

	free(pointers);
}

int** pointerSort(int* arr, unsigned int size, int ascend_flag)
{
	unsigned int i;

	int** pointers = (int**)malloc(size * sizeof(int*));
	if(!pointers)
	{
	    fprintf(stderr, "Allocation failed.");
	    exit(ALLOCATION_ERROR);
	}

	for (i = 0; i < size; i++)
	{
		pointers[i] = arr + i;
	}

	mergeSort(pointers, size);

	if (ascend_flag == 1)
	{
		return pointers;
	}
	else if (ascend_flag == 0)
	{
		reversePointersArray(pointers, size);
		return pointers;
	}

	return NULL;

}

void reversePointersArray(int** ptrs, unsigned int size)
{
	unsigned int i;
	for (i = 0; i < size / 2; i++)
	{
		swap(&ptrs[i], &ptrs[size - i - 1]);
	}
}

void swap(int** ap, int** bp)
{
	int* temp = *ap;
	*ap = *bp;
	*bp = temp;
}

void mergeSort(int** ptrs, unsigned int n)
{
	int** temp_ptrs;

	if (n < 2)
		return;
	else
	{
		mergeSort(ptrs, n / 2);
		mergeSort(ptrs + n / 2, n - n / 2);
		temp_ptrs = (int**)malloc(n * sizeof(int*));
		checkAllocation(temp_ptrs);
		merge(temp_ptrs, ptrs, n / 2, ptrs + n / 2, n - n / 2);
		memcpy(ptrs, temp_ptrs, n * sizeof(int*));
		free(temp_ptrs); // Is it enough to free temp_ptrs?
	}

}

void merge(int** dest, int** ptrs1, unsigned int n, int** ptrs2, unsigned int m)
{
	unsigned int i, j, k;
	i = j = k = 0;

	while (i < n && j < m)
	{
		if (*(ptrs1[i]) < *(ptrs2[j]))
		{
			dest[k] = ptrs1[i];
			i++;
		}
		else
		{
			dest[k] = ptrs2[j];
			j++;
		}
		k++;
	}

	while (i < n)
	{
		dest[k] = ptrs1[i];
		i++;
		k++;
	}

	while (j < m)
	{
		dest[k] = ptrs2[j];
		j++;
		k++;
	}
}

void checkAllocation(void* pointer)
{
	if (pointer == NULL)
	{
		fprintf(stderr, "Allocation failed.");
		exit(ALLOCATION_ERROR);
	}
}
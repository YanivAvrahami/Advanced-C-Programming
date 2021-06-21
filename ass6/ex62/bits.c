#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "bits.h"

void printLongInBin(unsigned long x)
{
	unsigned int i;
	unsigned long mask = MSB_SET_MASK(unsigned long);
	for (i = 0; i < sizeof(long) * 8; i++, mask >>= 1)
	{
		if (i % 8 == 0 && i > 0)
			putchar(' ');
		putchar(mask & x ? '1' : '0');
	}
	putchar('\n');
}

void printIntInBin(unsigned int x)
{
	unsigned int i;
	unsigned int mask = MSB_SET_MASK(unsigned int);
	for (i = 0; i < sizeof(int) * 8; i++, mask >>= 1)
	{
		if (i % 8 == 0 && i > 0)
			putchar(' ');
		putchar(mask & x ? '1' : '0');
	}
	putchar('\n');
}

void printCharInBin(unsigned char x)
{
	unsigned int i;
	unsigned char mask = MSB_SET_MASK(unsigned char);
	for (i = 0; i < sizeof(char) * 8; i++, mask >>= 1)
		putchar(mask & x ? '1' : '0');
	putchar('\n');
}

int countSetBits(unsigned char *bitsArr, int size)
{
	int i, j;
	int count = 0;

	for (i = 0; i < size; i++) 
	{
		for (j = 0; j < 8; j++) 
		{
			if (0x01 & bitsArr[i] >> j) 
				count++;
		}
	}
	
	return count;
}


unsigned char *createBitsArr(int size)
{
	unsigned char *res;
	int i;

	res = (unsigned char *)malloc(sizeof(unsigned char) * size);

	for (i = 0; i < size; i++)
		res[i] = 0;

	return res;
}


void setBit(unsigned char *pch, int i)
{
	unsigned char mask = 1 << i;
	*pch |= mask;
}

void printCharArrInBin(unsigned char *arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
		printCharInBin(arr[i]);
}
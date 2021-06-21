#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include "generic_functions.h"
#include "binary_tree.h"

int compareInts(void *num_1, void *num_2)
{
	if (*(int *)num_1 > *(int *)num_2)
		return 1;
	else if (*(int *)num_1 == *(int *)num_2)
		return 0;
	else
		return -1;
}

int compareChars(void *char_1, void *char_2)
{
	if (*(char *)char_1 > *(char *)char_2)
		return 1;
	else if (*(char *)char_1 == *(char *)char_2)
		return 0;
	else
		return -1;
}

void *maxInt(int number_of_args, ...) 
{
	int i;
	int max;
	int next;
	va_list list;
	
	va_start(list, number_of_args);
	max = *(int *)va_arg(list, void *);

	for (i = 1; i < number_of_args; i++)
	{
		next = *(int *)va_arg(list, void *);
		if (next > max) 
			max = next;
	}

	va_end(list);
	return max;
}

void *maxChar(int number_of_args, ...)
{
	int i;
	char max;
	char next;
	va_list list;

	va_start(list, number_of_args);
	max = *(char *)va_arg(list, void *);

	for (i = 1; i < number_of_args; i++)
	{
		next = *(char *)va_arg(list, void *);
		if (next > max)
			max = next;
	}

	va_end(list);
	return max;
}


void printChar(void *ch)
{
	putchar(*(char *)ch);
}

void printString(void *string) 
{
	printf("%s", (char *)string);
}

void printInt(void *integer) 
{
	printf("%d", *(int *)integer);
}

void printCharBinaryTreeNode(void *node) 
{
	BinaryTreeNode *binary_tree_node = node;
	printf("(%c) ", *(char *)(binary_tree_node->data)) ;
}

void checkMemoryAlloc(void *ptr) 
{
	if (ptr == NULL) 
	{
		fprintf(stderr, "Memory Allocation Failed!");
		exit(10);
	}
}
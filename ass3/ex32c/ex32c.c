#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "list_utils.h"


void main()
{
	List lst1, lst2, mergedList;

	lst1 = getList();
	lst2 = getList();

	mergedList = merge3(lst1, lst2);

	printf("Merged list:\n");
	printList(&mergedList);

	freeList(&lst1);
	freeList(&lst2);
	freeList(&mergedList);
}

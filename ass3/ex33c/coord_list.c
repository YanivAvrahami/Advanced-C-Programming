#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "coord_list.h"

List getCoordList() 
{
	List new_list;
	unsigned int coords_to_enter;
	unsigned int i;
	int x, y;

	makeEmptyList(&new_list);

	scanf("%u", &coords_to_enter);

	for (i = 0; i < coords_to_enter; i++)
	{
		scanf("%d%d", &x, &y);
		if ( isEmptyList(&new_list) || *(new_list.tail->x) != x)
		{
			insertDataToEndList(&new_list, x);
		}
		insertDataToEndYList(new_list.tail->yList, y);
	}
	return new_list;
}

bool isXExist(int x, List *list)
{
	bool res = false;
	while (list->head != NULL) 
	{
		if ( *(list->head->x) == x ) 
		{
			res = true;
			break;
		}
		list->head = list->head->next;
	}
	return res;
}

unsigned int getPairOccurrences(List coord_list, int x, int y) 
{
	unsigned int count = 0;
	XListNode *curr = coord_list.head;

	while (curr != NULL && *(curr->x) != x)
		curr = curr->next;

	if (curr == NULL)
		return 0;
	else
		return occurrencesInSortedYList(curr->yList, y);
}

unsigned int occurrencesInSortedYList(YList *ylist, int y_to_count) 
{
	unsigned int count = 0;
	YListNode *curr = ylist->head;

	while (curr != NULL && *(curr->y) != y_to_count)
		curr = curr->next;

	if (curr == NULL)
		return 0;
	else
		while (curr != NULL && *(curr->y) == y_to_count) 
		{
			count++;
			curr = curr->next;
		}
		
	return count;
}

unsigned int getYOccurrences(List coord_list, int y) 
{
	unsigned int count = 0;
	XListNode *curr = coord_list.head;

	while (curr != NULL) 
	{
		count += occurrencesInSortedYList(curr->yList, y);
		curr = curr->next;
	}

	return count;
}

unsigned int getXOccurrences(List coord_list, int x) 
{
	XListNode *curr = coord_list.head;

	while (curr != NULL && *(curr->x) != x)
		curr = curr->next;

	if (curr == NULL)
		return 0;
	else
		return lengthOfYList(curr->yList);
}

unsigned int lengthOfYList(YList *list)
{
	unsigned int length = 0;
	YListNode *curr = list->head;

	while (curr != NULL) 
	{
		length++;
		curr = curr->next;
	}

	return length;
}

XListNode *findPlaceToInsertInXList(List *list, int x_value)
{
	XListNode *curr = list->head;
	XListNode *prev = NULL;

	while (curr != NULL && *(curr->x) < x_value)
	{
		prev = curr;
		curr = curr->next;
	}

	return prev;
}

XListNode *findNodeInXList(List *list, int node_x_value)
{
	XListNode *curr = list->head;

	while (curr != NULL && *(curr->x) != node_x_value)
		curr = curr->next;

	if (curr == NULL)
		return NULL;
	else
		return curr;
}

void printCoordList(List *list)
{
	XListNode *curr = list->head;

	while (curr != NULL)
	{
		printColumnInCoordList(curr);
		curr = curr->next;
	}
}

void printSingleColumnInCoordList(List *list, int x_value)
{
	XListNode *targetXListNode = findNodeInXList(list, x_value);

	if (targetXListNode != NULL)
	{
		YListNode *running_node = targetXListNode->yList->head;
		while (running_node != NULL)
		{
			printf("(%d,%d)\n", x_value, *(running_node->y));
			running_node = running_node->next;
		}
	}
}

void printColumnInCoordList(XListNode *node)
{
	YListNode *running_node = node->yList->head;
	
	while (running_node != NULL)
	{
			printf("(%d,%d)\n", *(node->x), *(running_node->y));
			running_node = running_node->next;
	}
}

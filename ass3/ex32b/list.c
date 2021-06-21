#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

static void insertNodeToEndList(List *lst, ListNode *node);
static void insertNodeToStartList(List *lst, ListNode *node);
static void insertNodeAheadTo(List *lst, ListNode *prev, ListNode *node);

void insertDataToEndList(List *lst, int data)
{
	ListNode *newTail;
	newTail = createNewListNode(data, NULL);
	insertNodeToEndList(lst, newTail);
}


void insertDataToStartList(List *lst, int data)
{
	ListNode *node = createNewListNode(data, NULL);
	insertNodeToStartList(lst, node);
}


void insertDataAheadTo(List *lst, ListNode *prev, int data)
{
	ListNode *node = createNewListNode(data, NULL);
	insertNodeAheadTo(lst, prev, node);
}


void deleteDataAtStartList(List *lst)
{
	if (isEmptyList(lst))
	{
		return;
	}
	else if (lst->head->next == NULL) // if list has 1 node
	{
		free(lst->head);
		lst->head = lst->tail == NULL;
	}
	else // if list has more then 1 node
	{
		ListNode *new_head;
		new_head = lst->head->next;
		free(lst->head);
		lst->head = new_head;
	}
}


void deleteDataAtEndList(List *lst)
{
	if (isEmptyList(lst))
	{
		return;
	}
	else if (lst->head->next == NULL) // if list has 1 node
	{
		free(lst->head);
		lst->head = lst->tail == NULL;
	}
	else // if list has more then 1 node
	{
		ListNode *curr = lst->head;

		while (curr->next->next != NULL)
		{
			curr = curr->next;
		}

		free(lst->tail);
		curr->next = NULL;
		lst->tail = curr;
	}
}


void makeEmptyList(List *lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}


bool isEmptyList(List *lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}


ListNode *createNewListNode(int data, ListNode *next)
{
	ListNode *res;
	int *pdata;

	res = (ListNode *)malloc(sizeof(ListNode));
	if(res == NULL)
	{
	    fprintf(stderr, "Memory allocation failed.");
	    exit(MEMORY_ALLOCATION_ERROR);
	}
	
	pdata = (int *)malloc(sizeof(int));
	if(pdata == NULL)
	{
	    fprintf(stderr, "Memory allocation failed.");
	    exit(MEMORY_ALLOCATION_ERROR);
	}
	
	*pdata = data;
	res->dataPtr = pdata;
	res->next = next;

	return res;
}


void freeList(List *lst)
{
	ListNode *curr;

	while (lst->head != NULL) 
	{
		curr = lst->head;
		lst->head = lst->head->next;
		free(curr);
	}
}


static void insertNodeToEndList(List *lst, ListNode *node)
{
	if (isEmptyList(lst) == true) {
		lst->head = lst->tail = node;
	}
	else 
	{
		lst->tail->next = node;
		lst->tail = node;
	}
	node->next = NULL;
}


static void insertNodeToStartList(List *lst, ListNode *node)
{
	if (isEmptyList(lst))
	{
		lst->head = lst->tail = node;
	}
	else
	{
		node->next = lst->head;
		lst->head = node;
	}
}


static void insertNodeAheadTo(List *lst, ListNode *prev, ListNode *node)
{
	if (isEmptyList(lst))
	{
		lst->head = lst->tail = node;
	}
	else
	{
		if (prev->next == NULL)
		{
			node->next = prev->next;
			prev->next = node;
			lst->tail = node;
		}
		else
		{
			node->next = prev->next;
			prev->next = node;
		}
	}
}
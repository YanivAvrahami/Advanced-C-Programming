#define _CRT_SECURE_NO_WARININGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

static void insertNodeToEndList(List *lst, XListNode *node);
static void insertNodeToStartList(List *lst, XListNode *node);
static void insertNodeInInnerPlace(XListNode *prev, XListNode *node);


static void insertNodeToEndYList(YList *lst, YListNode *node);
static void insertNodeToStartYList(YList *lst, YListNode *node);
static void insertNodeAheadToInYList(YList *lst, YListNode *prev, YListNode *node);



void insertDataToEndList(List *lst, int data)
{
	XListNode *newTail;
	newTail = createNewListNode(data, NULL, NULL);
	insertNodeToEndList(lst, newTail);
}

void insertDataToStartList(List *lst, int data)
{
	XListNode *node = createNewListNode(data, NULL, NULL);
	insertNodeToStartList(lst, node);
}

void insertDataInInnerPlace(List *lst, XListNode *prev, int data)
{
	XListNode *node = createNewListNode(data, NULL, NULL);
	insertNodeInInnerPlace(prev, node);
}

void deleteDataAtStartList(List *lst)
{
	if (isEmptyList(lst))
	{
		return;
	}
	else if (lst->head->next == NULL)
	{
		free(lst->head);
		lst->head = lst->tail = NULL;
	}
	else
	{
		XListNode *new_head = lst->head->next;
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
	else if (lst->head->next == NULL)
	{
		free(lst->head);
		lst->head = lst->tail = NULL;
	}
	else
	{
		XListNode *new_tail = lst->tail->prev;
		free(lst->tail);
		lst->tail = new_tail;
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

XListNode *createNewListNode(int data, XListNode *next, XListNode *prev)
{
	XListNode *new_node = (XListNode *)malloc(sizeof(XListNode));
	if(new_node == NULL)
	{
	    fprintf(stderr, "Memory allocation failed.");
	    exit(MEMORY_ALLOCATION_ERROR);
	}
	
	new_node->x = (int *)malloc(sizeof(int));
	if(new_node->x == NULL)
	{
	    fprintf(stderr, "Memory allocation failed.");
	    exit(MEMORY_ALLOCATION_ERROR);
	}
	
	*(new_node->x) = data;

	new_node->yList = createNewEmptyYList();
	new_node->next = next;
	new_node->prev = prev;

	return new_node;
}

void freeList(List *lst)
{
	XListNode *to_del;

	while (lst->head != NULL)
	{
		to_del = lst->head;
		lst->head = lst->head->next;
		free(to_del->x);
		freeYList(to_del->yList);
		free(to_del);
	}
}

static void insertNodeToEndList(List *lst, XListNode *node)
{
	if (isEmptyList(lst)) {
		lst->head = lst->tail = node;
	}
	else
	{
		node->prev = lst->tail;
		lst->tail->next = node;
		lst->tail = node;
	}
}

static void insertNodeToStartList(List *lst, XListNode *node)
{
	if (isEmptyList(lst))
	{
		lst->head = lst->tail = node;
	}
	else
	{
		node->next = lst->head;
		lst->head->prev = node;
		lst->head = node;
	}
}

static void insertNodeInInnerPlace(XListNode *prev, XListNode *node)
{
	XListNode *after = prev->next;

	node->next = after;
	node->prev = prev;

	prev->next = node;
	after->prev = node;
}

void printList(List *list)
{
	XListNode *running_node = list->head;

	while (running_node != NULL)
	{
		printf("%d\n", *(running_node->x));
		running_node = running_node->next;
	}
}




void insertDataToEndYList(YList *lst, int data)
{
	YListNode *newTail;
	newTail = createNewYListNode(data, NULL);
	insertNodeToEndYList(lst, newTail);
}

void insertDataToStartYList(YList *lst, int data)
{
	YListNode *node = createNewYListNode(data, NULL);
	insertNodeToStartYList(lst, node);
}

void insertDataAheadToInYList(YList *lst, YListNode *prev, int data)
{
	YListNode *node = createNewYListNode(data, NULL);
	insertNodeAheadToInYList(lst, prev, node);
}

void deleteDataAtStartYList(YList *lst)
{
	if (isEmptyYList(lst))
	{
		return;
	}
	else if (lst->head->next == NULL) // if list has 1 node
	{
		free(lst->head);
		lst->head = lst->tail = NULL;
	}
	else // if list has more then 1 node
	{
		YListNode *new_head;
		new_head = lst->head->next;
		free(lst->head);
		lst->head = new_head;
	}
}

void deleteDataAtEndYList(YList *lst)
{
	if (isEmptyYList(lst))
	{
		return;
	}
	else if (lst->head->next == NULL) // if list has 1 node
	{
		free(lst->head);
		lst->head = lst->tail = NULL;
	}
	else // if list has more then 1 node
	{
		YListNode *curr = lst->head;

		while (curr->next->next != NULL)
		{
			curr = curr->next;
		}

		free(lst->tail);
		curr->next = NULL;
		lst->tail = curr;
	}
}

YList *createNewEmptyYList()
{
	YList *new_list = (YList *)malloc(sizeof(YList));
	if(new_list == NULL)
	{
	    fprintf(stderr, "Memory allocation failed.");
	    exit(MEMORY_ALLOCATION_ERROR);
	}
	
	makeEmptyYList(new_list);
	return new_list;
}

void makeEmptyYList(YList *lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}

bool isEmptyYList(YList *lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

YListNode *createNewYListNode(int data, YListNode *next)
{
	YListNode *res;
	int *pdata;

	res = (YListNode *)malloc(sizeof(YListNode));
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
	res->y = pdata;
	res->next = next;

	return res;
}

void freeYList(YList *lst)
{
	YListNode *curr;

	while (lst->head != NULL)
	{
		curr = lst->head;
		lst->head = lst->head->next;
		free(curr->y);
		free(curr);
	}
}

static void insertNodeToEndYList(YList *lst, YListNode *node)
{
	if (isEmptyYList(lst) == true) {
		lst->head = lst->tail = node;
	}
	else
	{
		lst->tail->next = node;
		lst->tail = node;
	}
	node->next = NULL;
}

static void insertNodeToStartYList(YList *lst, YListNode *node)
{
	if (isEmptyYList(lst))
	{
		lst->head = lst->tail = node;
	}
	else
	{
		node->next = lst->head;
		lst->head = node;
	}
}

static void insertNodeAheadToInYList(YList *lst, YListNode *prev, YListNode *node)
{
	if (isEmptyYList(lst))
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

void printYList(YList *ylist)
{
	YListNode *running_node = ylist->head;

	while (running_node != NULL)
	{
		printf("%d\n", *(running_node->y));
		running_node = running_node->next;
	}
}



//static void insertNodeInInnerPlaceAtYList(YListNode *prev, YListNode *node)
//{
//	YListNode *after = prev->next;
//
//	node->next = after;
//	node->prev = prev;
//
//	prev->next = node;
//	after->prev = node;
//}
//
//
//void insertDataInInnerPlace(List *lst, XListNode *prev, int data)
//{
//	XListNode *node = createNewListNode(data, NULL, NULL);
//	insertNodeInInnerPlace(prev, node);
//}
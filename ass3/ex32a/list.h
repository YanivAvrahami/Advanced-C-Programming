#ifndef ___LIST_H___
#define ___LIST_H___

#include <stdbool.h>

#define MEMORY_ALLOCATION_ERROR -1

typedef struct listNode {
	int *dataPtr;
	struct listNode *next;
}ListNode;


typedef struct list {
	ListNode *head;
	ListNode *tail;
}List;


/*
This function gets a list and a number and inserts the number to the end of the list.
*/
void insertDataToEndList(List *lst, int data);

/*
This function gets a list and a number and inserts the number to the start of the list.
*/
void insertDataToStartList(List *lst, int data);

/*
This function gets a list and a number and inserts the number after another node of the list.
*/
void insertDataAheadTo(List *lst, ListNode *prev, int data);

/*
This function gets a list and deletes the number at the start of the list.
*/
void deleteDataAtStartList(List *lst);

/*
This function gets a list and deletes the number at the start of the list.
*/
void deleteDataAtEndList(List *lst);

/*
This function gets a list, checks if the list is empty and returns the result.
*/
bool isEmptyList(List *lst);

/*
This function gets a list, and initialize its variables.
*/
void makeEmptyList(List *lst);

/*
This function creates a new list node.
*/
ListNode *createNewListNode(int data, ListNode *next);

/*
This function gets a list and deallocate its nodes.
*/
void freeList(List *lst);


#endif
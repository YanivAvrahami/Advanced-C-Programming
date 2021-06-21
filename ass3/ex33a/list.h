#ifndef ___LIST_H___
#define ___LIST_H___

#include <stdbool.h>

#define MEMORY_ALLOCATION_ERROR -1

typedef struct YlistNode {
	int *y;
	struct YlistNode *next;
} YListNode;

typedef struct Ylist {
	YListNode *head;
	YListNode *tail;
} YList;


typedef struct XlistNode {
	int *x;
	struct XlistNode *prev;
	struct XlistNode *next;
	YList *yList;
} XListNode;

typedef struct list
{
	XListNode *head;
	XListNode *tail;
} List;






static void insertNodeToEndYList(YList *lst, YListNode *node);
static void insertNodeToStartYList(YList *lst, YListNode *node);
static void insertNodeAheadToInYList(YList *lst, YListNode *prev, YListNode *node);



/*
This function gets a list and a number and 
inserts the number to the end of the list.
*/
void insertDataToEndList(List *lst, int data);


/*
This function gets a list and a number and 
inserts the number to the start of the list.
*/
void insertDataToStartList(List *lst, int data);


/*
This function gets a list and a number and 
inserts the number after another node of the list.
*/
void insertDataInInnerPlace(List *lst, XListNode *prev, int data);


/*
This function gets a list and deletes the 
number at the start of the list.
*/
void deleteDataAtStartList(List *lst);


/*
This function gets a list and deletes the 
number at the start of the list.
*/
void deleteDataAtEndList(List *lst);


/*
This function gets a list, checks if the 
list is empty and returns the result.
*/
bool isEmptyList(List *lst);


/*
This function gets a list, and initialize 
its variables.
*/
void makeEmptyList(List *lst);


/*
This function creates a new list node.
*/
XListNode *createNewListNode(int data, XListNode *next, XListNode *prev);


/*
This function gets a list and deallocate 
its nodes.
*/
void freeList(List *lst);


/*
This function prints the values in list 
from head to tail.
*/
void printList(List *list);









/*
This function gets a list and a number and inserts the number to the end of the list.
*/
void insertDataToEndYList(YList *lst, int data);


/*
This function gets a list and a number and inserts the number to the start of the list.
*/
void insertDataToStartYList(YList *lst, int data);


/*
This function gets a list and a number and inserts the number after another node of the list.
*/
void insertDataAheadToInYList(YList *lst, YListNode *prev, int data);


/*
This function gets a list and deletes the number at the start of the list.
*/
void deleteDataAtStartYList(YList *lst);


/*
This function gets a list and deletes the number at the start of the list.
*/
void deleteDataAtEndYList(YList *lst);


YList *createNewEmptyYList();

/*
This function gets a list, checks if the list is empty and returns the result.
*/
bool isEmptyYList(YList *lst);


/*
This function gets a list, and initialize its variables.
*/
void makeEmptyYList(YList *lst);


/*
This function creates a new list node.
*/
YListNode *createNewYListNode(int data, YListNode *next);


/*
This function gets a list and deallocate its nodes.
*/
void freeYList(YList *lst);


/*
	This function prints a YList.
*/
void printYList(YList *ylist);







#endif
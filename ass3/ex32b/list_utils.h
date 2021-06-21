#ifndef ___LIST_UTILS_H___
#define ___LIST_UTILS_H___


#include <stdbool.h>
#include "list.h"

List getList();



/*
This function gets two decreasingly sorted lists, merges them with an additional list,
and returns the result.
*/
List merge1(List lst1, List lst2);


/*
This function gets two decreasingly sorted lists, merges them WITHOUT an additional list,
and returns the result.
*/
List merge2(List lst1, List lst2);


/*
This function gets two decreasingly sorted lists,  merges them in recursion with an additional list.
*/
List merge3(List lst1, List lst2);
void merge3Helper(ListNode *lst1Head, ListNode *lst2Head, List *out);


///*
//This function gets two decreasingly sorted lists,  merges them in recursion WITHOUT an additional list.
//*/
List merge4(List lst1, List lst2);
void merge4Helper(ListNode *lst1Head, ListNode *lst2Head, List *out);




/*
This function gets a list pointer and reverses the list.
*/
void reverseList(List *lst);


/*
This function gets a list pointer and prints the list.
*/
void printList(List *lst);


/*
This function gets a list pointer,
and returns a copy of the list.
*/
List copyList(List *lst);


/*
This function gets two list pointers, adds list2 to the tail of list1,
and returns the new list.
*/
List listConcat(List *l1, List *l2);


/*
This function gets two list pointers, checks if the lists are equal,
and returns the result.
*/
bool isEqual(List *lst1, List *lst2);


#endif
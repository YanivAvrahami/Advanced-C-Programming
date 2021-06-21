#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_utils.h"


static reverseListAux(ListNode *curr);


List getList()
{
	List res;
	int size, num, i;

	makeEmptyList(&res);

	printf("Please enter the number of items to be entered:\n");
	scanf("%d", &size);

	printf("Please enter the numbers:\n");
	for (i = 0; i < size; i++)
	{
		scanf("%d", &num);
		insertDataToEndList(&res, num);
	}

	return res;
}



List merge1(List lst1, List lst2)
{
	List res;
	makeEmptyList(&res);

	ListNode *curr1, *curr2;

	curr1 = lst1.head;
	curr2 = lst2.head;

	while (curr1 != NULL && curr2 != NULL)
	{
		if (*(curr1->dataPtr) > * (curr2->dataPtr))
		{
			insertDataToEndList(&res, *(curr1->dataPtr));
			curr1 = curr1->next;
		}
		else
		{
			insertDataToEndList(&res, *(curr2->dataPtr));
			curr2 = curr2->next;
		}
	}

	while (curr1 != NULL)
	{
		insertDataToEndList(&res, *(curr1->dataPtr));
		curr1 = curr1->next;
	}

	while (curr2 != NULL)
	{
		insertDataToEndList(&res, *(curr2->dataPtr));
		curr2 = curr2->next;
	}

	return res;
}

List merge2(List lst1, List lst2)
{
	ListNode *curr1, *curr2, *sorting;
	List *list_to_return;

	if (lst1.head == NULL)
		return lst2;

	if (lst2.head == NULL)
		return lst1;

	curr1 = lst1.head;
	curr2 = lst2.head;

	if (*(lst1.head->dataPtr) >= *(lst2.head->dataPtr))
	{
		sorting = lst1.head;
		curr1 = lst1.head->next;
		list_to_return = &lst1;
	}
	else
	{
		sorting = lst2.head;
		curr2 = lst2.head->next;
		list_to_return = &lst2;
	}

	while (curr1 != NULL && curr2 != NULL)
	{
		if (*(curr1->dataPtr) >= *(curr2->dataPtr))
		{
			sorting->next = curr1;
			sorting = curr1;
			curr1 = sorting->next;
		}
		else
		{
			sorting->next = curr2;
			sorting = curr2;
			curr2 = sorting->next;
		}
	}

	if (curr1 == NULL)
	{
		sorting->next = curr2;
	}

	if (curr2 == NULL)
	{
		sorting->next = curr1;
	}

	ListNode *curr = list_to_return->head;
	while (curr->next != NULL)
	{
		curr = curr->next;
	}
	list_to_return->tail = curr;

	return *list_to_return;
}

List merge3(List lst1, List lst2)
{
	List out;
	makeEmptyList(&out);
	merge3Helper(lst1.head, lst2.head, &out);
	return out;
}

void merge3Helper(ListNode *lst1Head, ListNode *lst2Head, List *out)
{
	if (lst1Head == NULL && lst2Head == NULL)
	{
		return;
	}
	else if (lst1Head == NULL)
	{
		merge3Helper(lst1Head, lst2Head->next, out);
		insertDataToStartList(out, *(lst2Head->dataPtr));
	}
	else if (lst2Head == NULL)
	{
		merge3Helper(lst1Head->next, lst2Head, out);
		insertDataToStartList(out, *(lst1Head->dataPtr));
	}
	else
	{
		if (*(lst1Head->dataPtr) > * (lst2Head->dataPtr))
		{
			merge3Helper(lst1Head->next, lst2Head, out);
			insertDataToStartList(out, *(lst1Head->dataPtr));
		}
		else
		{
			merge3Helper(lst1Head, lst2Head->next, out);
			insertDataToStartList(out, *(lst2Head->dataPtr));
		}
	}
}

//List merge4(List lst1, List lst2)
//{
//	List output;
//	makeEmptyList(&output);
//	merge4Helper(lst1.head, lst2.head, &output);
//	return output;
//}
//
//void merge4Helper(ListNode *lst1Head, ListNode *lst2Head, List *output)
//{
//	if ((lst1Head == NULL) && (lst2Head == NULL))
//	{
//		return;
//	}
//	else if (lst1Head == NULL)
//	{
//		insertNodeToEndList(output, lst2Head);
//		mergeHelper(lst1Head, lst2Head->next, output);
//	}
//	else if (lst2Head == NULL)
//	{
//		insertNodeToEndList(output, lst1Head);
//		mergeHelper(lst1Head->next, lst2Head, output);
//	}
//	else
//	{ // if both lists have nodes
//		if (*(lst1Head->dataPtr) > * (lst2Head->dataPtr))
//		{
//			insertNodeToEndList(output, lst1Head);
//			mergeHelper(lst1Head->next, lst2Head, output);
//		}
//		else
//		{
//			insertNodeToEndList(output, lst2Head);
//			mergeHelper(lst1Head, lst2Head->next, output);
//		}
//	}
//}




void printList(List *lst)
{
	ListNode *curr;
	curr = lst->head;
	while (curr != NULL)
	{
		printf("%d ", *(curr->dataPtr));
		curr = curr->next;
	}
	printf("\n");
}


bool isEqual(List *lst1, List *lst2)
{
	bool res = true;
	ListNode *curr1, *curr2;
	curr1 = lst1->head;
	curr2 = lst2->head;
	while ((curr1 != NULL) && (curr2 != NULL) && (res != false))
	{
		if (*(curr1->dataPtr) != *(curr2->dataPtr))
			res = false;
		else
		{
			curr1 = curr1->next;
			curr2 = curr2->next;
		}
	}
	if (res == false)
		return false;
	else if ((curr1 == NULL) && (curr2 == NULL))
		return true;
	else
		return false;
}


List copyList(List *lst)
{
	List res;
	ListNode *curr = lst->head;
	makeEmptyList(&res);
	while (curr != NULL)
	{
		insertDataToEndList(&res, *(curr->dataPtr));
		curr = curr->next;
	}
	return res;
}


List listConcat(List *l1, List *l2)
{
	List res;
	if (isEmptyList(l1) == true && isEmptyList(l2) == true)
		makeEmptyList(&res);
	else if ((isEmptyList(l1) == true))
		res = *l2;
	else if ((isEmptyList(l2) == true))
		res = *l1;
	else
	{
		l1->tail->next = l2->head;
		res.head = l1->head;
		res.tail = l2->tail;
	}
	return res;
}


static reverseListAux(ListNode *curr)
{
	if (curr->next != NULL)
	{
		reverseListAux(curr->next);
		curr->next->next = curr;
	}
}


void reverseList(List *lst)
{
	ListNode *temp;
	if (isEmptyList(&lst))
	{
		return;
	}
	reverseListAux(lst->head);
	lst->head->next = NULL;
	temp = lst->tail;
	lst->tail = lst->head;
	lst->head = temp;
}
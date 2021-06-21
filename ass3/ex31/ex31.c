// Full name: Yaniv Avrahami
// ID: 302374921

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct list_node
{
	char *dataPtr;
	struct list_node *next;
} ListNode;

typedef struct list
{
	ListNode *head;
	ListNode *tail;
} List;

typedef struct student
{
	List first;
	int grade;
} Student;

// returns a student name and grade from a scrambled list
Student unScramble(List  lst);

// creates an empty list
void makeEmptyList(List *list);

// creates a dynamically allocated character
char *AllocateData(char c);

// creates a node containing a character pointer 
ListNode *AllocateListNode(char *data_ptr);

// inserts a character to the end of a given list
void insertDataToEndList(List *list, char c);

// prints a given list
void PrintList(List *list);

// checks if a given char is a digit or not
bool IsDigit(char c);

// checks if a given char is an alphabet letter or not
bool IsAlphabet(char c);

// converts an character into an int
int ConvertToInt(char c);

// prints student struct data
void printStudent(Student* pStudent);

// free all list nodes
void freeList(List *pFirstName);

// free a list node
void DeallocateListNode(ListNode *node);

// deletes a node from beginning of a list
void DeleteFromBeginningOfList(List *list);

void main()
{
    List lst;
    Student student;
    char ch;

    makeEmptyList(&lst);

    printf("Please enter the scrambled student:\n");

    ch = (char)getchar();
    while (ch != '\n')
    {
        insertDataToEndList(&lst, ch);
        ch = (char)getchar();
    }

    student = unScramble(lst);

    printStudent(&student);

    freeList(&student.first);
}

Student unScramble(List  lst) 
{
	Student student;
	List first_name;
	int grade = 0;
	ListNode *curr;

	makeEmptyList(&first_name);

	curr = lst.head;
	while (curr) 
	{
		if (IsAlphabet(*curr->dataPtr)) 
		{
			insertDataToEndList(&first_name, *curr->dataPtr);
		}
		else
		{
			grade *= 10;
			grade += ConvertToInt(*curr->dataPtr);
		}
		curr = curr->next;
	}

	student.first = first_name;
	student.grade = grade;
	return student;
}

void makeEmptyList(List *list)
{
    list->head = list->tail = NULL;
}

char *AllocateData(char c)
{
	char *char_ptr;

	char_ptr = (char *)malloc(sizeof(char));
	if (char_ptr == NULL)
	{
		fprintf(stderr, "Allocation failed.");
		exit(1);
	}

	*char_ptr = c;

	return char_ptr;
}

ListNode *AllocateListNode(char *data_ptr)
{
	ListNode *node;

	node = (ListNode *)malloc(sizeof(ListNode));
	if (node == NULL)
	{
		fprintf(stderr, "Allocation failed.");
		exit(1);
	}

	node->dataPtr = data_ptr;
	node->next = NULL;

	return node;
}

void insertDataToEndList(List *list, char c)
{
	char *char_ptr = AllocateData(c);
	ListNode *node_to_insert = AllocateListNode(char_ptr);

	if (list->head == NULL) 
	{
		list->head = node_to_insert;
		list->tail = node_to_insert;
	}
	else 
	{
		list->tail->next = node_to_insert;
		list->tail = node_to_insert;
	}
}

void PrintList(List *list)
{
	ListNode *curr = list->head;
	while (curr)
	{
		putchar(*curr->dataPtr);
		curr = curr->next;
	}
}

bool IsDigit(char c) 
{
	return c >= '0' && c <= '9';
}

bool IsAlphabet(char c) 
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void printStudent(Student *pStudent) 
{
	printf("First name: ");
	PrintList( &(pStudent->first));
	printf("\n");
	printf("Grade: %d", pStudent->grade);
}

int ConvertToInt(char c) 
{
	return c - '0';
}

void freeList(List *pFirstName) 
{
	while (pFirstName->head)
	{
		DeleteFromBeginningOfList(pFirstName);
	}
}

void DeleteFromBeginningOfList(List *list)
{
	ListNode *to_delete;

	if (list->head == NULL)
		return;

	if (list->head->next == NULL) 
	{
		DeallocateListNode(list->head);
		list->head = list->tail = NULL;
	}
	else 
	{
		to_delete = list->head;
		list->head = list->head->next;
		DeallocateListNode(to_delete);
	}
}

void DeallocateListNode(ListNode *node)
{
	free(node->dataPtr);
	free(node);
}
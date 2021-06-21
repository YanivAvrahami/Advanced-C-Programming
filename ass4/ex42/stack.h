#ifndef ___STACK_H___
#define ___STACK_H___
#include <stdbool.h>

typedef struct _StackNode {
    void *data;
    struct _StackNode *next;
} StackNode;

typedef struct _Stack {
    StackNode *top;
    size_t type_size;
} Stack;

//Creates a new empty stack.
Stack createEmptyStack(size_t stack_type_size);

//Push data into a given stack.
void push(Stack *stack_p, void *data);

//Pop data from a given stack.
void *pop(Stack *stack_p);

//Returns the data of the top of a given stack. 
void *peek(Stack *stack_p);

//Deallocates a stack node.
void freeStackNode(StackNode *node);

//Prints a given stack.
void printStack(Stack *stack_p, void (*print)(void *));

#endif
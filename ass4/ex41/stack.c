#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"
#include "generic_functions.h"

Stack createEmptyStack(size_t stack_type_size)
{
    Stack stack = {NULL, stack_type_size};
    return stack;
}

void push(Stack *stack_p, void *data)
{
    void *data_copy;
    StackNode *new_node;

    data_copy = malloc(stack_p->type_size);
    checkMemoryAlloc(data_copy);
    memcpy(data_copy, data, stack_p->type_size);

    new_node = (StackNode *)malloc(sizeof(StackNode));
    checkMemoryAlloc(new_node);
    new_node->data = data_copy;
    new_node->next = stack_p->top;
    stack_p->top = new_node;
}

void *pop(Stack *stack_p)
{
    void *data_to_pop;
    StackNode *temp_node;

    if (stack_p->top == NULL) 
    {
        return NULL;
    }
    else if (stack_p->top->next == NULL)
    {
        data_to_pop = stack_p->top->data;
        free(stack_p->top);
        stack_p->top = NULL;
    }
    else
    {
        data_to_pop = stack_p->top->data;
        temp_node = stack_p->top->next;
        free(stack_p->top);
        stack_p->top = temp_node;
    }

    return data_to_pop;
}

void *peek(Stack *stack_p)
{
    if (stack_p->top == NULL)
        return NULL;
    else
        return stack_p->top->data;
}

void freeStackNode(StackNode *node)
{
    free(node->data);
    free(node);
}

void printStack(Stack *stack_p, void (*print)(void *)) 
{
    int i;
    StackNode *current;

    printf("Stack Top: ");
    current = stack_p->top;
    while (current != NULL) 
    {
        print(current->data);
        putchar(' ');
        current = current->next;
    }
    putchar('\n');
}
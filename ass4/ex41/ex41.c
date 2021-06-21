#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binary_tree.h"
#include "generic_functions.h"

#define SIZE 100

int main() 
{
    int i;
    int size;
    int arr[SIZE];
    BinaryTree binary_tree;

    printf("Please enter the number of items: ");
    scanf("%d", &size);

    for (i = 0; i < size; i++) 
    {
        scanf("%d", &arr[i]);
    }
    
    binary_tree = BuildTreeFromArray(arr, size);
    printInOrder(binary_tree, printInt);
    clearTree(&binary_tree);
}
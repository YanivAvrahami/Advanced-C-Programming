#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "my_functions.h"

void main()
{
    int size, i, arr[SIZE];
    Tree tree;
    TreeNode *parent;
    int parentData, data, branchSelect;
    
    printf("Please enter the number of items: ");
    scanf("%d", &size);
    for (i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }
    
    scanf("%d%d%d", &parentData, &data, &branchSelect);
    
    tree = BuildTreeFromArrayWithLeafList(arr, size);
    
    parent = findParentNode(tree, parentData, branchSelect);
    tree = AddLeaf(tree, parent, branchSelect, data);
    
    printTreeInorder(tree);
    
    printLeafList(tree);
    freeTree(tree);
}
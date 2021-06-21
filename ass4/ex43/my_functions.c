#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "my_functions.h"



Tree BuildTreeFromArrayWithLeafList(int *arr, int size)
{
    Tree tree;
    List leaf_list;

    tree = allocateBinaryTreeFromArray(arr, size);
    leaf_list = allocateList(tree);
    tree.leafList = leaf_list;

    return tree;
}

Tree allocateBinaryTreeFromArray(int *arr, int size)
{
    Tree res_tree;
    Tree left;
    Tree right;
    
    res_tree.root = (TreeNode *)malloc(sizeof(TreeNode));
    checkMemoryAlloc(res_tree.root);

    if (size == 1)
    {   
        res_tree.root->data = arr[0];
        res_tree.root->left = NULL;
        res_tree.root->right = NULL;
        res_tree.root->parent = NULL;
    }
    else
    {
        res_tree.root->data = arr[size / 2];
        if (arr[(size / 2) / 2] != -1)
        {
            left = allocateBinaryTreeFromArray(arr, size / 2);
            left.root->parent = res_tree.root;
            res_tree.root->left = left.root;
        }
        else
        {
            res_tree.root->left = NULL;
        }
        if (arr[(size / 2) + ((size / 2) / 2) + 1] != -1)
        {
            right = allocateBinaryTreeFromArray(arr + (size / 2) + 1, size / 2);
            right.root->parent = res_tree.root;
            res_tree.root->right = right.root;
        }
        else
        {
            res_tree.root->right = NULL;
        }
    }

    return res_tree;
}

List allocateList(Tree tree)
{
    List list;
    list.head = NULL;
    list.tail = NULL;
    allocateListAux(tree.root, &list);
    return list;
}

void allocateListAux(TreeNode *root, List *list)
{
    if ((root->left == NULL) && (root->right == NULL))
    {
        insertDataToEndList(list, root->data);
    }
    else
    {
        if (root->left != NULL)
        {
            allocateListAux(root->left, list);
        }
        if (root->right != NULL)
        {
            allocateListAux(root->right, list);
        }
    }
}



void insertDataToEndList(List *list, int data)
{
    ListNode *node_to_add;
    node_to_add = allocateListNode(data, NULL);
    insertNodeToEndList(list, node_to_add);
}

void insertNodeToEndList(List *list, ListNode *node_to_add)
{
    if (list->head == NULL)
    {
        list->head = list->tail = node_to_add;
    }
    else
    {
        list->tail->next = node_to_add;
        list->tail = node_to_add;
    }
}

ListNode *allocateListNode(int data, ListNode *next)
{
    ListNode *res;
    res = (ListNode *)malloc(sizeof(ListNode));
    res->data = data;
    res->next = next;
    return res;
}




TreeNode *findParentNode(Tree tree, int parentData, int branchSelect)
{
    return findParentNodeAux(tree.root, parentData, branchSelect);
}

TreeNode *findParentNodeAux(TreeNode *root, int parentData, int branchSelect)
{
    TreeNode *res;

    if (root == NULL)
    {
        res = NULL;
    }
    else if ((root->data == parentData) && ((root->left == NULL && branchSelect == LEFT) || (root->right == NULL && branchSelect == RIGHT)))
    {
        res = root;
    }
    else
    {
        res = findParentNodeAux(root->left, parentData, branchSelect);

        if (res == NULL)
        {
            res = findParentNodeAux(root->right, parentData, branchSelect);
        }
    }

    return res;
}

Tree AddLeaf(Tree tree, TreeNode *parent, int branchSelect, int parentData)
{
    List list;
    TreeNode *node;

    node = (TreeNode *)malloc(sizeof(TreeNode));
    checkMemoryAlloc(node);
    node->data = parentData;
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;

    if (branchSelect == RIGHT)
    {
        parent->right = node;
    }
    else
    {
        parent->left = node;
    }

    freeList(&tree.leafList);
    list = allocateList(tree);
    tree.leafList = list;
    return tree;
}



void printTreeInorder(Tree tree)
{
    printTreeInorderAux(tree.root);
    printf("\n");
}

void printTreeInorderAux(TreeNode *root)
{
    if (root != NULL)
    {
        printTreeInorderAux(root->left);
        printf("%d ", root->data);
        printTreeInorderAux(root->right);
    }
}

void printLeafList(Tree tree)
{
    ListNode *curr = tree.leafList.head;
    while (curr != NULL)
    {
        printf("%d ", curr->data);
        curr = curr->next;
    }
}



void freeTree(Tree tree)
{
    freeTreeAux(tree.root);
    tree.root = NULL;
    freeList(&tree.leafList);
}

void freeTreeAux(TreeNode *root)
{
    if (root != NULL)
    {
        freeTreeAux(root->left);
        freeTreeAux(root->right);
        free(root);
    }
}

void freeList(List *list)
{
    ListNode *temp;
    ListNode *current;
    
    current = list->head;
    while (current != NULL)
    {
        temp = current->next;
        free(current);
        current = temp;
    }
}



void checkMemoryAlloc(void *ptr)
{
    if (ptr == NULL)
    {
        fprintf(stderr, "Memory allocation error");
        exit(1);
    }
}
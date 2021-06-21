#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binary_tree.h"
#include "generic_functions.h"

static unsigned int getNumberOfLevelsAux(BinaryTreeNode *root, void *(*g_max)(int, ...));
static unsigned int getNumberOfNodesAux(BinaryTreeNode *root);
static void printInOrderAux(BinaryTreeNode *root, void(*print_function)(void *));
static void printPreOrderAux(BinaryTreeNode *root, unsigned int level, void(*print_function)(void *));
static void printPostOrderAux(BinaryTreeNode *root, void(*print_function)(void *));
static void printLeftToRightSingleLevelAux(BinaryTreeNode *root, unsigned int required_level, unsigned int curr_level, void(*print_function)(void *));
static void *findAux(BinaryTreeNode *root, void *data_to_search, int level, int (*compare)(void *, void *));
static void *getMaximumAux(BinaryTreeNode *root, void *(*g_max)(int, ...));
static void clearTreeAux(BinaryTreeNode *root);

BinaryTree allocateEmptyTree(size_t type_size)
{
	BinaryTree tree;
	tree.root = NULL;
	tree.type_size = type_size;
	return tree;
}
unsigned int getNumberOfLevels(BinaryTree tree, void *(*g_max)(int, ...))
{
	if (tree.root == NULL)
		return 0;
	return getNumberOfLevelsAux(tree.root, g_max);
}
unsigned int getHeight(BinaryTree tree , void *(*g_max)(int, ...))
{
	return getNumberOfLevels(tree, g_max) - 1;
}
unsigned int getNumberOfNodes(BinaryTree tree)
{
	return getNumberOfNodesAux(tree.root);
}
BinaryTreeNode *allocateTreeNode(void *data, size_t size)
{
	BinaryTreeNode *node_to_allocate;
	void *data_copy;

	node_to_allocate = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
	checkMemoryAlloc(node_to_allocate);

	data_copy = malloc(size);
	checkMemoryAlloc(data_copy);
	memcpy(data_copy, data, size);

	node_to_allocate->data = data_copy;
	node_to_allocate->left = NULL;
	node_to_allocate->right = NULL;
	

	return node_to_allocate;
}
void *find(BinaryTree tree, void *data_to_search, int (*compare)(void *, void *))
{
	if (tree.root != NULL)
		return findAux(tree.root, data_to_search, 0, compare);
	else
		NOT_FOUND;
}
void *getMaximum(BinaryTree tree, int *result, void *(*g_max)(int, ...))
{
	if (tree.root != NULL)
	{
		*result = getMaximumAux(tree.root, g_max);
		return NON_EMPTY_TREE;
	}
	else
		return EMPTY_TREE;
}
void clearTree(BinaryTree *tree)
{
	if (tree->root != NULL)
	{
		clearTreeAux(tree->root);
		tree->root = NULL;
	}
}

void printInOrder(BinaryTree tree, void (*print_function)(void *))
{
	printf("\n==========InOrder===========\n");
	if (tree.root != NULL)
		printInOrderAux(tree.root, print_function);
	printf("\n============================\n");
}

void printPreOrder(BinaryTree tree, void(*print_function)(void *))
{
	printf("\n==========PreOrder============\n");
	if (tree.root != NULL)
		printPreOrderAux(tree.root, 0, print_function);
	printf("\n==============================\n");
}

void printPostOrder(BinaryTree tree, void(*print_function)(void *))
{
	printf("\n==========PostOrder==========\n");
	if (tree.root != NULL)
		printPostOrderAux(tree.root, print_function);
	printf("\n=============================\n");
}
void printLeftToRightSingleLevel(BinaryTree tree, unsigned int required_level, void(*print_function)(void *))
{
	printf("\n==========Level %d from left to right==========\n", required_level);
	if (tree.root != NULL)
		printLeftToRightSingleLevelAux(tree.root, required_level, 1, print_function);
	printf("\n===============================================\n");
}

static unsigned int getNumberOfLevelsAux(BinaryTreeNode *root, void *(*g_max)(int, ...))
{
	int left_subtree_result = 0, right_subtree_result = 0;

	if (root->left != NULL)
		left_subtree_result = getNumberOfLevelsAux(root->left, g_max);

	if (root->right != NULL)
		right_subtree_result = getNumberOfLevelsAux(root->right, g_max);

	return 1 + *(int *)g_max(2, &left_subtree_result, &right_subtree_result);
}
static unsigned int getNumberOfNodesAux(BinaryTreeNode *root)
{
	if (root == NULL)
		return 0;
	else
		return 1 + getNumberOfNodesAux(root->left) + getNumberOfNodesAux(root->right);
}

static void printInOrderAux(BinaryTreeNode *root, void (*print_function)(void *))
{
	if (root->left != NULL)
		printInOrderAux(root->left, print_function);

	print_function(root->data);
	putchar(' ');

	if (root->right != NULL)
		printInOrderAux(root->right, print_function);
}

static void printPreOrderAux(BinaryTreeNode *root, unsigned int level, void (*print_function)(void *))
{
	int i;

	for (i = 0; i < (3 * level); i++)
		putchar(' ');

	print_function(root->data);
	printf("\n");

	if (root->left != NULL)
		printPreOrderAux(root->left, level + 1, print_function);

	if (root->right != NULL)
		printPreOrderAux(root->right, level + 1, print_function);
}
static void printPostOrderAux(BinaryTreeNode *root, void (*print_function)(void *))
{
	if (root->left != NULL)
		printPostOrderAux(root->left, print_function);
	
	if (root->right != NULL)
		printPostOrderAux(root->right, print_function);

	print_function(root->data);
	putchar(' ');
}
static void printLeftToRightSingleLevelAux(BinaryTreeNode *root, unsigned int required_level, unsigned int curr_level, void (*print_function)(void *))
{
	if (curr_level == required_level)
	{
		print_function(root->data);
		putchar(' ');
		return;
	}

	if (root->left)
		printLeftToRightSingleLevelAux(root->left, required_level, curr_level + 1, print_function);

	if (root->right)
		printLeftToRightSingleLevelAux(root->right, required_level, curr_level + 1, print_function);
}
static void *findAux(BinaryTreeNode *root, void *data_to_search, int level, int (*compare)(void *, void *))
{
	void *subtree_res = NOT_FOUND;

	if (compare(root->data, data_to_search) == 0)
		return level;

	if (root->left != NULL)
		subtree_res = findAux(root->left, data_to_search, level + 1, compare);

	if (subtree_res == NOT_FOUND)
		if (root->right != NULL)
			subtree_res = findAux(root->right, data_to_search, level + 1, compare);

	return subtree_res;
}
static void *getMaximumAux(BinaryTreeNode *root, void *(*g_max)(int, ...))
{
	void *left_subtree_maxval, *right_subtree_maxval;

	if ((root->left == NULL) && (root->right == NULL))
		return root->data;

	if (root->left != NULL)
		left_subtree_maxval = getMaximumAux(root->left, g_max);
	else
		left_subtree_maxval = root->data;

	if (root->right != NULL)
		right_subtree_maxval = getMaximumAux(root->right, g_max);
	else
		right_subtree_maxval = root->data;

	return g_max(3, root->data, left_subtree_maxval, right_subtree_maxval);
}
static void clearTreeAux(BinaryTreeNode *root)
{
	if (root->right != NULL)
		clearTreeAux(root->right);

	if (root->left != NULL)
		clearTreeAux(root->left);

	free(root->data);
	free(root);
}


BinaryTree BuildTreeFromArray(int *arr, int  size)
{
	BinaryTree binary_tree;

	binary_tree = allocateEmptyTree(sizeof(int));

	if (size != 0)
	{
		binary_tree.root = intsArrayToBinaryTreeAux(binary_tree.root, arr, size);
	}

	return binary_tree;
}

BinaryTreeNode *intsArrayToBinaryTreeAux(BinaryTreeNode *root, int *arr, int size)
{
	BinaryTreeNode *root_node, *left_subtree, *right_subtree;
	int mid, right_mid, left_mid;

	mid = size / 2;
	right_mid = (size * 3) / 4;
	left_mid = (size * 1) / 4;

	root_node = allocateTreeNode(&arr[mid], sizeof(int));
	left_subtree = NULL;
	right_subtree = NULL;

	if (size / 2 != 0 && arr[right_mid] != -1)
	{
		right_subtree = intsArrayToBinaryTreeAux(root_node->right, arr + (mid + 1), size / 2);
	}

	if (size / 2 != 0 && arr[left_mid] != -1)
	{
		left_subtree = intsArrayToBinaryTreeAux(root_node->left, arr, size / 2);
	}

	root_node->right = right_subtree;
	root_node->left = left_subtree;

	return root_node;
}
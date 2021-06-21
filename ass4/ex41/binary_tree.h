#ifndef ___BINARY_TREE_H___
#define ___BINARY_TREE_H___
#include <stdbool.h>

#define MEMORY_ALLOCATION_ERROR 2
#define NON_EMPTY_TREE  1
#define EMPTY_TREE      0
#define NOT_FOUND      -1 

typedef struct _BinaryTreeNode {
	void *data;
	struct _BinaryTreeNode *right;
	struct _BinaryTreeNode *left;
} BinaryTreeNode;

typedef struct _BinaryTree {
	BinaryTreeNode *root;
	size_t type_size;
} BinaryTree;

//Allocates a new empty tree. 
BinaryTree allocateEmptyTree(size_t type_size);

//Gets the height of a given tree.
unsigned int getHeight(BinaryTree tree, void *(*g_max)(int, ...));

//Gets the number of levels in a given tree.
unsigned int getNumberOfLevels(BinaryTree tree, void *(*g_max)(int, ...));

//Gets the number of nodes in a given tree.
unsigned int getNumberOfNodes(BinaryTree tree);

//Allocates a new tree node.
BinaryTreeNode *allocateTreeNode(void *data, size_t size);

//Deallocates a given tree.
void clearTree(BinaryTree *tree);



//Prints a given tree in Inorder way.
void printInOrder(BinaryTree tree, void (*print_function)(void *));

//Prints a given tree in Preorder way.
void printPreOrder(BinaryTree tree, void (*print_function)(void *));

//Prints a given tree in Postorder way.
void printPostOrder(BinaryTree tree, void (*print_function)(void *));

//Prints a single level of a  given tree from left to right.
void printLeftToRightSingleLevel(BinaryTree tree, unsigned int required_level, void (*print_function)(void *));



//Returns a node with a given data
void *find(BinaryTree tree, void *data_to_search, int (*compare)(void *, void *));

//Returns a node with maximum data from a given tree.
void *getMaximum(BinaryTree tree, int *result, void *(*g_max)(int, ...));



//Builds a tree from a given array.
BinaryTree BuildTreeFromArray(int *arr, int  size);

//Turns an ints array into a binary tree.
BinaryTreeNode *intsArrayToBinaryTreeAux(BinaryTreeNode *root, int *arr, int size);

#endif
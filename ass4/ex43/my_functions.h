#ifndef ___MY_FUNCTIONS_H___
#define ___MY_FUNCTIONS_H___
#include <stdbool.h>

#define SIZE 100
#define LEFT 0
#define RIGHT 1

typedef struct listNode {
	int data;
	struct listNode *next;
} ListNode;

typedef struct list {
	ListNode *head;
	ListNode *tail;
} List;

typedef struct treeNode {
	int data;
	struct treeNode *parent;
	struct treeNode *left;
	struct treeNode *right;
} TreeNode;

typedef struct tree {
	TreeNode *root;
	List leafList;
} Tree;


//Build tree from a given array with list of all the tree leafs.
Tree BuildTreeFromArrayWithLeafList(int *arr, int size);

//Allocates a new binary tree from a given array.
Tree allocateBinaryTreeFromArray(int *arr, int size);

//Allocates a new list for a given tree.
List allocateList(Tree tree);

//allocateList auxiliary function.
void allocateListAux(TreeNode *root, List *list);


//Create a new node with the given data and inserts the node to the end of a list.
void insertDataToEndList(List *list, int data);

//Inserts a node to end of a list.
void insertNodeToEndList(List *list, ListNode *node_to_add);

//Allocates a new list node.
ListNode *allocateListNode(int data, ListNode *next);



//Finds a node in a tree.
TreeNode *findParentNode(Tree tree, int parentData, int branchSelect);

//findParentNode auxiliary function.
TreeNode *findParentNodeAux(TreeNode *root, int parentData, int branchSelect);

//Adds a leaf to a tree after a given parent node.
Tree AddLeaf(Tree tree, TreeNode *parent, int branchSelect, int parentData);


//Prints the leaf list of the tree.
void printLeafList(Tree tree);

//Prints tree Inorder.
void printTreeInorder(Tree tree);

//printTreeInorder auxiliary function.
void printTreeInorderAux(TreeNode *root);



//Deallocates a list.
void freeList(List *list);

//Deallocates all tree elements.
void freeTree(Tree tree);

//freeTree auxiliary function.
void freeTreeAux(TreeNode *root);


//Checks if a pointer points to a memory located in the heap.
void checkMemoryAlloc(void *ptr);

#endif
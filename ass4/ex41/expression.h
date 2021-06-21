#ifndef ___EXPRESSION_H___
#define ___EXPRESSION_H___
#include <stdbool.h>
#include "binary_tree.h"

#define EXPRESSION_SIZE 100

//Builds an expression tree from a given string.
bool buildExpressionTree(char str[], BinaryTree *tr);

//Converts infix expression into a postfix expression.
void convertInfixToPostfix(char str[]);

//Checks if a given expression is valid or not.
bool isValidExpression(char str[]);

//Converts postfix expression into a binary tree expression.
void convertPostfixExpToBinaryTreeExp(char postfix_exp[], BinaryTree *binary_tree_exp_out);

//Returns the precedence of a given operator.
int operatorPrecedence(char c);

//Checks if a given char is an operand or not.
bool isOperand(char ch);

//Checks if a given char is an operator or not.
bool isOperator(char ch);

//Evaluates a given expression tree.
int evaluateExpressionTree(BinaryTree *binary_tree);

//evaluateExpressionTree auxiliary function.
int evaluateExpressionTreeAux(BinaryTreeNode *binary_tree_root);

//Prints the value of a given expression tree.
void printExpressionTreeValue(BinaryTree *binary_tree);

#endif
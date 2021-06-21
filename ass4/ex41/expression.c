#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "expression.h"
#include "stack.h"
#include "binary_tree.h"
#include "generic_functions.h"

bool buildExpressionTree(char str[], BinaryTree *tr)
{
	char string_duplication[EXPRESSION_SIZE];
	
	strcpy(string_duplication, str);
	
	*tr = allocateEmptyTree(sizeof(char));

	if (!isValidExpression(string_duplication))
	{
		return false;
	}

	convertInfixToPostfix(string_duplication);
	convertPostfixExpToBinaryTreeExp(string_duplication, tr);

	return true;
}

void convertPostfixExpToBinaryTreeExp(char postfix_exp[], BinaryTree *binary_tree_exp_out)
{
	int i;
	char ch;
	Stack stack;
	BinaryTreeNode *new_node_p;

	stack = createEmptyStack(sizeof(BinaryTreeNode *));

	for (i = 0; postfix_exp[i] != '\0'; i++)
	{
		ch = postfix_exp[i];

		if (isOperand(ch))
		{
			new_node_p = allocateTreeNode(&ch, sizeof(char));
			push(&stack, &new_node_p);
		}
		else
		{
			BinaryTreeNode *right_node = *(BinaryTreeNode **)pop(&stack);
			BinaryTreeNode *left_node = *(BinaryTreeNode **)pop(&stack);

			new_node_p = allocateTreeNode(&ch, sizeof(char));
			new_node_p->right = right_node;
			new_node_p->left = left_node;

			push(&stack, &new_node_p);
		}
	}

	binary_tree_exp_out->root = *(BinaryTreeNode **)pop(&stack);
	binary_tree_exp_out->type_size = sizeof(char);
}

void convertInfixToPostfix(char str[])
{
	char postfix_expression[EXPRESSION_SIZE];
	Stack stack;
	int i, write_index;
	
	stack = createEmptyStack(sizeof(char));
	write_index = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (isOperand(str[i]))
		{
			postfix_expression[write_index] = str[i];
			write_index++;
		}
		else if (str[i] == '(')
		{
			push(&stack, &str[i]);
		}
		else if (str[i] == ')')
		{
			while (*(char *)peek(&stack) != '(') 
			{
				postfix_expression[write_index] = *(char *)pop(&stack);
				write_index++;
			}
			pop(&stack);
		}
		else if ( (stack.top == NULL) || (*(char *)peek(&stack) == '(') || (operatorPrecedence(str[i]) > operatorPrecedence(*(char *)peek(&stack))) )
		{
			push(&stack, &str[i]);
		}
		else
		{
			while ( (stack.top != NULL) && (operatorPrecedence(str[i]) <= operatorPrecedence(*(char *)peek(&stack)))) 
			{
				postfix_expression[write_index] = *(char *)pop(&stack);
				write_index++;
			}
			push(&stack, &str[i]);
		}
	}
	
	while (stack.top != NULL) 
	{
		postfix_expression[write_index] = *(char *)pop(&stack);
		write_index++;
	}
	
	postfix_expression[write_index] = '\0';

	for (i = 0; postfix_expression[i] != '\0'; i++)
		str[i] = postfix_expression[i];

	str[i] = '\0';
}

bool isValidExpression(char str[])
{
	int i;
	int open_brackets_count = 0, close_brackets_count = 0;
	int digits_in_row = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '(')
			open_brackets_count++;

		if (str[i] == ')')
			close_brackets_count++;

		if (str[i] >= '0' && str[i] <= '9')
			digits_in_row++;
		else
			digits_in_row = 0;

		if (digits_in_row >= 2)
			return false;
	}

	if (open_brackets_count != close_brackets_count)
		return false;

	return true;
}

int operatorPrecedence(char c)
{
	switch (c)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
	case '%':
		return 2;
	}

	return -1;
}

bool isOperand(char ch) 
{
	return ch >= '0' && ch <= '9';
}

bool isOperator(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%';
}

int evaluateExpressionTree(BinaryTree *binary_tree)
{
	if (binary_tree->root == NULL)
	{
		return 0;
	}
	else
	{
		return evaluateExpressionTreeAux(binary_tree->root);
	}
}

int evaluateExpressionTreeAux(BinaryTreeNode *binary_tree_root)
{
	int left_subtree_value, right_subtree_value, root_data_value;
	char root_data_char;

	left_subtree_value = 0;
	right_subtree_value = 0;
	root_data_char = *(char *)binary_tree_root->data;

	if (binary_tree_root->left == NULL && binary_tree_root->right == NULL)
	{
		root_data_value = atoi(&root_data_char);
		return root_data_value;
	}

	if (binary_tree_root->left != NULL)
	{
		left_subtree_value = evaluateExpressionTreeAux(binary_tree_root->left);
	}

	if (binary_tree_root->right != NULL)
	{
		right_subtree_value = evaluateExpressionTreeAux(binary_tree_root->right);
	}


	if (root_data_char == '+')
	{
		return left_subtree_value + right_subtree_value;
	}
	else if (root_data_char == '-')
	{
		return left_subtree_value - right_subtree_value;
	}
	else if (root_data_char == '*')
	{
		return left_subtree_value * right_subtree_value;
	}
	else if (root_data_char == '/')
	{
		return left_subtree_value / right_subtree_value;
	}
	else
	{
		return left_subtree_value % right_subtree_value;
	}
}

void printExpressionTreeValue(BinaryTree *binary_tree) 
{
	int expression_tree_value;

	expression_tree_value = evaluateExpressionTree(binary_tree);
	printf("%d", expression_tree_value);
}
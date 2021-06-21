#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"
#include "binary_tree.h"
#include "generic_functions.h"
#include "expression.h"

int main() 
{
    char str[EXPRESSION_SIZE];
    BinaryTree tr;
    double res;
    bool expressionOK;

    gets(str);
    expressionOK = buildExpressionTree(str, &tr);

    if (expressionOK == true)
    {
        res = evaluateExpressionTree(&tr);
        printf("%s = %.2f", str, res);
    }
    else 
    {
        printf("The input expression is not valid\n");
    }

    clearTree(&tr);
}

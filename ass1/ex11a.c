// Full Name: Yaniv Avrahami 
// ID: 302374921

/* 
This program prints a multiplication table of size 10x10
*/

#include <stdio.h>
#define TABLESIZE 10

//This function gets the size of the multiplication table and prints
//a multiplication table with the given size
void printMultTable(int size);

//This function gets a number and
//returns his amount of digits
int numberOfDigits(int n);

int main() 
{
	printMultTable(TABLESIZE);
}

void printMultTable(int size) 
{
	int i, j;
	int maxNumberInCol;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			maxNumberInCol = size * (j + 1);

			if (j == 0) 
			{
				printf("%*d", numberOfDigits(maxNumberInCol), (i + 1) * (j + 1));
			}
			else
			{
				printf("%*d", numberOfDigits(maxNumberInCol) + 1, (i + 1) * (j + 1));
			}
			
		}
		printf("\n");
	}
}

int numberOfDigits(int n) 
{
	int count = 0;

	if (n == 0)
		return 1;

	while (n != 0) 
	{
		count++;
		n /= 10;
	}

	return count;
}
// Full Name: Yaniv Avrahami 
// ID: 302374921

/*
This program has a function which transforms a formatted string with conversion characters and a numbers string
into a string which contains the numbers correspondingly to the conversion characters
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

//This function transforms a formatted string with conversion characters and a numbers strings
//into a string which contains the numbers correspondingly to the conversion characters
void printFormattedIntegers(char* format, char* numbers);

//Prints the binary representation of a given number
void printBin(int num);

//Prints the octal representation of a given number
void printOct(int num);

//Prints the decimal representation of a given number
void printDec(int num);

//Prints the hexadecimal representation of a given number
void printHex(int num);

//Prints the roman representation of a given number
void printRom(int num);

//Converts string to integer 
int stringToInt(char* str);

//Converts string with integers to array 
int* stringToIntsArr(char str[], int* outSize);

//Counts the amount of integers in a string
int countIntsInString(char str[]);

void main()
{
	char format[100];
	char numbers[100];
	
	gets(format);

	gets(numbers);

	printFormattedIntegers(format, numbers);
}

void printFormattedIntegers(char* format, char* numbers) 
{
	int i, j = 0, currentNumber, numsSize;
	char* currentToken;
	int* nums;

	nums = stringToIntsArr(numbers, &numsSize);
	
	for (i = 0; format[i]; i++)
	{
		currentNumber = nums[j];

		if (format[i] == '%') 
		{
			switch (format[i + 1]) 
			{
				case 'b':
					printBin(currentNumber);
					break;
				case 'd':
					printDec(currentNumber);
					break;
				case 'o':
					printOct(currentNumber);
					break;
				case 'x':
					printHex(currentNumber);
					break;
				case 'r':
					printRom(currentNumber);
					break;
			}
			j++;
			i++;
		}
		else
		{
			putchar(format[i]);
		}
	}
}

void printBin(int num) 
{
	if (num == 0)
		return;
	else 
	{
		printBin(num / 2);
		printf("%d", num % 2);
	}
}

void printOct(int num) 
{
	if (num == 0)
		return;
	else
	{
		printOct(num / 8);
		printf("%d", num % 8);
	}
}

void printDec(int num) 
{
	printf("%d", num);
}

void printHex(int num) 
{
	if (num == 0)
		return;
	else
	{
		printHex(num / 16);
		if (num % 16 > 9) 
			printf("%c", (num % 16) - 10 + 'A' );
		else
			printf("%d", num % 16);
	}
}

void printRom(int num) 
{
	int i, j, count;

	int values[] = { 1, 4, 5, 9, 10, 40, 50, 
					 90, 100, 400, 500, 900, 1000 };

	char* symbols[] = { "I", "IV", "V", "IX", "X", "XL", "L", 
						"XC", "C", "CD", "D", "CM", "M" };

	for (i = 12; i >= 0; i--)
	{
		count = num / values[i];

		for (j = 0; j < count; j++) 
			printf("%s", symbols[i]);

		num = num % values[i];
	}
}

int stringToInt(char* str) 
{
	int i, len, dec = 0;
	
	len = strlen(str);

	for (i = 0; i < len; i++) 
	{
		dec *= 10;
		dec += str[i] - '0';
	}

	return dec;
}

int* stringToIntsArr(char str[], int* outLength) 
{
	char* strDup = strdup(str);
	
	if (!strDup) 
	{
		printf("Memory allocation failed!\n");
		exit(-1);
	}
	
	char* currToken;
	int i = 0;
	int length = countIntsInString(strDup);
	int currInt;
	
	int* intArr = (int*)malloc(length * sizeof(int));
	if (!intArr) 
	{
		printf("Memory allocation failed!\n");
		exit(-1);
	}
	
	if (length > 0) 
	{
		currToken = strtok(strDup, " ");
		intArr[i] = stringToInt(currToken);
		i++;
		currToken = strtok(NULL, " ");
		while (currToken != NULL) 
		{
			currInt = stringToInt(currToken);
			intArr[i] = currInt;
			i++;
			currToken = strtok(NULL, " ");
		}
	}
		
	*outLength = length;
    	free(strDup);
	return intArr;
}

int countIntsInString(char str[]) 
{
	int count = 0;

	char* strCopy = strdup(str);

    if (!strCopy) 
	{
		printf("Memory allocation failed!\n");
		exit(-1);
	}

	if (strtok(strCopy, " ") == NULL)
		return 0;
	else
		count++;

	while (strtok(NULL, " ") != NULL)
		count++;
	
	free(strCopy);
	
	return count;
}
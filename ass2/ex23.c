//Full Name: Yaniv Avrahami
//ID: 302374921

#define _CRT_SECURE_NO_WARNINGS
#define INIT_VALUE 1
#define ALLOCATION_ERROR -1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// removes pointed characters from a string array
int RemoveFromStrArray(char*** pStringArray, int stringArraySize, char** pointerArray);

// set the pointers to the addresses of the characters in the string array
char** setPtrToCharsArray(char** strings);

// gets a string from the user into a dynamic array
char* getString();

// gets strings from the user
char** getStrArrayInput(int* psize);

// doubles the size of a given array
char* doubleArraySize(char* array, int* psize);

// changes the array size to a given logical size
char* fixArraySize(char* array, int logicalSize);

// Checks if allocation was successful or not.
void checkAllocation(void* pointer);

// prints the strings array
void printArray(char** strings, int size);

// prints the characters that are pointed by the pointers array
void printPointersData(char** pointers);

// removes all the occurrences of a given char in a given string
void removeAllChars(char* string, char c);

// removes a given char in a given string
void removeChar(char* string, char c);

// gives the number of occurrences of a given character
int countChar(char* string, char c);

// swaps between two chars
void swap(char* pa, char* pb);

// deallocates all strings in the string array
void freeArray(char** strings, int size);

int main()
{
	char** str_array;
	unsigned int str_array_size;
	char** ptr_to_chars_array;
	unsigned int res;
	
	str_array = getStrArrayInput(&str_array_size);
	ptr_to_chars_array = setPtrToCharsArray(str_array);
	res = RemoveFromStrArray(&str_array, str_array_size, ptr_to_chars_array);
	printArray(str_array, str_array_size - res);

	freeArray(str_array, str_array_size - res);
	free(ptr_to_chars_array);
}

int RemoveFromStrArray(char*** pStringArray, int stringArraySize, char** pointerArray)
{
	char** strArr = *pStringArray;
	int i, removed = 0;;
	char* temp;

	for (i = 0; pointerArray[i]; i++)
	{
		*(pointerArray[i]) = '\n';
	}

	for (i = 0; i < stringArraySize; i++)
	{
		removeAllChars(strArr[i], '\n');
		temp = (char*)realloc(strArr[i], sizeof(char) * (strlen(strArr[i]) + 1) );
		if (temp != NULL) 
			strArr[i] = temp;
		else 
		{
			fprintf(stderr, "Allocation failed.");
			exit(ALLOCATION_ERROR);
		}
	}

	// removing empty strings from strings array
	for (i = 0; i < stringArraySize; i++)
	{
		if (strArr[i][0] == '\0')
		{
			free((strArr[i]));
			memcpy(strArr + i, strArr + i + 1, (stringArraySize - i - 1) * sizeof(char*));
			stringArraySize--;
			strArr = (char**)realloc(strArr, sizeof(char*) * stringArraySize);
			checkAllocation(strArr);
			i--;
			removed++;
		}
	}

	*pStringArray = strArr;
	return removed;
}

char** setPtrToCharsArray(char** strings)
{
	char** res;
	int size, i;
	int str_array_row, str_array_col;

	scanf("%d", &size); // Get number of ptrs

	res = (char**)malloc(sizeof(char*) * (size + 1)); // Add 1 for NULL at the end
	checkAllocation(res);

	for (i = 0; i < size; i++)
	{
		scanf("%d", &str_array_row);
		scanf("%d", &str_array_col);
		res[i] = strings[str_array_row] + str_array_col;
	}

	res[size] = NULL; // Set the last one to NULL
	return res;
}

char* getString()
{
	char nextCharacter;
	char* array;
	int logicalSize, physicalSize;

	logicalSize = 0;
	physicalSize = INIT_VALUE;
	array = (char*)malloc(physicalSize * sizeof(char));
	nextCharacter = getchar();

	while (nextCharacter != '\n')
	{
		if (logicalSize == physicalSize)
		{
			array = doubleArraySize(array, &physicalSize);
		}

		array[logicalSize] = nextCharacter;
		logicalSize++;
		nextCharacter = getchar();
	}

	if (logicalSize == physicalSize)
	{
		array = doubleArraySize(array, &physicalSize);
	}
	array[logicalSize] = '\0';
	logicalSize++;

	array = fixArraySize(array, logicalSize);

	return array;
}

char** getStrArrayInput(int* psize)
{
	char** strings;
	int size;
	int i;

	scanf("%d", &size);
	strings = (char**)malloc(sizeof(char*) * size);

	getchar();

	for (i = 0; i < size; i++)
		strings[i] = getString();

	*psize = size;
	return strings;
}

char* doubleArraySize(char* array, int* psize)
{
	*psize *= 2;
	array = (char*)realloc(array, *psize * sizeof(char));
	checkAllocation(array);
	return array;
}

char* fixArraySize(char* array, int logicalSize)
{
	array = (char*)realloc(array, logicalSize * sizeof(char));
	checkAllocation(array);
	return array;
}

void checkAllocation(void* pointer)
{
	if (pointer == NULL)
	{
		fprintf(stderr, "Allocation failed.");
		exit(ALLOCATION_ERROR);
	}
}

void printArray(char** strings, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		puts(strings[i]);
	}
}

void printPointersData(char** pointers)
{
	int i;
	char nextCharacter;
	for (i = 0; pointers[i] != NULL; i++)
	{
		nextCharacter = *(pointers[i]);
		putchar(nextCharacter);
		putchar('\n');
	}
}

void removeAllChars(char* string, char c) 
{
	int i;
	int times = countChar(string, c);

	for (i = 0; i < times; i++)
	{
		removeChar(string, c);
	}

}

void removeChar(char* string, char c) 
{
	int i;
	int stringLength = strlen(string);
	for (i = 0; i < stringLength; i++)
	{
		if (string[i] == c)
		{
			swap(&string[i], &string[i + 1]);
		}
	}
}

int countChar(char* string, char c) 
{
	int i, count = 0;
	for (i = 0; string[i] != '\0'; i++)
	{
		if (string[i] == c)
		{
			count++;
		}
	}
	return count;
}

void swap(char* pa, char* pb) 
{
	char temp = *pa;
	*pa = *pb;
	*pb = temp;
}

void freeArray(char** strings, int size) 
{
	int i;
	for (i = 0; i < size; i++)
	{
		free(strings[i]);
	}
}
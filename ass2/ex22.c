//Full Name: Yaniv Avrahami
//ID: 302374921

/*
	This program let a user enter two polynoms and 
	the program prints the product and the sum of the 
	two polynoms.
*/

#define _CRT_SECURE_NO_WARNINGS
#define INIT_VALUE 1
#define ALLOCATION_ERROR -1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct monom {
	int coefficient;
	int power;
} Monom;

// Sums monom and a polynom, and returns a new polynom.
Monom* sumMonomAndPolynom(Monom monom, Monom* polynom, int* psize);

// Sums two polynoms, and returns a new polynom.
Monom* sumTwoPolynoms(Monom* polynom1, int n, Monom* polynom2, int m, int* outSize);

// Multiplies two polynoms, and returns a new polynom.
Monom* multiplyTwoPolynoms(Monom* polynom1, int n, Monom* polynom2, int m, int* outSize);

// Checks if allocation was successful or not.
void checkAllocation(void* pointer);

// Sorts the monoms that are inside a polynom.
void mergeSort(Monom* polynom, int n);

// Combines two sorted polynoms into a new sorted polynom
void merge(Monom* dest, Monom* polynom1, int n, Monom* polynom2, int m);

// Prints a given polynom
void printPolynom(Monom* polynom, int size);

// gets a string from the user into a dynamic array
char* getString();

// double the size of a given array
char* doubleArraySize(char* array, int* psize);

// gets a polynom from the user
Monom* getPolynom(unsigned int* size);

// changes the array size to a given logical size
char* fixArraySize(char* array, int logicalSize);

// counts the amount of words inside a string
int countWords(char* string);

// extracts all the numbers from a given string into an dynamic array
int* extractNumbers(char* string, int* psize);

// converts a given string into int
int convertToInt(char* string);

// prints the sum of two polynoms
void printPolySum(Monom* polynom1, int n, Monom* polynom2, int m);

// prints the product of two polynoms
void printPolyMul(Monom* polynom1, int n, Monom* polynom2, int m);

int main()
{
	Monom* polynom1, * polynom2;             // The input polynoms
	unsigned int polynom1Size, polynom2Size; // The size of each polynom

	printf("Please enter the first polynom:\n");
	polynom1 = getPolynom(&polynom1Size);   // get polynom 1

	printf("Please enter the second polynom:\n");
	polynom2 = getPolynom(&polynom2Size);   // get polynom 2

	printf("The multiplication of the polynoms is:\n"); // print the multiplication
	printPolyMul(polynom1, polynom1Size, polynom2, polynom2Size);
	printf("\n");

	printf("The sum of the polynoms is:\n"); // print the sum
	printPolySum(polynom1, polynom1Size, polynom2, polynom2Size);
	printf("\n");

	free(polynom1); // releasing all memory allocations
	free(polynom2);
}

void printPolySum(Monom* polynom1, int n, Monom* polynom2, int m)
{
	int polynomSumSize;
	Monom* polynomSum = sumTwoPolynoms(polynom1, n, polynom2, m, &polynomSumSize);
	printPolynom(polynomSum, polynomSumSize);
}

void printPolyMul(Monom* polynom1, int n, Monom* polynom2, int m)
{
	int polynomMultSize;
	Monom* polynomMult = multiplyTwoPolynoms(polynom1, n, polynom2, m, &polynomMultSize);
	printPolynom(polynomMult, polynomMultSize);
}

Monom* getPolynom(unsigned int* size)
{
	Monom* polynom;
	int polynomSize;
	char* string;
	int i;
	int* numbers;
	int numOfNumbers;
	Monom nextMonom;

	polynom = NULL;
	polynomSize = 0;

	string = getString();
	numbers = extractNumbers(string, &numOfNumbers);

	for (i = 0; i < numOfNumbers; i += 2)
	{
		nextMonom.coefficient = numbers[i];
		nextMonom.power = numbers[i + 1];
		polynom = sumMonomAndPolynom(nextMonom, polynom, &polynomSize);
	}

	*size = polynomSize;
	return polynom;
}

Monom* sumTwoPolynoms(Monom* polynom1, int n, Monom* polynom2, int m, int* outSize)
{
	int i, size = n;
	for (i = 0; i < m; i++)
	{
		polynom1 = sumMonomAndPolynom(polynom2[i], polynom1, &size);
	}

	*outSize = size;
	return polynom1;
}

Monom* multiplyTwoPolynoms(Monom* polynom1, int n, Monom* polynom2, int m, int* outSize)
{
	Monom* newPolynom = NULL;
	int newPolynomSize = 0;
	Monom nextMonom;
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			nextMonom.coefficient = polynom1[i].coefficient * polynom2[j].coefficient;
			nextMonom.power = polynom1[i].power + polynom2[j].power;
			newPolynom = sumMonomAndPolynom(nextMonom, newPolynom, &newPolynomSize);
		}
	}
	*outSize = newPolynomSize;
	return newPolynom;
}

Monom* sumMonomAndPolynom(Monom monom, Monom* polynom, int* psize)
{
	int size = *psize;

	if (monom.coefficient == 0)
	{
		return polynom;
	}

	if (size == 0)
	{
		size++;
		polynom = (Monom*)malloc(size * sizeof(Monom));
		checkAllocation(polynom);
		polynom[0] = monom;
	}
	else
	{
		bool samePowerExist = false;
		int i;
		for (i = 0; i < size; i++)
		{
			if (monom.power == polynom[i].power)
			{
				polynom[i].coefficient += monom.coefficient;
				samePowerExist = true;
				break;
			}
		}

		if (!samePowerExist)
		{
			size++;
			polynom = (Monom*)realloc(polynom, size * sizeof(Monom));
			checkAllocation(polynom);
			polynom[size - 1] = monom;
			mergeSort(polynom, size);
		}
	}

	*psize = size;
	return polynom;
}

void mergeSort(Monom* polynom, int n)
{
	Monom* tempPolynom;

	if (n < 2)
		return;
	else
	{
		mergeSort(polynom, n / 2);
		mergeSort(polynom + n / 2, n - n / 2);
		tempPolynom = (Monom*)malloc(n * sizeof(Monom));
		checkAllocation(tempPolynom);
		merge(tempPolynom, polynom, n / 2, polynom + n / 2, n - n / 2);
		memcpy(polynom, tempPolynom, n * sizeof(Monom));
		free(tempPolynom);
	}

}

void merge(Monom* destination, Monom* polynom1, int n, Monom* polynom2, int m)
{
	int i, j, k;
	i = j = k = 0;

	while (i < n && j < m)
	{
		if (polynom1[i].power > polynom2[j].power)
		{
			destination[k] = polynom1[i];
			i++;
		}
		else
		{
			destination[k] = polynom2[j];
			j++;
		}
		k++;
	}

	while (i < n)
	{
		destination[k] = polynom1[i];
		i++;
		k++;
	}

	while (j < m)
	{
		destination[k] = polynom2[j];
		j++;
		k++;
	}
}

void checkAllocation(void* pointer)
{
	if (pointer == NULL)
	{
		fprintf(stderr, "Allocation failed.");
		exit(ALLOCATION_ERROR);
	}
}

void printPolynom(Monom* polynom, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{

		if (i == 0 && polynom[i].coefficient < 0)
		{
			printf("- ");
		}

		if (i != 0)
		{
			if (polynom[i].coefficient > 0)
				printf("+ ");
			else
				printf("- ");
		}

		if (polynom[i].power == 0)
			printf("%d ", abs(polynom[i].coefficient));
		else if (polynom[i].power == 1)
			printf("%dx ", abs(polynom[i].coefficient));
		else
			printf("%dx^%d ", abs(polynom[i].coefficient), polynom[i].power);

	}
	printf("\n");
}

char* getString()
{
	char nextCharacter;
	char* array;
	int logicalSize, physicalSize;

	logicalSize = 0;
	physicalSize = INIT_VALUE;
	array = (char*)malloc(physicalSize * sizeof(char));
	checkAllocation(array);
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

int countWords(char* string)
{
	int count;
	char* stringCopy;
	char delimiters[] = " \t";

	count = 0;
	stringCopy = strdup(string);
    checkAllocation(stringCopy);

	if (strtok(stringCopy, delimiters) != NULL)
	{
		count++;
		while (strtok(NULL, delimiters) != NULL)
		{
			count++;
		}
	}
    
    free(stringCopy);
	return count;
}

int* extractNumbers(char* string, int* psize)
{
	char* nextToken = NULL;
	int* numbers;
	int i;
	int logicalSize, physicalSize;
	char delimiters[] = " \t";

	logicalSize = 0;
	physicalSize = countWords(string);
	if (physicalSize == 0)
	{
		*psize = 0;
		return NULL;
	}

	numbers = (int*)malloc(physicalSize * sizeof(int));
	checkAllocation(numbers);

	nextToken = strtok(string, delimiters);
	numbers[0] = convertToInt(nextToken);
	logicalSize++;

	for (i = 1; i < physicalSize; i++)
	{
		nextToken = strtok(NULL, delimiters);
		numbers[i] = convertToInt(nextToken);
		logicalSize++;
	}

	*psize = logicalSize;
	return numbers;
}

int convertToInt(char* string)
{
	int integer;
	sscanf(string, "%d", &integer);
	return integer;
}
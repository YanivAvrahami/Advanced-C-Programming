#ifndef ARR_H
#define ARR_H
#include <stdbool.h>

#define SIZE 100

// copy an int array
void copyIntArr(int dest[], int src[], int size);

// print an int array
void printIntArr(int *arr, int size);

// checks if two char arrays are equal
bool isEqualCharArr(char *arr1, char *arr2, int size);

// gets an int array from user
int *getIntArr(int *psize);

// gets a string array from user
char **getStringArr(int *size);

// prints a string array
void printStringArr(char **strArr, int size);

// duplicates a string array
char **dupStrArr(char **strArr, int size);

#endif
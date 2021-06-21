#ifndef ___GENERIC_FUNCTIONS_H___
#define ___GENERIC_FUNCTIONS_H___
#include <stdbool.h>
#include <stdarg.h>

//Compares two ints
int compareInts(void *num_1, void *num_2);

//Compares two chars
int compareChars(void *char_1, void *char_2);

//Returns max number.
void *maxInt(int number_of_args, ...);

//Returns max char.
void *maxChar(int number_of_args, ...);

//Prints a given char.
void printChar(void *ch);

//Prints a given string.
void printString(void *string);

//Prints a given integer.
void printInt(void *integer);

//Prints a given BinaryTreeNode that hold a char.
void printCharBinaryTreeNode(void *node);

//Checks a given pointer for successful memory allocation.
void checkMemoryAlloc(void *ptr);

#endif
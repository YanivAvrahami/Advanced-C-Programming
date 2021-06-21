#ifndef ___UTIL_H___
#define ___UTIL_H___

#define ALLOC_FAILED 1

// allocating memory and checking memory allocation
void *safeMalloc(size_t typeSize, int numOfElems);
// reallocing memory and checking memory allocation
void *safeRealloc(void *block, size_t typeSize, int numOfElems);
// checking memory allocation
void  checkAlloc(void *ptr);

// printing string arr
void   printStrArr(char **strArr, int size);
// removes uppercase letters from string
char  *removeUppercase(char *str);
// counts lowercase letters in string
int    countLowercase(char *str);
// sorts a string arr lexicographically
char **sortLexicographically(char **strArr, int size);
// swaps between two string pointers
void   swap(char **pa, char **pb);


#endif
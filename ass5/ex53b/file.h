#ifndef ___FILE_H___
#define ___FILE_H___
#include <stdio.h>

#define OPEN_FILE_FAILED 2
#define FILE_EXTENSION_LEN 4

// reading a string from file using short int as name length
char*  freadStr2(FILE *fp);
// reading a string from file using int as name length
char*  freadStr(FILE *fp);
// reading a long int from file
long   freadLong(FILE *fp);
// reading an int from file
int    freadInt(FILE *fp);
// reading a float from file
float  freadFloat(FILE *fp);
// reading a double from file
double freadDouble(FILE *fp);
// reading a short int from file
short  freadShort(FILE *fp);
// reading a char from file
char   freadChar(FILE *fp);

// writing an int to file
void   fwriteInt(FILE *fp, int x);
// writing a string to file
void   fwriteStr(FILE *fp, char *x);
// writing a long to file
void   fwriteLong(FILE *fp, long x);
// writing a float to file
void   fwriteFloat(FILE *fp, float x);
// writing a double to file
void   fwriteDouble(FILE *fp, double x);
// writing a short to file
void   fwriteShort(FILE *fp, short x);
// writing a char to file
void   fwriteChar(FILE *fp, char x);

// creating a text file that will contain string arr
void   createTextFile(char *filename, char **strArr, int size);
// printing a text file
void   printTextFile(char *filename);
// concatenating ".txt" to string
char*  addTxtExtension(char *str);
// concatenating ".ind" to string
char*  addIndExtension(char *fname);

// checking if the fpi of a file is in the end of the file
// returns non-zero else returns 0
int    isEndOfFile(FILE *fp);
// checking if file opened successfuly
void   checkFileOpen(FILE *fp);
// opening a file and checking if it was open successfuly
FILE*  safeFileOpen(char *filename, char *mode);

#endif
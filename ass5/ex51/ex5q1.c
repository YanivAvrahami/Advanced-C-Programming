#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "file.h"
#include "util.h"

void Exe5Q1(char *fname, unsigned int x)
{
	char **strArr;
	FILE *fp;
	int currCharCount;
	int i;

	strArr = (char *)safeMalloc(sizeof(char *), x);

	fp = safeFileOpen(fname, "rb");
	for (i = 0; i < x; i++)
		strArr[i] = freadStr(fp);
	fclose(fp);

	for (i = 0; i < x; i++)
		strArr[i] = removeUppercase(strArr[i]);

	strArr = sortLexicographically(strArr, x);


	fname = addTxtExtension(fname);

	createTextFile(fname, strArr, x);
}
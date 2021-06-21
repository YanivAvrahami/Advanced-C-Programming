#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "file.h"
#include "util.h"



char  *freadStr(FILE *fp)
{
	char *res;
	int strLen;
	int i;

	strLen = freadInt(fp) + 1;
	res = (char *)safeMalloc(sizeof(char), strLen);
	fread(res, sizeof(char), strLen - 1, fp);
	res[strLen - 1] = '\0';

	return res;
}
char  *freadStr2(FILE *fp)
{
	char *res;
	int strLen;
	int i;

	strLen = freadShort(fp) + 1;
	res = (char *)safeMalloc(sizeof(char), strLen);
	fread(res, sizeof(char), strLen - 1, fp);
	res[strLen - 1] = '\0';

	return res;
}
long   freadLong(FILE *fp)
{
	long res;
	fread(&res, sizeof(long), 1, fp);
	return res;
}
int    freadInt(FILE *fp)
{
	int res;
	fread(&res, sizeof(int), 1, fp);
	return res;
}
double freadDouble(FILE *fp)
{
	double res;
	fread(&res, sizeof(double), 1, fp);
	return res;
}
float  freadFloat(FILE *fp)
{
	float res;
	fread(&res, sizeof(float), 1, fp);
	return res;
}
short  freadShort(FILE *fp)
{
	short res;
	fread(&res, sizeof(short), 1, fp);
	return res;
}
char   freadChar(FILE *fp)
{
	char res;
	fread(&res, sizeof(char), 1, fp);
	return res;
}

void fwriteStr(FILE *fp, char *x) 
{
	int i;
	int size;
	size = strlen(x);
	for (i = 0; i < size; i++)
		fwriteChar(fp, x[i]);
}
void fwriteLong(FILE *fp, long x) 
{
	fwrite(&x, sizeof(long), 1, fp);
}
void fwriteInt(FILE *fp, int x)
{
	fwrite(&x, sizeof(int), 1, fp);
}
void fwriteFloat(FILE *fp, float x) 
{
	fwrite(&x, sizeof(float), 1, fp);
}
void fwriteDouble(FILE *fp, double x) 
{
	fwrite(&x, sizeof(double), 1, fp);
}
void fwriteShort(FILE *fp, short x) 
{
	fwrite(&x, sizeof(short), 1, fp);
}
void fwriteChar(FILE *fp, char x) 
{
	fwrite(&x, sizeof(char), 1, fp);
}

void  createTextFile(char *filename, char **strArr, int size)
{
	FILE *fp;
	int i;

	fp = safeFileOpen(filename, "w");

	for (i = 0; i < size; i++)
	{
		fputs(strArr[i], fp);
		fputc('\n', fp);
	}
	fclose(fp);
}
void  printTextFile(char *filename)
{
	FILE *fp;
	int c;

	fp = safeFileOpen(filename, "r");

	while ((c = fgetc(fp)) != EOF)
		putchar(c);

	fclose(fp);
}
char *addTxtExtension(char *str)
{
	char *res;
	char ext[FILE_EXTENSION_LEN + 1] = ".txt";
	int i;
	int strLen;

	strLen = strlen(str);
	res = (char *)safeMalloc(sizeof(char), strLen + FILE_EXTENSION_LEN + 1);

	for (i = 0; i < strLen; i++)
		res[i] = str[i];

	for (i = 0; i < FILE_EXTENSION_LEN; i++)
		res[i + strLen] = ext[i];

	res[i + strLen] = '\0';

	return res;
}

char *addIndExtension(char *fname) 
{
	char *res;
	res = safeMalloc(sizeof(char), strlen(fname) + FILE_EXTENSION_LEN + 1);
	strcpy(res, fname);
	strcat(res, ".ind");
	return res;
}

int isEndOfFile(FILE *fp)
{
	int c;
	if ((c = fgetc(fp)) == EOF)
		return 1;
	else
	{
		ungetc(c, fp);
		return 0;
	}
}

FILE *safeFileOpen(char *filename, char *mode)
{
	FILE *res;
	res = fopen(filename, mode);
	checkFileOpen(res);
	return res;
}
void  checkFileOpen(FILE *fp)
{
	if (fp == NULL)
	{
		fprintf(stderr, "FAILED TO OPEN FILE!");
		exit(OPEN_FILE_FAILED);
	}
}
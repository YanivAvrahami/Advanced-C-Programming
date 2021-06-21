#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "file.h"
#include "util.h"
#include "ex5q3.h"

void      Exe5Q3(char *fname) 
{
	STUDENT *studentArr;
	STUDENT *studentPtrArr;
	int size;
	char **nameArr;
	int nameArrSize;

	studentArr = LoadStudentsFromFile(fname, &size);
	studentPtrArr = createStudentPtrArr(studentArr, size);
	
	mergeSortStudentPtrArr(studentPtrArr, size);
	SaveStudentsToFile(fname, studentPtrArr, size);
	createIndexFileForStudentsFile(fname);

	nameArr = findAverageGrade(fname, 99, &nameArrSize);

	printNames(nameArr, nameArrSize);
}
char    **findAverageGrade(char *database, int avgGrade, int *resSize) 
{
	char **res;
	FILE *fp, *findex;
	int numStudents;

	fp = safeFileOpen(database, "rb");
	findex = safeFileOpen(addIndExtension(database), "rb");

	numStudents = freadShort(fp);
	res = binarySearchStudentsByGrade(fp, findex, avgGrade, numStudents, resSize);

	return res;
}
void      createIndexFileForStudentsFile(char *fname)
{
	FILE *fstud, *findex;
	char *filename;
	int i;
	short numOfStudents;

	filename = addIndExtension(fname);
	findex = safeFileOpen(filename, "wb");
	fstud = safeFileOpen(fname, "rb");
	numOfStudents = freadShort(fstud);
	for (i = 0; i < numOfStudents; i++)
	{
		fwriteLong(findex, ftell(fstud));
		fseekStudent(fstud);
	}
	fclose(findex);
	fclose(fstud);
}
STUDENT*  LoadStudentsFromFile(char *fname, int *outArrSize) 
{
	STUDENT *res;
	int i, size;
	FILE *fp;

	fp = safeFileOpen(fname, "rb");
	size = freadShort(fp);
	res = freadnStudents(fp, size);
	fclose(fp);

	*outArrSize = size;
	return res;
} 
void      SaveStudentsToFile(char *fname, STUDENT **ptrArr, int size)
{
	FILE *fp;
	int i;
	fp = safeFileOpen(fname, "wb");
	fwriteShort(fp, size);
	for (i = 0; i < size; i++)
		fwriteStudent(fp, *(ptrArr[i]));
	fclose(fp);
}
STUDENT** createStudentPtrArr(STUDENT *studentArr, int size) 
{
	STUDENT **res;
	res = allocStudentPtrArr(size);
	initStudentPtrArr(res, studentArr, size);
	return res;
}
void      initStudentPtrArr(STUDENT **ptrArr, STUDENT *arr, int size) 
{
	int i;
	for (i = 0; i < size; i++)
		ptrArr[i] = &(arr[i]);
}
STUDENT** allocStudentPtrArr(int size) 
{
	STUDENT **res;
	res = safeMalloc(sizeof(STUDENT *), size);
	return res;
}
void      fwriteStudent(FILE *fp, STUDENT x)
{
	fwriteShort(fp, (short)strlen(x.name));
	fwriteStr(fp, x.name);
	fwriteInt(fp, x.average);
}
STUDENT*  freadnStudents(FILE *fp, int n)
{
	STUDENT *res;
	int i;

	res = safeMalloc(sizeof(STUDENT), n);
	for (i = 0; i < n; i++)
		res[i] = freadStudent(fp);

	return res;
}
STUDENT   freadStudent(FILE *fp) 
{
	STUDENT res;
	res.name = freadStr2(fp);
	res.average = freadInt(fp);
	return res;
}
void      fseekStudent(FILE *fp) 
{
	short nameLen;
	nameLen = freadShort(fp);
	fseek(fp, nameLen, SEEK_CUR);
	fseek(fp, sizeof(int), SEEK_CUR);
}
void      mergeSortStudentPtrArr(STUDENT **ptrArr, unsigned int size)
{
	STUDENT **temp;
	unsigned int i;

	if (size < 2)
		return;
	else
	{
		mergeSortStudentPtrArr(ptrArr, size / 2);
		mergeSortStudentPtrArr(ptrArr + (size / 2), size - (size / 2));
		temp = (STUDENT **)safeMalloc(sizeof(STUDENT *), size);
		merge2(ptrArr, size / 2, ptrArr + (size / 2), size - (size / 2), temp);
		for (i = 0; i < size; i++)
			ptrArr[i] = temp[i];
		free(temp);
	}
}
void      merge2(STUDENT **ptrArrL, unsigned int sizeL, STUDENT **ptrArrR, unsigned int sizeR, STUDENT **temp)
{
	unsigned int i, j, k;
	i = j = k = 0;

	while ((i < sizeL) && (j < sizeR))
	{
		if ((ptrArrL[i]->average) < (ptrArrR[j]->average))
		{
			temp[k] = ptrArrL[i];
			i++;
		}
		else
		{
			temp[k] = ptrArrR[j];
			j++;
		}
		k++;
	}

	while (i < sizeL)
	{
		temp[k] = ptrArrL[i];
		i++;
		k++;
	}

	while (j < sizeR)
	{
		temp[k] = ptrArrR[j];
		j++;
		k++;
	}
}
void      printNames(char **records, int size) {
	int i;
	printf("The students names are:\n");
	for (i = 0; i < size; i++) {
		printf("%s\n", records[i]);
	}
}
void      printStudent(STUDENT x)
{
	printf("%s , %d\n", x.name, x.average);
}
void      printStudentArr(STUDENT *arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
		printStudent(arr[i]);
}
void      printStudentArr2(STUDENT **ptrArr, int size) 
{
	int i;
	for (i = 0; i < size; i++)
		printStudent(*(ptrArr[i]));
}
void	  printStudentByIndex(char *fname, int index) 
{
	STUDENT res;
	FILE *fp, *findex;
	char *findexName;

	fp = safeFileOpen(fname, "rb");
	findex = safeFileOpen(addIndExtension(fname), "rb");
	fseek(findex, index * sizeof(long), SEEK_SET);
	fseek(fp, freadLong(findex), SEEK_SET);
	res = freadStudent(fp);
	printStudent(res);
}
STUDENT   studentAtIndex(FILE* studentsFile, FILE* studentsIndFile, int index) 
{
	STUDENT res;
	fseek(studentsIndFile, index * sizeof(long), SEEK_SET);
	fseek(studentsFile, freadLong(studentsIndFile), SEEK_SET);
	res = freadStudent(studentsFile);
	return res;
}
char**    binarySearchStudentsByGrade(FILE *studentsFile, FILE *indexFile, int targetGrade, int size, int *outSize) 
{
	char **res = NULL;
	int left, mid, right;
	int write = 0;

	if (size == 0) 
	{
		*outSize = 0;
		return NULL;
	}

	if (size == 1)
	{
		if (studentAtIndex(studentsFile, indexFile, 1).average == targetGrade) 
		{
			res = safeMalloc(sizeof(char *), 1);
			*outSize = 1;
			return res;
		}
		else 
		{
			*outSize = 0;
			return NULL;
		}
	}

	left = 0;
	right = size - 1;
	
	while (left <= right) 
	{
		mid = (left + right) / 2;

		if (studentAtIndex(studentsFile, indexFile, mid).average != targetGrade &&
			studentAtIndex(studentsFile, indexFile, mid + 1).average == targetGrade)
		{
			while (mid + 1 != size && studentAtIndex(studentsFile, indexFile, mid + 1).average == targetGrade)
			{
				res = safeRealloc(res, sizeof(char *), write + 1);
				res[write] = _strdup(studentAtIndex(studentsFile, indexFile, mid + 1).name);
				write++;
				mid++;
			}
			*outSize = write;
			return res;
		}
		else if (studentAtIndex(studentsFile, indexFile, mid).average == targetGrade && mid == 0)
		{
			while (mid != size && studentAtIndex(studentsFile, indexFile, mid).average == targetGrade)
			{
				res = safeRealloc(res, sizeof(char *), write + 1);
				res[write] = _strdup(studentAtIndex(studentsFile, indexFile, mid).name);
				write++;
				mid++;
			}
			*outSize = write;
			return res;
		}
		else if (studentAtIndex(studentsFile, indexFile, mid + 1).average < targetGrade)
			left = mid + 1;
		else
			right = mid - 1;
	}

	*outSize = 0;
	return NULL;
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "file.h"
#include "util.h"
#include "ex5q2.h"

void Exe5Q2(char *fname1, char *fname2)
{
	Employee *employeeArr;
	int employeeArrSize;
	float *raiseArr;
	int raiseArrSize;
	int i;
	Employee **ptrArr;

	employeeArr = LoadEmployeesFromFile(fname1, &employeeArrSize);
	raiseArr = LoadFloatsFromFile(fname2, &raiseArrSize);

	addRaiseToEmployees(employeeArr, raiseArr, employeeArrSize);
	
	ptrArr = safeMalloc(sizeof(Employee *), employeeArrSize);
	for (i = 0; i < employeeArrSize; i++)
		ptrArr[i] = &(employeeArr[i]);
	mergeSort(ptrArr, employeeArrSize);

	SaveEmployeesToFile(fname1, ptrArr, employeeArrSize);
}

Employee* LoadEmployeesFromFile(char *fname, int *outArrSize)
{
	Employee *res;
	int logSize = 0, phySize = 1;
	int i;
	FILE *fp;

	fp = safeFileOpen(fname, "rb");
	res = (Employee *)safeMalloc(sizeof(Employee), phySize);
	
	for (i = 0; !isEndOfFile(fp); i++) 
	{
		if (logSize == phySize) 
			res = safeRealloc(res, sizeof(Employee), phySize *= 2);

		res[i] = freadEmployee(fp);
		logSize++;
	}

	fclose(fp);

	res = safeRealloc(res, sizeof(Employee), logSize);
	*outArrSize = logSize;
	return res;
}
float*    LoadFloatsFromFile(char *fname, int *outArrSize) 
{
	float *res;
	int logSize = 0, phySize = 1;
	int i;
	FILE *fp;

	fp = safeFileOpen(fname, "rb");
	res = (float *)safeMalloc(sizeof(float), phySize);

	for (i = 0; !isEndOfFile(fp); i++)
	{
		if (logSize == phySize)
			res = safeRealloc(res, sizeof(float), phySize *= 2);

		res[i] = freadFloat(fp);
		logSize++;
	}

	fclose(fp);

	res = safeRealloc(res, sizeof(float), logSize);
	*outArrSize = logSize;
	return res;
}
void      SaveEmployeesToFile(char *fname, Employee **ptrArr, int size) 
{
	FILE *fp;
	int i;
	fp = safeFileOpen(fname, "wb");
	for (i = 0; i < size; i++)
		fwriteEmployee(fp, *(ptrArr[i]));
	fclose(fp);
}
void      addRaiseToEmployees(Employee *employeeArr, float *raiseArr, int size) 
{
	int i;
	for (i = 0; i < size; i++)
		employeeArr[i].salary += raiseArr[i];
}
Employee  freadEmployee(FILE *fp)
{
	Employee res;
	res.name_length = freadInt(fp);
	fseek(fp, -1 * (int)(sizeof(int)), SEEK_CUR);
	res.name = freadStr(fp);
	res.salary = freadFloat(fp);
	return res;
}
void	  fwriteEmployee(FILE *fp, Employee x) 
{
	fflush(fp);
	fwriteInt(fp, x.name_length);
	fwriteStr(fp, x.name);
	fwriteFloat(fp, x.salary);
}
void      printEmployee(Employee x)
{
	printf("%d , %s , %f\n", x.name_length, x.name, x.salary);
}
void      printEmployeeArr(Employee *arr, int size) 
{
	int i;
	for (i = 0; i < size; i++)
		printEmployee(arr[i]);
}
void      mergeSort(Employee **ptrArr, unsigned int size)
{
	Employee **temp;
	unsigned int i;
	
	if (size < 2)
		return;
	else
	{
		mergeSort(ptrArr, size / 2);
		mergeSort(ptrArr + (size / 2), size - (size / 2));
		temp = (Employee **)safeMalloc(sizeof(Employee *), size);
		merge(ptrArr, size / 2, ptrArr + (size / 2), size - (size / 2), temp);
		for (i = 0; i < size; i++)
			ptrArr[i] = temp[i];
		free(temp);
	}
}
void      merge(Employee **ptrArrL, unsigned int sizeL, Employee **ptrArrR, unsigned int sizeR, Employee **temp)
{
	unsigned int i, j, k;
	i = j = k = 0;

	while ((i < sizeL) && (j < sizeR))
	{
		if ((ptrArrL[i]->salary) > (ptrArrR[j]->salary)) 
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
		temp[k] = ptrArrL[j];
		j++;
		k++;
	}
}
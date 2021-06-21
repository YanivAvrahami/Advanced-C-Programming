#ifndef ___EX5Q3_H___
#define ___EX5Q3_H___

typedef struct student {
	char *name;
	int average;
}STUDENT;

// exercise 1 function
void      Exe5Q3(char *fname);
// creating an index file for a students file
void      createIndexFileForStudentsFile(char *fname);
// loading all students from a file to an students arr
STUDENT*  LoadStudentsFromFile(char *fname, int *outArrSize);
// saving all students from student ptr arr to a file
void      SaveStudentsToFile(char *fname, STUDENT **ptrArr, int size);
// creating a student ptr arr
STUDENT** createStudentPtrArr(STUDENT *studentArr, int size);
// initializing a student ptr arr to linearly point to a student arr 
void      initStudentPtrArr(STUDENT **ptrArr, STUDENT *arr, int size);
// allocating memory for a student ptr arr
STUDENT** allocStudentPtrArr(int size);
// writing student to file
void      fwriteStudent(FILE *fp, STUDENT x);
// reading a given number of students from file
STUDENT*  freadnStudents(FILE *fp, int n);
// reading a student from file
STUDENT   freadStudent(FILE *fp);
// seeking a student in file
void      fseekStudent(FILE *fp);
// sorting a student ptr arr by lowest to highest grade using merge sort algorithem
void      mergeSortStudentPtrArr(STUDENT **ptrArr, unsigned int size);
// used in mergeSort to sorting a student ptr arr by lowest to highest grade using merge sort algorithem
void      merge2(STUDENT **ptrArrL, unsigned int sizeL, STUDENT **ptrArrR, unsigned int sizeR, STUDENT **temp);
// printing names of a given str arr
void      printNames(char **records, int size);
// printing a student
void      printStudent(STUDENT x);
// printing a student arr
void      printStudentArr(STUDENT *arr, int size);
// printing a student ptr arr
void      printStudentArr2(STUDENT **ptrArr, int size);
// printing a student by their index in the index file
void	  printStudentByIndex(char *fname, int index);
// gives a str arr of the names of the students with the requested avgGrade
char    **findAverageGrade(char *database, int avgGrade, int *resSize);
// gives a str arr of the names of the students with the requested avgGrade using binary search
char    **binarySearchStudentsByGrade(FILE *studentsFile, FILE *indexFile, int targetGrade, int size, int *outSize);

#endif
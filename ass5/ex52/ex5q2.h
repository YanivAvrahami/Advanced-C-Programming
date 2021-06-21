#ifndef ___EX5Q2_H___
#define ___EX5Q2_H___

typedef struct employee
{
	int name_length;
	char *name;
	float salary;
} Employee;

// exercise 1 function
void      Exe5Q2(char *fname1, char *fname2);
// reading employee from file
Employee  freadEmployee(FILE *fp);
// writing employee to file
void      fwriteEmployee(FILE *fp, Employee x);
// loading employees from file into an employee arr
Employee* LoadEmployeesFromFile(char *fname, int *outArrSize);
// saving an employee arr to file
void      SaveEmployeesToFile(char *fname, Employee **ptrArr, int size);
// loading floats from file into an float arr
float*    LoadFloatsFromFile(char *fname, int *outArrSize);
// printing employee
void      printEmployee(Employee x);
// printing employee arr
void      printEmployeeArr(Employee *arr, int size);
// adding raise to each employee in employee arr
void      addRaiseToEmployees(Employee *employeeArr, float *raiseArr, int size);
// sorting an employees ptr arr by highest salary to lowest salary using merge sort algorithem
void      mergeSort(Employee **ptrArr, unsigned int size);
// used in mergeSort to sorting an employees ptr arr by highest salary to lowest salary using merge sort algorithem
void      merge(Employee **ptrArrL, unsigned int sizeL, Employee **ptrArrR, unsigned int sizeR, Employee **temp);

#endif
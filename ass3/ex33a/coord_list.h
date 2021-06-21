#ifndef ___COORD_LIST_H___
#define ___COORD_LIST_H___

#include "list.h"

/*
	The user will enter the number of points followed by the points.
    The pointes will be entered in a sorted fashion.
    i.e. first by the x value and then by y.
    for example (5 points): 5 1 2 1 5 2 7 3 3 3 8
    are: (1,2),(1,5),(2,7),(3,3),(3,8)
*/
List getCoordList();

/*
    This function checks if an x value exists in the list.
*/

bool isXExist(int x, List *list);



/*
   Counts the amount of times that (x,y) appear in list.
*/
unsigned int getPairOccurrences(List coord_list, int x, int y);

/*
   Counts the amount of times that a given y value appears in list.
*/
unsigned int occurrencesInSortedYList(YList *ylist, int y_to_count);

/*
   Counts the amount of times that (*,y) appear in list.
*/
unsigned int getYOccurrences(List coord_list, int y);

/*
   Counts the amount of times that (x,*) appear in list.
*/
unsigned int getXOccurrences(List coord_list, int x);

unsigned int lengthOfYList(YList *list);

/*
   inserts (x,y) in list. 
   if (x,y) already appear in list, then returns 1.
   else return 0.
   Anyway, the function will insert (x,y) in list.
*/
int insertCoordinate(List *coord_list, int x, int y);

XListNode *findNodeInXList(List *list, int node_x_value);

XListNode *findPlaceToInsertInXList(List *list, int x_value);

/*
    removes (x,y) from list.
    if (x,y) appears MORE THEN 1 time in list then remove only one
    of the occurences.
    if list has only one point with the x specified then 
    remove corresponding cell.

    returns 1 if point was'nt found.
    returns 2 if multiple occurences were found.
    returns 3 if the point was the only point with such x value.
    else returns 0.
*/
int removeCoordinate(List *coord_list, int x, int y);

/*
This function prints a coordList.
*/
void printCoordList(List *list);

/*
This function prints a single coord gets a ylist and prints its elements from head to tail.
*/
void printSingleColumnInCoordList(List *list, int x_value);

/*
This function gets an XListNode and prints its (x,y) coords.
*/
void printColumnInCoordList(XListNode *node);

#endif

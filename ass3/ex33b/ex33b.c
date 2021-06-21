#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "coord_list.h"

void main()
{
    List coordList;
    int y;
    unsigned int res;

    coordList = getCoordList();

    // get the (*,y) to look for
    scanf("%d", &y);

    res = getYOccurrences(coordList, y);

    printf("The point (*,%d) appears %u times\n", y, res);

    freeList(&coordList);
}
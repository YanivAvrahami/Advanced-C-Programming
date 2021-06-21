#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "coord_list.h"

void main()
{
    List coordList;
    int x, y;
    unsigned int res;

    coordList = getCoordList();

    // get the (x,y) to look for
    scanf("%d%d", &x, &y);

    res = getPairOccurrences(coordList, x, y);

    printf("The point (%d,%d) appears %u times\n", x, y, res);

    freeList(&coordList);
}
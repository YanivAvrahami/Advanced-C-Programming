#define _CRT_SECURE_NO_WARNINGs
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "coord_list.h"

void main()
{
    List coordList;
    int x;
    unsigned int res;

    coordList = getCoordList();

    // get the (x,*) to look for
    scanf("%d", &x);

    res = getXOccurrences(coordList, x);

    printf("The point (%d,*) appears %u times\n", x, res);

    freeList(&coordList);
}
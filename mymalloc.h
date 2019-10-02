#include <stdio.h>
#include <stdlib.h>

#define malloc(x) myMalloc(x)
#define free(x) myFree(x)
#define true 1
//need a library file that uses the header file for functions.

static char myblock[4096];
int* integers = (integers*) myblock; // used to store integers by bytes along with char

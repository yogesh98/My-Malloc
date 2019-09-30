#include <stdio.h>
#include <stdlib.h>

#define malloc(x) myMalloc(x)
#define free(x) myFree(x)
#define true 1


static char myblock[4096];

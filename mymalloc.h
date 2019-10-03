#include <stdio.h>
#include <stdlib.h>

#define malloc(x) myMalloc(x, __FILE__,__LINE__)
#define free(x) myFree(x,__FILE_,__LINE__)
#define BLOCKSIZE 4096
#define INTSIZE 5
#define inUse 'y'
#define notInUse 'n'

//need a library file that uses the header file for functions.

static char myblock[BLOCKSIZE];
 // used to store integers by bytes along with char

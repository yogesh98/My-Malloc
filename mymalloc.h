//Aditya Patel ajp365,06
//Yogesh Patel ymp20,07
#ifndef mymalloc_h_
#define mymalloc_h_

#define malloc(x) myMalloc(x, __FILE__,__LINE__)
#define free(x) myFree(x,__FILE__,__LINE__)
#define BLOCKSIZE 4096
#define inUse 6
#define notInUse 21
typedef struct metadata {
  char ussage;
  short size;
}metadata;

void* myMalloc(size_t inputSize, char* file , int line);
int myFree(void* ptr,char * file, int line);

static char myblock[BLOCKSIZE];
 // used to store integers by bytes along with char
#endif

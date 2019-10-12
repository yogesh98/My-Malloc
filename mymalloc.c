#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

void* myMalloc(size_t inputSize, char* file , int line){
  short requestedSize = (short) inputSize;
  //Check for uninitialized array
  if(myblock[0] == '\0'){
    metadata* temp = (metadata*) &myblock[0];
    temp->ussage = inUse;
    temp->size = requestedSize;
    metadata* next =(metadata*) &myblock[sizeof(*temp) + requestedSize];
    next->ussage = notInUse;
    next->size = BLOCKSIZE - requestedSize;
    return &myblock[4];
  }

  //loop through and look for smallest block that can fit data to minimize datablocks inbetween
  int i =0;
  metadata* blockPtr = (metadata*) &myblock[i];
  for(i = 0; i<BLOCKSIZE; i += blockPtr->size + sizeof(metadata)){
    //printf("%d" , i);
    blockPtr = (metadata*) &myblock[i];
    if(blockPtr->ussage == notInUse && blockPtr->size >= requestedSize){
      blockPtr->ussage = inUse;
      if(myblock[i + sizeof(metadata) + requestedSize] != inUse){
        metadata* next = (metadata*) &myblock[i + sizeof(metadata) + requestedSize];
        next->ussage = notInUse;
        int j;
        for(j = i + sizeof(metadata) + requestedSize; j<BLOCKSIZE; j++){
          if(myblock[i] == inUse){
            break;
          }
        }
        next->size = j - i;
      }
      blockPtr->size = requestedSize;
      int deleteLater = sizeof(blockPtr);
      return &myblock[i + sizeof(*blockPtr)];
    }
  }
  return NULL;
}



//0 for error 1 for success
int myFree(void* ptr,char * file, int line){
  metadata* blockPtr = ptr - sizeof(metadata);
  char* dataPtr = (char*) ptr;
  //printf("ussage: %c\nsize: %d\n", blockPtr->ussage, blockPtr->size);
  if(blockPtr->ussage != inUse){
    printf("Error: freeing non allocated memory %p from file: %s on line %d has made an error\n",ptr,file,line);
    return 0;
  }
  else{
    blockPtr->ussage = notInUse;
    //metadata* nextPtr = (metadata*) &blockPtr[sizeof(metadata) + blockPtr->size];
    char* i;
    for(i = (char*) blockPtr - 1; i >= &myblock[0]; i--){
      if(*i == inUse){
        break;
      }
      else if(*i == notInUse){
        short oldSize = blockPtr->size;
        blockPtr = (metadata*) i;
        blockPtr->size = blockPtr->size + oldSize + sizeof(metadata);
        int deleteLater = sizeof(metadata);
        dataPtr = (char*) blockPtr + sizeof(*blockPtr);
        break;
      }
    }
    metadata* nextPtr =(metadata*) (dataPtr + blockPtr->size);
    if(nextPtr->ussage == notInUse){
      blockPtr->size = blockPtr->size + nextPtr->size;
    }
    int j = 0;
    for(j = 0; j < blockPtr->size; j++){
      dataPtr[j] = '\0';
    }
    //printf("ussage: %c\nsize: %d\n", blockPtr->ussage, blockPtr->size);
    return 1;
  }
}
void tempPrintMem(int start, int end){
   int i = 0;
   for(i = start; i<end; i++){
     //myblock[i] = 0;
     printf("%d: %c\n" ,i, myblock[i]);
   }
 }

// int main (int argc, char ** argv){
//   char* a = (char*) malloc(1);
//   char* b = (char*) malloc(1);
//   char* c = (char*) malloc(1);
//   a[0] = 'a';
//   b[0] = 'b';
//   c[0] = 'c';
//   printf("a: %p\nb: %p\nc: %p\n", a, b, c);
//   printf("\n\n");
//   tempPrintMem(0, 15);
//   free(a);
//   printf("\n\n");
//   tempPrintMem(0, 15);
//   free(b);
//   printf("\n\n");
//   tempPrintMem(0, 15);
//   free(c);
//   printf("\n\n");
//   tempPrintMem(0, 15);
//
//   printf("\n\n\n\n\n");
//
//   a = (char*) malloc(1);
//   b = (char*) malloc(1);
//   c = (char*) malloc(1);
//   a[0] = 'a';
//   b[0] = 'b';
//   c[0] = 'c';
//   printf("a: %p\nb: %p\nc: %p\n", a, b, c);
//   printf("\n\n");
//   tempPrintMem(0, 15);
//   free(c);
//   printf("\n\n");
//   tempPrintMem(0, 15);
//   free(b);
//   printf("\n\n");
//   tempPrintMem(0, 15);
//   free(a);
//   printf("\n\n");
//   tempPrintMem(0, 15);
//
//   printf("\n\n\n\n\n");
//
//   a = (char*) malloc(1);
//   b = (char*) malloc(1);
//   c = (char*) malloc(1);
//   a[0] = 'a';
//   b[0] = 'b';
//   c[0] = 'c';
//   printf("a: %p\nb: %p\nc: %p\n", a, b, c);
//   printf("\n\n");
//   tempPrintMem(0, 15);
//   free(b);
//   printf("\n\n");
//   tempPrintMem(0, 15);
//   free(c);
//   printf("\n\n");
//   tempPrintMem(0, 15);
//   free(a);
//   printf("\n\n");
//   tempPrintMem(0, 15);
//
// }

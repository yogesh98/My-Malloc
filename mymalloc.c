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
    metadata* nextPtr = (metadata*) &blockPtr[sizeof(metadata) + blockPtr->size];
    if(nextPtr->ussage == notInUse){
      blockPtr->size = blockPtr->size + nextPtr->size;
      myFree(blockPtr + sizeof(metadata), __FILE__, __LINE__);
    }
    else{
      blockPtr->ussage = notInUse;
      int i = 0;
      for(i = 0; i < blockPtr->size; i++){
        dataPtr[i] = '\0';
      }
      //printf("ussage: %c\nsize: %d\n", blockPtr->ussage, blockPtr->size);
      return 1;
    }
  }
}
void tempPrintMem(){
   int i = 0;
   for(i = 0; i<42; i++){
     //myblock[i] = 0;
     printf("%d: %c\n" ,i, myblock[i]);
   }
 }

// int main (int argc, char ** argv){
//   char* x = (char*)malloc(sizeof(char) *10);
//   int i = 0;
//   for(i = 0; i < 10; i++){
//     x[i] = 'A';
//     //printf("%c\n", x[i]);
//   }
//
//   printf("\n");
//   char* y = (char*)malloc(sizeof(char)* 10);
//   for(i = 0; i < 10; i++){
//     y[i] = 'B';
//     //printf("%c\n", y[i]);
//   }
//
//   printf("\n");
//   char* z = (char*)malloc(sizeof(char) *10);
//   for(i = 0; i < 10; i++){
//     z[i] = 'C';
//     //printf("%c\n", x[i]);
//   }
//   tempPrintMem();
//   printf("\n");
//
//   free(x);
//   free(x);
//   tempPrintMem();
// }

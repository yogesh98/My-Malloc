#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"



//TODO:
//myMalloc initilization works (Works when uninitialized) TEST and debug for intialized
//myFree needs to be implemented!

//need my free
//need my myMalloc


void* myMalloc(size_t inputSize) {
//=======
//ERROR REPORTING:
//printf("Error on Line %d, in file %s\n", line, file);

//Manages space of size chops of null terminator to save 1 byte
char* itoa(char* buffer, int integer){
  char temp[5];
  snprintf(temp, INTSIZE, "%d", integer);
  int i = 0;
  for(i = 0; i < 4; i++){
    buffer[i] = temp[i];
  }
}

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
    printf("Error: freeing non allocated memory %p from file: %s on line %d has made an error",ptr,file,line);
    return 0;
  }
  else{
    metadata* nextPtr = (metadata*) &blockPtr[sizeof(metadata) + blockPtr->size];
    if(nextPtr->ussage == notInUse){
      blockPtr->size = blockPtr->size + nextPtr->size;
      myFree(blockPtr + sizeof(metadata));
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
  //if user tried to free alredy freed memory
  if (!blockPtr->ussage == inUse){
    printf("Error: freeing alredy free %p from file: %s on line %d has made an error",ptr,file,line);
    return 0;
  }

}
}

int main (int argc, char ** argv){
  char* x = (char*)myMalloc(sizeof(char) *10 ,__FILE__,__LINE__);
  int i = 0;
  for(i = 0; i < 10; i++){
    x[i] = 'A';
    //printf("%c\n", x[i]);
  }

  printf("\n");
  char* y = (char*)myMalloc(sizeof(char)* 10 ,__FILE__,__LINE__);
  for(i = 0; i < 10; i++){
    y[i] = 'B';
    //printf("%c\n", y[i]);
  }

  printf("\n");
  char* z = (char*)myMalloc(sizeof(char) *10 ,__FILE__,__LINE__);
  for(i = 0; i < 10; i++){
    z[i] = 'C';
    //printf("%c\n", x[i]);
  }
  tempPrintMem();
  printf("\n");

  myFree(x);
  tempPrintMem();
}
/*void myFree (void *freeptr, char * file, int line){
  void* freemem = (char* (freeptr)) - INTSIZE;
  char previous = 0;
  char next = 0;

  freemem = NULL;
  //if trying to free non allocated memory
  if ((char*)freemem < myblock || (char*)freemem >= myblock + sizeof(myblock)) {
    printf("Error: pointer to free %p from file : %s on line %d has made an error\n",freeptr, file,line);
  }
  //if user tried to free alredy freed memory
  if (notInUse){
    printf("Error: freeing alredy free %p from file: %s on line %d has made an error",freeptr,file,line);

  }
}*/

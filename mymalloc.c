#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"



//TODO:
//myMalloc initilization works (Works when uninitialized) TEST and debug for intialized
//myFree needs to be implemented!

//need my free
//need my myMalloc
//ERROR REPORTING:
//printf("Error on Line %d, in file %s\n", line, file);

//Manages space of size chops of null terminator to save 1 byte
char* itoa(char* buffer, int integer){
  char temp[5];
  snprintf(temp, 5, "%d", integer);
  int i = 0;
  for(i = 0; i < 4; i++){
    buffer[i] = temp[i];
  }
}

void* myMalloc(size_t inputSize, char* file , int line){

  int requestedSize = (int) inputSize;

  //Check for uninitialized array
  if(myblock[0] == '\0'){
    myblock[0] = inUse;
    //myblock[1] = snprintf(&myblock[1], 4,requestedSize);
    snprintf(&myblock[1], 5, "%d",requestedSize);
    //itoa(&myblock[1], requestedSize);
    myblock[INTSIZE+ requestedSize + 1] = notInUse;
    myblock[INTSIZE + requestedSize + 2] = BLOCKSIZE - requestedSize;
    return &myblock[5];
  }

  int i =0;
  for(i =0; i<BLOCKSIZE; i++){
    if(myblock[i] == inUse){
      i = i + atoi(&myblock[i+1]);
    }
    if(myblock[i] == notInUse && myblock[i+1] >= requestedSize){
      myblock[i] = inUse;
      //myblock[i+5+requestedSize + 1] = snprintf(&myblock[i+5+requestedSize + 1],4, atoi(&myblock[i+1]) - requestedSize );
      snprintf(&myblock[i+INTSIZE+requestedSize + 2],5, "%d", atoi(&myblock[i+1]) - requestedSize );
      //itoa(&myblock[i+INTSIZE+requestedSize + 2], atoi(&myblock[i+1]) - requestedSize );

      //myblock[i+1] = itoa(requestedSize);
      snprintf(&myblock[i + 1],5, "%d", requestedSize );
      //itoa(&myblock[i + 1], requestedSize);
      myblock[i+ INTSIZE + requestedSize + 1] = notInUse;
      return &myblock[i+ INTSIZE + 1];
    }
  }
}
int main (int argc, char ** argv){
  int* x = (int*)myMalloc(sizeof(int)* 100 ,__FILE__,__LINE__);
  int i = 0;
  for(i = 0; i < 100; i++){
    x[i] = i;
    printf("%d\n", x[i]);
  }
  printf("\n\n\n\n\n\n\n\n\n\n");
  int* y = (int*)myMalloc(sizeof(int)* 100 ,__FILE__,__LINE__);
  for(i = 0; i < 100; i++){
    y[i] = i;
    printf("%d", y[i]);
  }
}

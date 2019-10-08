#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

//need my free
//need my myMalloc
void free (void *freeptr){
  ((char*) freeptr -sizeof(struct metaDeta))->inuse  
}
void* myMalloc(size_t inputSize){

  int requestedSize = (int) inputSize;

  //Check for uninitialized array
  if(myblock[0] == '\0'){
    myblock[0] = inUse;
    //myblock[1] = snprintf(&myblock[1], 4,requestedSize);
    snprintf(&myblock[1], 4,requestedSize);
    myblock[5+requestedSize] = notInUse;
    myblock[5+requestedSize + 1] = BLOCKSIZE - requestedSize;
    return &myblock[5];
  }

  int i =0;
  for(i =0; i<BLOCKSIZE; i++){
    if(myblock[i] == inUse){
      i = i + myblock[i+1];
    }
    if(myblock[i] == notInUse && myblock[i+1] >= requestedSize){
      myblock[i] = inUse;
      //myblock[i+5+requestedSize + 1] = snprintf(&myblock[i+5+requestedSize + 1],4, atoi(&myblock[i+1]) - requestedSize );
      snprintf(&myblock[i+5+requestedSize + 1],4, atoi(&myblock[i+1]) - requestedSize );
      myblock[i+1] = itoa(requestedSize);
      myblock[i+5+requestedSize] = notInUse;
      return &myblock[i+5];
    }
  }
}
int main (int argc, char ** argv){
  int * x = (int*)myMalloc(sizeof(int)* 100);
}

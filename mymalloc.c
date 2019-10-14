#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

void* myMalloc(size_t inputSize, char* file , int line){
  short requestedSize = (short) inputSize;

  if(requestedSize < 0){
    return NULL;
  }
  //Check for uninitialized array
  if(myblock[0] == '\0'){
    metadata* temp = (metadata*) &myblock[0];
    temp->ussage = notInUse;
    temp->size = BLOCKSIZE - sizeof(metadata);
  }


  //loop through and look for smallest block that can fit data to minimize datablocks inbetween
  int i =0;
  metadata* blockPtr = (metadata*) &myblock[i];
  int smallestPtrIndex;
  metadata* smallestPtr = NULL;
  for(i = 0; i<BLOCKSIZE; i += blockPtr->size + sizeof(metadata)){
    //printf("%d" , i);
    blockPtr = (metadata*) &myblock[i];
    if(blockPtr->ussage == notInUse && blockPtr->size >= requestedSize){
      if(smallestPtr == NULL){
        smallestPtr = blockPtr;
        smallestPtrIndex = i;
      }
      else{
        if(smallestPtr->size > blockPtr->size){
          smallestPtr = blockPtr;
          smallestPtrIndex = i;
        }
      }
    }
  }

  if(smallestPtr == NULL){
    return NULL;
  }
  blockPtr = smallestPtr;
  blockPtr->ussage = inUse;

  if(blockPtr->size - requestedSize > 4){
    metadata* nextPtr = (metadata*) &myblock[smallestPtrIndex + requestedSize + sizeof(metadata)];
    nextPtr->ussage = notInUse;
    nextPtr->size = blockPtr->size - requestedSize - sizeof(metadata);
    blockPtr->size = requestedSize;
  }
  return &myblock[smallestPtrIndex + sizeof(*blockPtr)];
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


    metadata* prevPtr = NULL;
    if(blockPtr != (metadata*) &myblock[0]){
      int i;
      for(i = 0; i<BLOCKSIZE; i += prevPtr->size + sizeof(metadata)){
        prevPtr = (metadata*) &myblock[i];
        char* nextPtr = (char*) prevPtr + prevPtr->size + sizeof(metadata);
        if((metadata*) nextPtr == blockPtr){
          break;
        }
      }
    }


    metadata* nextPtr =(metadata*) (dataPtr + blockPtr->size);
    if(nextPtr != NULL && nextPtr->ussage == notInUse){
      blockPtr->size = blockPtr->size + nextPtr->size + sizeof(metadata);
    }
    if(prevPtr != NULL && prevPtr->ussage == notInUse){
      prevPtr->size = blockPtr->size + prevPtr->size + sizeof(metadata);
      blockPtr = prevPtr;
      dataPtr = (char*) prevPtr + sizeof(metadata);
    }
    int j = 0;
    for(j = 0; j < blockPtr->size; j++){
      dataPtr[j] = '\0';
    }
    //printf("ussage: %c\nsize: %d\n", blockPtr->ussage, blockPtr->size);
    return 1;
  }
}


// //0 for error 1 for success
// int myFree(void* ptr,char * file, int line){
//   metadata* blockPtr = ptr - sizeof(metadata);
//   char* dataPtr = (char*) ptr;
//   //printf("ussage: %c\nsize: %d\n", blockPtr->ussage, blockPtr->size);
//   if(blockPtr->ussage != inUse){
//     printf("Error: freeing non allocated memory %p from file: %s on line %d has made an error\n",ptr,file,line);
//     return 0;
//   }
//   else{
//     blockPtr->ussage = notInUse;
//     //metadata* nextPtr = (metadata*) &blockPtr[sizeof(metadata) + blockPtr->size];
//     char* i;
//     for(i = (char*) blockPtr - 1; i >= &myblock[0]; i--){
//       if(*i == inUse){
//         break;
//       }
//       else if(*i == notInUse){
//         short oldSize = blockPtr->size;
//         blockPtr = (metadata*) i;
//         blockPtr->size = blockPtr->size + oldSize + sizeof(metadata);
//         int deleteLater = sizeof(metadata);
//         dataPtr = (char*) blockPtr + sizeof(*blockPtr);
//         break;
//       }
//     }
//     metadata* nextPtr =(metadata*) (dataPtr + blockPtr->size);
//     if(nextPtr->ussage == notInUse){
//       blockPtr->size = blockPtr->size + nextPtr->size + sizeof(metadata);
//     }
//     int j = 0;
//     for(j = 0; j < blockPtr->size; j++){
//       dataPtr[j] = 'i';
//     }
//     //printf("ussage: %c\nsize: %d\n", blockPtr->ussage, blockPtr->size);
//     return 1;
//   }
// }
void printMem(int start, int end){
   // int i = 0;
   // for(i = start; i<end; i++){
   //   //myblock[i] = 0;
   //   printf("%d: %c\n" ,i, myblock[i]);
   // }
   metadata* blockPtr;
   int i;
   for(i = 0; i<BLOCKSIZE; i += blockPtr->size + sizeof(metadata)){
     blockPtr = (metadata*) &myblock[i];
     char ussage;
     if(blockPtr->ussage == inUse){
       ussage = 'y';
     }
     if(blockPtr->ussage == notInUse){
       ussage = 'n';
     }
     printf("%d -- U: %c , S: %d, Mem: " , i, ussage, blockPtr->size);
     int j;
     for(j = 0; j < blockPtr->size; j++){
       printf("%c " , myblock[i + sizeof(metadata) + j]);
     }
     printf("\n");
   }

 }

//Aditya Patel ajp365,06
//Yogesh Patel ymp20,07
#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

void* myMalloc(size_t inputSize, char* file , int line){
  short requestedSize = (short) inputSize;

  //Check to make sure requestedSize isnt under 1
  if(requestedSize < 1){
    return NULL;
  }
  //Check for uninitialized array
  if(myblock[0] == '\0'){
    metadata* temp = (metadata*) &myblock[0];
    temp->usage = notInUse;
    temp->size = BLOCKSIZE - sizeof(metadata);
  }


  //Traverse forward find the first block that can fit the data and put it in.
  int i =0;
  metadata* blockPtr = (metadata*) &myblock[i];
  for(i = 0; i<BLOCKSIZE; i += blockPtr->size + sizeof(metadata)){
    blockPtr = (metadata*) &myblock[i];
    //Checking if the block can accomodate requestedSize
    if(blockPtr->usage == notInUse && blockPtr->size >= requestedSize){
      blockPtr->usage = inUse;
      //if there isnt enough space to allow for metadata and 1 byte atleast it will
      //just return the whole block otherwise it will split it into 2. The block to give
      //and the block to set as notInUse for further use.
      if(blockPtr->size - requestedSize > sizeof(metadata)){
        metadata* nextPtr = (metadata*) &myblock[i + requestedSize + sizeof(metadata)];
        nextPtr->usage = notInUse;
        nextPtr->size = blockPtr->size - requestedSize - sizeof(metadata);
        blockPtr->size = requestedSize;
      }
      return &myblock[i + sizeof(*blockPtr)];
    }
  }
  //if nothing is found returns null
  printf("Error: All Dynamic Memory has been allocated: %s on line %d has made an error\n",ptr,file,line);
  return NULL;
}



//0 for error 1 for success
int myFree(void* ptr,char * file, int line){
  metadata* blockPtr = ptr - sizeof(metadata);
  char* dataPtr = (char*) ptr;
  //checks if it is a valid pointer to free
  if(blockPtr->usage != inUse){
    printf("Error: freeing non allocated memory %p from file: %s on line %d has made an error\n",ptr,file,line);
    return 0;
  }
  else{

    //set pointer to not in use
    blockPtr->usage = notInUse;

    //find prevPtr
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
    //find nextPtr
    metadata* nextPtr =(metadata*) (dataPtr + blockPtr->size);


    //if nextPtr isnt in use it will combine them into 1 block.
    if(nextPtr != NULL && nextPtr->usage == notInUse){
      blockPtr->size = blockPtr->size + nextPtr->size + sizeof(metadata);
    }
    //if nextPtr isnt in use it will combine them into 1 block.
    if(prevPtr != NULL && prevPtr->usage == notInUse){
      prevPtr->size = blockPtr->size + prevPtr->size + sizeof(metadata);
      blockPtr = prevPtr;
      dataPtr = (char*) prevPtr + sizeof(metadata);
    }

    //Erasing all memory in the dataportion of the block.
    int j = 0;
    for(j = 0; j < blockPtr->size; j++){
      dataPtr[j] = '\0';
    }
    return 1;
  }
}


// //0 for error 1 for success
// int myFree(void* ptr,char * file, int line){
//   metadata* blockPtr = ptr - sizeof(metadata);
//   char* dataPtr = (char*) ptr;
//   //printf("usage: %c\nsize: %d\n", blockPtr->usage, blockPtr->size);
//   if(blockPtr->usage != inUse){
//     printf("Error: freeing non allocated memory %p from file: %s on line %d has made an error\n",ptr,file,line);
//     return 0;
//   }
//   else{
//     blockPtr->usage = notInUse;
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
//     if(nextPtr->usage == notInUse){
//       blockPtr->size = blockPtr->size + nextPtr->size + sizeof(metadata);
//     }
//     int j = 0;
//     for(j = 0; j < blockPtr->size; j++){
//       dataPtr[j] = 'i';
//     }
//     //printf("usage: %c\nsize: %d\n", blockPtr->usage, blockPtr->size);
//     return 1;
//   }
// }


//Method to print memory for debugging purposes
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
     char usage;
     if(blockPtr->usage == inUse){
       usage = 'y';
     }
     if(blockPtr->usage == notInUse){
       usage = 'n';
     }
     printf("%d -- U: %c , S: %d, Mem: " , i, usage, blockPtr->size);
     int j;
     for(j = 0; j < blockPtr->size; j++){
       printf("%c " , myblock[i + sizeof(metadata) + j]);
     }
     printf("\n");
   }

 }

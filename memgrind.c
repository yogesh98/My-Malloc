#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "mymalloc.h"

void A();
void B();
void C();
void D();
void E();
void F();
void FWithSmallerChunks();
void reproduceError();


int main (int argc, char ** argv){



  int i = 0;
  int numTimesToRun = 100;
  int ATotalTime = 0;
  int BTotalTime = 0;
  int CTotalTime = 0;
  int DTotalTime = 0;
  int ETotalTime = 0;
  int FTotalTime = 0;
  int FWithSmallerChunksTotalTime = 0;
  struct timeval start;
  struct timeval end;



  for(i = 0; i<numTimesToRun; i++){
    gettimeofday(&start,NULL);
    A();
    gettimeofday(&end,NULL);
    ATotalTime += ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
  }
  for(i = 0; i<numTimesToRun; i++){
    gettimeofday(&start,NULL);
    B();
    gettimeofday(&end,NULL);
    BTotalTime += ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
  }
  for(i = 0; i<numTimesToRun; i++){
    gettimeofday(&start,NULL);
    C();
    gettimeofday(&end,NULL);
    CTotalTime += ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
  }
  for(i = 0; i<numTimesToRun; i++){
    gettimeofday(&start,NULL);
    D();
    gettimeofday(&end,NULL);
    DTotalTime += ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
  }
  for(i = 0; i<numTimesToRun; i++){
    gettimeofday(&start,NULL);
    E();
    gettimeofday(&end,NULL);
    ETotalTime += ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
  }
  for(i = 0; i<numTimesToRun; i++){
    gettimeofday(&start,NULL);
    F();
    gettimeofday(&end,NULL);
    FTotalTime += ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
  }
  // for(i = 0; i<numTimesToRun; i++){
  //   gettimeofday(&start,NULL);
  //   FWithSmallerChunks();
  //   gettimeofday(&end,NULL);
  //   FWithSmallerChunksTotalTime += ((end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
  // }


  printf("Average Workload Times in milliseconds:\n");
  printf("\tA: %f\n", (ATotalTime/100.0)/1000);
  printf("\tB: %f\n", (BTotalTime/100.0)/1000);
  printf("\tC: %f\n", (CTotalTime/100.0)/1000);
  printf("\tD: %f\n", (DTotalTime/100.0)/1000);
  printf("\tE: %f\n", (ETotalTime/100.0)/1000);
  printf("\tF: %f\n", (FTotalTime/100.0)/1000);
  //printf("\tF With Smaller Chunks: %f\n", (FWithSmallerChunksTotalTime/100.0)/1000);

}

void A(){
  int i;
  // A: malloc() 1 byte and immediately free it - do this 150 times
  for(i = 0; i<150; i++){
    char* temp = (char*) malloc(sizeof(char));
    free(temp);
  }
}
void B(){
  // B: malloc() 1 byte, store the pointer in an array - do this 150 times.
  // Once you've malloc()ed 50 byte chunks, then free() the 50 1 byte pointers one by one.
  int i;
  int j;
  for(i = 0; i<3; i++){
    char* temp[50];
    for(j = 0; j<50; j++){
      temp[j] = (char*) malloc(1);
    }
    for(j = 0; j<50; j++){
      if(free(temp[j]) == 0){
        //printf("%d\n" , j);
      }
    }
  }
}
void C(){
  // C: Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer > do this until you have allocated 50 times
  // - Keep track of each operation so that you eventually malloc() 50 bytes, in total
  // > if you have already allocated 50 times, disregard the random and just free() on each
  // iteration
  // - Keep track of each operation so that you eventually free() all pointers
  // > don't allow a free() if you have no pointers to free()
  srand(time(NULL));
  char* malloced[50];
  int nextMallocIndex = 0;
  int nextFreeIndex = 0;
  while(nextMallocIndex < 50){

    int chooser = rand() % 2;
    if(chooser == 0){
      malloced[nextMallocIndex] = (char*) malloc(1);
      nextMallocIndex++;
    }
    else if(chooser == 1){
      if(nextFreeIndex < nextMallocIndex){
        free(malloced[nextFreeIndex]);
        nextFreeIndex++;
      }
    }
  }
  int i;
  while(nextFreeIndex < 50){
    free(malloced[nextFreeIndex]);
    nextFreeIndex++;
  }
}
void D(){
  // D: Randomly choose between a randomly-sized malloc() or free()ing a pointer – do this many times (see below)
  // - Keep track of each malloc so that all mallocs do not exceed your total memory capacity - Keep track of each operation so that you eventually malloc() 50 times
  // - Keep track of each operation so that you eventually free() all pointers
  // - Choose a random allocation size between 1 and 64 bytes


  // FILE* toReproduceErrror = fopen("error", "w+");
  // FILE* randNumbers = fopen("errorNums", "w+");


  srand(time(NULL));
  char* malloced[50];
  int nextMallocIndex = 0;
  int nextFreeIndex = 0;
  int memUsed = sizeof(metadata);
  while(nextMallocIndex < 50){
    int chooser = rand() % 2;
    if(chooser == 0){
      int randRequest = rand() % (64 + 1 - 1) + 1;
      if(memUsed + randRequest + sizeof(metadata) <= BLOCKSIZE){
        memUsed += randRequest+sizeof(metadata);
        malloced[nextMallocIndex] = (char*) malloc(randRequest);


        // fprintf(randNumbers, "%d\n", randRequest);
        // fputs("Malloced\n", toReproduceErrror);
        // printf("Malloced: %d -- %d\n",nextMallocIndex, randRequest);
        // printMem();



        nextMallocIndex++;
      }
    }
    else if(chooser == 1){
      if(nextFreeIndex < nextMallocIndex){
        free(malloced[nextFreeIndex]);


        // fputs("Freed\n", toReproduceErrror);
        // printf("Feed: %d\n",nextFreeIndex);
        // printMem();




        nextFreeIndex++;
      }
    }
  }
  int i;
  while(nextFreeIndex < 50){
    free(malloced[nextFreeIndex]);


    // fputs("Freed\n", toReproduceErrror);
    // printf("Feed: %d\n",nextFreeIndex);
    // printMem();



    nextFreeIndex++;
  }
}
void E(){
  //Malloc to capacity then free in random order
  //in 64 byte chunks
  srand(time(NULL));
  char* malloced[4096];
  char* freedPointer;
  int nextMallocIndex = 0;
  int randRequest = 0;
  int memUsed = 0;
  while(memUsed < BLOCKSIZE){
    randRequest = rand() % (64 + 1 - 1) + 1;
    if(memUsed + randRequest + sizeof(metadata) > BLOCKSIZE ){
      randRequest = BLOCKSIZE - memUsed - sizeof(metadata);
    }
    malloced[nextMallocIndex] = (char*) malloc(randRequest);
    memUsed += randRequest+sizeof(metadata);
    nextMallocIndex++;
  }

  int indexToFree[nextMallocIndex];
  int i;
  for(i = 0; i < nextMallocIndex; i++){
    indexToFree[i] = i;
  }
  for(i = nextMallocIndex - 1; i >= 0; i--){
    int swap = rand() % (i+1);
    int temp = indexToFree[i];
    indexToFree[i] = indexToFree[swap];
    indexToFree[swap] = temp;
  }

  for(i = 0; i < nextMallocIndex; i++){
    free(malloced[indexToFree[i]]);
  }
}

void F(){
  //Malloc to Capacity and fill with random data (Since used ascii codes for inuse and notInUse)
  //Malloc to capacity then free in random order
  //chunks can be anysize from 1 to 4092
  srand(time(NULL));
  char* malloced[4096];
  char* freedPointer;
  int nextMallocIndex = 0;
  int randRequest = 0;
  int memUsed = 0;
  while(memUsed < BLOCKSIZE){
    randRequest = rand() % (4092 + 1 - 1) + 1;
    if(memUsed + randRequest + sizeof(metadata) > BLOCKSIZE ){
      randRequest = BLOCKSIZE - memUsed - sizeof(metadata);
    }
    malloced[nextMallocIndex] = (char*) malloc(randRequest);
    int i;
    for(i = 0; i < randRequest; i++){
      malloced[nextMallocIndex][i] = rand() % (255 + 1 - 0) + 0;
    }
    memUsed += randRequest+sizeof(metadata);
    nextMallocIndex++;
  }

  //printMem();

  int indexToFree[nextMallocIndex];
  int i;
  for(i = 0; i < nextMallocIndex; i++){
    indexToFree[i] = i;
  }
  for(i = nextMallocIndex - 1; i >= 0; i--){
    int swap = rand() % (i+1);
    int temp = indexToFree[i];
    indexToFree[i] = indexToFree[swap];
    indexToFree[swap] = temp;
  }

  for(i = 0; i < nextMallocIndex; i++){
    free(malloced[indexToFree[i]]);
  }
  //printMem();
}
void FWithSmallerChunks(){
  //Malloc to Capacity and fill with random data (Since used ascii codes for inuse and notInUse)
  //Malloc to capacity then free in random order
  //chunks can be anysize from 1 to 10
  srand(time(NULL));
  char* malloced[4096];
  char* freedPointer;
  int nextMallocIndex = 0;
  int randRequest = 0;
  int memUsed = 0;
  while(memUsed < BLOCKSIZE){
    randRequest = rand() % (10 + 1 - 1) + 1;
    if(memUsed + randRequest + sizeof(metadata) > BLOCKSIZE ){
      randRequest = BLOCKSIZE - memUsed - sizeof(metadata);
    }
    malloced[nextMallocIndex] = (char*) malloc(randRequest);
    int i;
    for(i = 0; i < randRequest; i++){
      malloced[nextMallocIndex][i] = rand() % (255 + 1 - 0) + 0;
    }
    memUsed += randRequest+sizeof(metadata);
    nextMallocIndex++;
  }

  //printMem();

  int indexToFree[nextMallocIndex];
  int i;
  for(i = 0; i < nextMallocIndex; i++){
    indexToFree[i] = i;
  }
  for(i = nextMallocIndex - 1; i >= 0; i--){
    int swap = rand() % (i+1);
    int temp = indexToFree[i];
    indexToFree[i] = indexToFree[swap];
    indexToFree[swap] = temp;
  }

  for(i = 0; i < nextMallocIndex; i++){
    free(malloced[indexToFree[i]]);
  }
  //printMem();
}

void reproduceError(){
  char *line = NULL;
  size_t len;
  char* malloced[50];
  int nextMallocIndex = 0;
  int nextFreeIndex = 0;
  int count = 0;
  FILE* file = fopen("error", "r");
  FILE* index = fopen("errorIndex", "w+");
  FILE* randNumbers = fopen("errorNums", "r");
  while(!feof(file)){
    getline(&line, &len, file);
    if(line[0] == 'M'){
      int num;
      fscanf(randNumbers, "%d", &num);
      malloced[nextMallocIndex] = (char*) malloc(num);
      printf("\nMalloced %d -- %d\n" , nextMallocIndex, num);
      printMem(0, 35);
      nextMallocIndex++;
    }
    else{
      if(nextFreeIndex != 50){
        if(free(malloced[nextFreeIndex]) == 0){
            fprintf(index, "%d\n", nextFreeIndex);
        }
        malloced[nextFreeIndex] = NULL;
        printf("\nFreed %d\n" , nextFreeIndex);
        printMem(0, 35);
        nextFreeIndex++;
      }
    }
    count++;
  }
}

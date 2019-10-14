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
int timeToRun(int numTimesToRun, void(*function)());


int main (int argc, char ** argv){

  srand(time(NULL));
  int i = 0;
  int numTimesToRun = 100;
  int ATotalTime = 0;
  int BTotalTime = 0;
  int CTotalTime = 0;
  int DTotalTime = 0;
  int ETotalTime = 0;
  int FTotalTime = 0;
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


  printf("Average Workload Times in milliseconds:\n");
  printf("\tA: %f\n", (ATotalTime/100.0)/1000);
  printf("\tB: %f\n", (BTotalTime/100.0)/1000);
  printf("\tC: %f\n", (CTotalTime/100.0)/1000);
  printf("\tD: %f\n", (DTotalTime/100.0)/1000);
  printf("\tE: %f\n", (FTotalTime/100.0)/1000);
  printf("\tF: %f\n", (ETotalTime/100.0)/1000);

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

  char* malloced[50];
  int nextMallocIndex = 0;
  int nextFreeIndex = 0;
  while(nextMallocIndex < 50){
    int chooser = rand() % 2;
    if(chooser == 0){
      int randRequest = rand() % (64 + 1 - 1) + 1;
      malloced[nextMallocIndex] = (char*) malloc(randRequest);
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
void E(){

}
void F(){

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
      printf("\nMalloced %d\n" , nextMallocIndex);
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

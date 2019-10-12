#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"

void A();
void B();
void C();
void D();
void E();
void F();
void breakpoint();


int main (int argc, char ** argv){

  // char* a = (char*) malloc(1);
  // char* b = (char*) malloc(1);
  // char* c = (char*) malloc(1);
  // a[0] = 'a';
  // b[0] = 'b';
  // c[0] = 'c';
  // printf("a: %p\nb: %p\nc: %p\n", a, b, c);
  // printf("\n\n");
  // tempPrintMem(0, 15);
  // free(a);
  // printf("\n\n");
  // tempPrintMem(0, 15);
  // free(b);
  // printf("\n\n");
  // tempPrintMem(0, 15);
  // free(c);
  // printf("\n\n");
  // tempPrintMem(0, 15);
  //
  // printf("\n\n\n\n\n");
  //
  // a = (char*) malloc(1);
  // b = (char*) malloc(1);
  // c = (char*) malloc(1);
  // a[0] = 'a';
  // b[0] = 'b';
  // c[0] = 'c';
  // printf("a: %p\nb: %p\nc: %p\n", a, b, c);
  // printf("\n\n");
  // tempPrintMem(0, 15);
  // free(c);
  // printf("\n\n");
  // tempPrintMem(0, 15);
  // free(b);
  // printf("\n\n");
  // tempPrintMem(0, 15);
  // free(a);
  // printf("\n\n");
  // tempPrintMem(0, 15);
  //
  // printf("\n\n\n\n\n");








  //
  // char* a = (char*) malloc(1);
  // a[0] = 'a';
  // printf("m a\n\n");
  // tempPrintMem(0, 35);
  //
  // char* b = (char*) malloc(1);
  // b[0] = 'b';
  // printf("m b\n\n");
  // tempPrintMem(0, 35);
  //
  // free(b);
  // printf("free b\n\n");
  // tempPrintMem(0, 35);
  //
  // char* c = (char*) malloc(1);
  // c[0] = 'c';
  // printf("m c\n\n");
  // tempPrintMem(0, 35);
  //
  // char* d = (char*) malloc(1);
  // d[0] = 'd';
  // printf("m d\n\n");
  // tempPrintMem(0, 35);
  //
  // char* e = (char*) malloc(1);
  // e[0] = 'e';
  // printf("m e\n\n");
  // tempPrintMem(0, 35);
  //
  // free(c);
  // printf("free c\n\n");
  // tempPrintMem(0, 35);
  //
  // char* f = (char*) malloc(1);
  // f[0] = 'f';
  // printf("m f\n\n");
  // tempPrintMem(0, 35);
  //
  // free(a);
  // printf("f a\n\n");
  // tempPrintMem(0, 35);
  //
  // char* g = (char*) malloc(1);
  // g[0] = 'g';
  // printf("m g\n\n");
  // tempPrintMem(0, 35);
  //
  // free(d);
  // printf("f e\n\n");
  // tempPrintMem(0, 35);
  // free(e);
  // printf("f f\n\n");
  // tempPrintMem(0, 35);
  // free(f);
  // printf("f g\n\n");
  // tempPrintMem(0, 35);
  // free(g);
  // printf("f d\n\n");
  // tempPrintMem(0, 35);



  int i = 0;
  // A();
  // B();
  // C();
  // D();
  E(fopen("error", "r"));
  // F();
  for(i = 0; i<100; i++){
    // A();
    // B();
    // C();
    // D();
    // E();
    // F();
  }
}

void A(){
  // A: malloc() 1 byte and immediately free it - do this 150 times
  int i;
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
      free(temp[j]);
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
  FILE* toReproduceErrror = fopen("error", "w+");
  char* malloced[50];
  int nextMallocIndex = 0;
  int nextFreeIndex = 0;
  while(nextMallocIndex < 50){
    int chooser = rand() % 2;
    if(chooser == 0){
      malloced[nextMallocIndex] = (char*) malloc(1);
      fputs("Malloced\n", toReproduceErrror);
      nextMallocIndex++;
    }
    else if(chooser == 1){
      if(nextFreeIndex < nextMallocIndex){
        free(malloced[nextFreeIndex]);
        fputs("Freed\n", toReproduceErrror);
        nextFreeIndex++;
      }
    }
  }
  int i;
  while(nextFreeIndex < 50){
    free(malloced[nextFreeIndex]);
    fputs("Freed\n", toReproduceErrror);
    nextFreeIndex++;
  }
}
void D(){
  // D: Randomly choose between a randomly-sized malloc() or free()ing a pointer – do this many times (see below)
  // - Keep track of each malloc so that all mallocs do not exceed your total memory capacity - Keep track of each operation so that you eventually malloc() 50 times
  // - Keep track of each operation so that you eventually free() all pointers
  // - Choose a random allocation size between 1 and 64 bytes
  int memoryUsed = 0;
int numAllocations = 0;
int indexFreed = 0;
char* malloced[50];

while(numAllocations < 50 && memoryUsed <=4096){
  //if 0 malloc, if 1 free
  int chooser = rand() % 2;

  if(chooser == 0){
    int randRequest = rand() % (64 + 1 - 1) + 1;
    malloced[numAllocations] = (char*) malloc(randRequest);
    memoryUsed += (4 + randRequest);
    ++numAllocations;
  }
  else if(chooser == 1){
    if(numAllocations < indexFreed){
      free(malloced[indexFreed]);
      ++indexFreed;
    }
  }
}
int i;
for(i = indexFreed; i<50; i++){
  free(malloced[i]);
}

}

void E(FILE* file){
  char *line = NULL;
  size_t len;
  char* malloced[50];
  int nextMallocIndex = 0;
  int nextFreeIndex = 0;
  int count = 0;
  FILE* index = fopen("errorIndex", "w+");

  while(!feof(file)){
    getline(&line, &len, file);
    if(line[0] == 'M'){
      malloced[nextMallocIndex] = (char*) malloc(1);
      // printf("\nMalloced %d\n" , nextMallocIndex);
      // tempPrintMem(0, 35);
      nextMallocIndex++;
    }
    else{
      if(nextFreeIndex != 50){
        if(free(malloced[nextFreeIndex]) == 0){
            fprintf(index, "%d\n", nextFreeIndex);
        }
        malloced[nextFreeIndex] = NULL;
        // printf("\nFreed %d\n" , nextFreeIndex);
        // tempPrintMem(0, 35);
        nextFreeIndex++;
      }
    }
    count++;
  }
}

void F(){

}
void breakpoint(){
  int i = 0;
  i++;
}

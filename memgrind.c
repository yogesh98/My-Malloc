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
void breakpoint();


int main (int argc, char ** argv){
  srand(time(NULL));

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









  // char* a = (char*) malloc(15);
  // printf("\n\nm a\n");
  // tempPrintMem(0, 35);
  //
  // char* b = (char*) malloc(7);
  // printf("\n\nm b\n");
  // tempPrintMem(0, 35);
  //
  // char* c = (char*) malloc(25);
  // printf("\n\nm c\n");
  // tempPrintMem(0, 35);
  //
  // free(a);
  // printf("\n\nf a\n");
  // tempPrintMem(0, 35);
  //
  // char* d = (char*) malloc(5);
  // d[0] = 'd';
  // printf("\n\nm d\n");
  // tempPrintMem(0, 35);

  // char* e = (char*) malloc(1);
  // e[0] = 'e';
  // printf("m e\n\n");
  // tempPrintMem(0, 35);

  // free(c);
  // printf("\n\nf c\n");
  // tempPrintMem(0, 35);

  // char* f = (char*) malloc(1);
  // f[0] = 'f';
  // printf("m f\n\n");
  // tempPrintMem(0, 35);

  // free(b);
  // printf("\n\nf b\n");
  // tempPrintMem(0, 35);

  // char* g = (char*) malloc(1);
  // g[0] = 'g';
  // printf("m g\n\n");
  // tempPrintMem(0, 35);

  // free(d);
  // printf("\n\nf e\n");
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
  // E(fopen("error", "r"));
  // F();
  //for(i = 0; i<100; i++){
    A();
    B();
    C();
    D();
    // E();
    // F();

}

void A(){
  int times;
  int i;
  // A: malloc() 1 byte and immediately free it - do this 150 times
double total_time = 0;
  clock_t start;
  clock_t end;
  for (times=0;times<100;times++){
  start = clock();
  for(i = 0; i<150; i++){
    char* temp = (char*) malloc(sizeof(char));
    free(temp);
  }
  end = clock();
  total_time += (double)(end - start)/CLOCKS_PER_SEC;
}
    total_time = total_time/100;
    printf("The average time required to run TestCase A is: %.2f micro seconds\n",total_time * 1000000); //1000000 for Ghz
}
void B(){
  // B: malloc() 1 byte, store the pointer in an array - do this 150 times.
  // Once you've malloc()ed 50 byte chunks, then free() the 50 1 byte pointers one by one.
  int times;
  double total_time = 0;
  clock_t  start;
  clock_t end;

  int i;
  int j;
  for(times=0;times<100;times++){
    start = clock();
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
  end = clock();
  total_time += (double)(end - start)/CLOCKS_PER_SEC;

}
    total_time = total_time/100;
    printf("The average time required to run TestCase B is: %.2f micro seconds\n",total_time * 1000000); //1000000 for Ghz
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
  double total_time =0;
  clock_t  start,end;
  int times;
  for (times=0;times<100;times++){
    start = clock();
  while(nextMallocIndex < 50){
    int chooser = rand() % 2;
    //printf("This is C");
    if(chooser == 0){
      malloced[nextMallocIndex] = (char*) malloc(1);
      fputs("Malloced\n", toReproduceErrror);
      //printf("\n\nm : %d\n", nextMallocIndex);
      //tempPrintMem();
      nextMallocIndex++;
    }
    else if(chooser == 1){
      if(nextFreeIndex < nextMallocIndex){
        free(malloced[nextFreeIndex]);
        fputs("Freed\n", toReproduceErrror);
        //printf("\n\nf : %d\n", nextFreeIndex);
        //tempPrintMem();
        nextFreeIndex++;
      }
    }
  }
  int i;
  while(nextFreeIndex < 50){
    free(malloced[nextFreeIndex]);
    //printf("This is C");
    //fputs("Freed\n", toReproduceErrror);
    //printf("\n\nf : %d\n", nextFreeIndex);
    //tempPrintMem();
    nextFreeIndex++;
  }
  end = clock();
  total_time += (double)(end - start)/CLOCKS_PER_SEC;

}
total_time = total_time/100;
printf("The average time required to run TestCase C is: %.2f micro seconds\n",total_time * 1000000); //1000000 for Ghz

}
void D(){
  // D: Randomly choose between a randomly-sized malloc() or free()ing a pointer – do this many times (see below)
  // - Keep track of each malloc so that all mallocs do not exceed your total memory capacity - Keep track of each operation so that you eventually malloc() 50 times
  // - Keep track of each operation so that you eventually free() all pointers
  // - Choose a random allocation size between 1 and 64 bytes

  FILE* toReproduceErrror = fopen("error", "w+");
  FILE* randNumbers = fopen("errorNums", "w+");
  int times;
  clock_t start,end;
  double total_time;
  char* malloced[50];
  int nextMallocIndex = 0;
  int nextFreeIndex = 0;
  for (times=0;times<100;times++){
    start = clock();
  while(nextMallocIndex < 50){
    int chooser = rand() % 2;
    //printf("\nThis is D");
    if(chooser == 0){
      int randRequest = rand() % (64 + 1 - 1) + 1;
      malloced[nextMallocIndex] = (char*) malloc(randRequest);
      fprintf(randNumbers, "%d\n", randRequest);
      fputs("Malloced\n", toReproduceErrror);
      //printf("\n\nm : %d size: %d\n", nextMallocIndex, randRequest);
      //tempPrintMem();
      nextMallocIndex++;
    }
    else if(chooser == 1){
      if(nextFreeIndex < nextMallocIndex){
        free(malloced[nextFreeIndex]);
        fputs("Freed\n", toReproduceErrror);
        //printf("\n\nf : %d\n", nextFreeIndex);
        //tempPrintMem();
        nextFreeIndex++;
      }
    }
  }
  int i;
  while(nextFreeIndex < 50){
    free(malloced[nextFreeIndex]);
    fputs("Freed\n", toReproduceErrror);
    //printf("\nThis is D");
    //printf("\n\nf : %d\n", nextFreeIndex);
    //tempPrintMem();
    nextFreeIndex++;
  }
  end = clock();
  total_time += (double)(end-start)/CLOCKS_PER_SEC;

}
total_time = total_time/100;
printf("The average time required to run TestCase D is: %.2f micro seconds\n",total_time * 1000000); //1000000 for Ghz

}
void E(FILE* file){
  char *line = NULL;
  size_t len;
  char* malloced[50];
  int nextMallocIndex = 0;
  int nextFreeIndex = 0;
  int count = 0;
  int times;
  clock_t  start,end;
  double total_time;
  FILE* index = fopen("errorIndex", "w+");
  FILE* randNumbers = fopen("errorNums", "r");
for(times=0;times<100;times++){
  start = clock();
  while(!feof(file)){
    getline(&line, &len, file);
    if(line[0] == 'M'){
      int num;
      fscanf(randNumbers, "%d", &num);
      malloced[nextMallocIndex] = (char*) malloc(num);
      printf("\nMalloced %d\n" , nextMallocIndex);
      tempPrintMem(0, 35);
      nextMallocIndex++;
    }
    else{
      if(nextFreeIndex != 50){
        if(free(malloced[nextFreeIndex]) == 0){
            fprintf(index, "%d\n", nextFreeIndex);
        }
        malloced[nextFreeIndex] = NULL;
        printf("\nFreed %d\n" , nextFreeIndex);
        tempPrintMem(0, 35);
        nextFreeIndex++;
      }
    }
    count++;
  }
  end = clock();
  total_time += (double)(end - start)/CLOCKS_PER_SEC;

}
  total_time = total_time/100;
  printf("The average time required to run TestCase E is: %.2f micro seconds\n",total_time * 1000000); //1000000 for Ghz

}
void F(){

}
void breakpoint(){
  int i = 0;
  i++;
}

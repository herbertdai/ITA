/*
 * main.c
 * For code in Introduction to Algorithm.
 * herbertd
 * 20100816
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "randomize/gen_rand_array.h"
#include "sorts/quick_sort/quick_sort.h"
#include "sorts/heap_sort/heap_sort.h"
#include "sorts/normal_sort.h"

#define  ARRAY_SIZE 999000

int A[ARRAY_SIZE];

static clock_t startTime = 0;
static clock_t endTime = 0;

void startProfileTime();
void endProfileTime(char * title);

int print_array(int array[], int array_size)
{
  int i = 0;
  printf("\n----------------------------------------\n");
  for(i=0; i<array_size; i++){
      if (i%1000 == 0)		 
	  printf("%d, ", array[i]);

  }
  printf("\n----------------------------------------\n");
  return 1;
}



////////////////////////
//Heap sort
///////////////////////
void testHeapSort() {

   int i = 0;

   printf("\nNow sorting by heap sort>>>>>>>>>>\n");
   for(i=0; i<ARRAY_SIZE; i++){
      A[i] = i;
   }
   randomize_in_place(A, ARRAY_SIZE);
   printf("\nRandomized array is :  ");
   print_array(A, ARRAY_SIZE);

   startProfileTime();
   heap_sort(A, ARRAY_SIZE);

   endProfileTime("heap sort");

   printf("\nSorted array is :  ");
   print_array(A, ARRAY_SIZE);
}

////////////////////////
//Test Quick sorts
///////////////////////
void testQuickSort() {
   printf("\nNow sorting by quick sort>>>>>>>>>>\n");

   startProfileTime();
   randomize_in_place(A, ARRAY_SIZE);
   print_array(A, ARRAY_SIZE);
   endProfileTime("Gen random array");

   startProfileTime();
   quick_sort(A, 1, ARRAY_SIZE);
   endProfileTime("quick sort");

   printf("\nSorted array is :  ");
   print_array(A, ARRAY_SIZE);
}

/**
 *
 */
void testInsertSort() {
   printf("\nNow sorting by insert sort>>>>>>>>>>\n");
   startProfileTime();
   randomize_in_place(A, ARRAY_SIZE);
   print_array(A, ARRAY_SIZE);
   endProfileTime("Gen random array");

   startProfileTime();
   insert_sort(A, ARRAY_SIZE);
   endProfileTime("insert sort");

   printf("\nSorted array is :  ");
   print_array(A, ARRAY_SIZE);

}

void testCountingSort() {
   printf("\nNow is Counting sort>>>>>>>>>>\n");
   
   int maxNumber = ARRAY_SIZE;
   int outputArray[ARRAY_SIZE];

   startProfileTime();
   randomize_maxnum(A, ARRAY_SIZE, 256);
   print_array(A, ARRAY_SIZE);
   endProfileTime("Gen random array");

   startProfileTime();
   counting_sort(A, outputArray, ARRAY_SIZE, maxNumber);
   endProfileTime("counting sort");

   printf("\nSorted array is :  ");
   print_array(outputArray, ARRAY_SIZE);
}
 
int main(int *argc, int **argv)
{
   printf("Running ITAlgoritms>>>>>>>>>>>\n");

   testHeapSort();   

   testQuickSort();

//   testInsertSort();

   testCountingSort();

   return 1;
}


void startProfileTime() {
  startTime = clock();
}

void endProfileTime(char *title) {
  endTime = clock();
  double duration = (double)(endTime - startTime)/CLOCKS_PER_SEC;
  printf("%s : used %f seconds\n", title, duration);

  startTime = 0;
  endTime = 0;

}


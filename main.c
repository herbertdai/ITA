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

#define  ARRAY_SIZE 9000000

int print_array(int array[], int array_size)
{
  int i = 0;
  printf("\n----------------------------------------\n");
  for(i=0; i<array_size; i++){
    // p   printf("%d, ", array[i]);
  }
  printf("\n----------------------------------------\n");
  return 1;
}

int A[ARRAY_SIZE];
 
int main(int *argc, int **argv)
{
   int i = 0;


   //Calculate used time:
   clock_t start = 0, finish = 0;
   double duration = 0;

   ////////////////////////
   //Heap sort
   ///////////////////////
   printf("Running ITAlgoritms>>>>>>>>>>>\n");
   printf("\nNow sorting by heap sort>>>>>>>>>>\n");
   for(i=0; i<ARRAY_SIZE; i++){
      A[i] = i;
   }
   randomize_in_place(A, ARRAY_SIZE);
   printf("\nRandomized array is :  ");
   print_array(A, ARRAY_SIZE);

   start = clock();
   heap_sort(A, ARRAY_SIZE);

   finish = clock();
   duration = (double)(finish-start)/CLOCKS_PER_SEC;
   printf("heap sort used %f seconds\n", duration);

   printf("\nSorted array is :  ");
   print_array(A, ARRAY_SIZE);
   
   ////////////////////////
   //Quick sort
   ///////////////////////
   printf("\nNow sorting by quick sort>>>>>>>>>>\n");
   sleep(1);
   start = clock();
   randomize_in_place(A, ARRAY_SIZE);
   finish = clock();
   duration = (double)(finish-start)/CLOCKS_PER_SEC;
   printf("Gen random array[%d] used %f seconds\n", ARRAY_SIZE, duration);

   printf("\nRandomized array is :  ");
   print_array(A, ARRAY_SIZE);

   start = clock();
   quick_sort(A, 1, ARRAY_SIZE);
   finish = clock();
   duration = (double)(finish-start)/CLOCKS_PER_SEC;
   printf("quick sort used %f seconds\n", duration);

   printf("\nSorted array is :  ");
   print_array(A, ARRAY_SIZE);

   
   return 1;
}

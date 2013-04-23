/*
 * quick_sort.c
 * HerbertD 20100831
 */
#include <stdio.h>
#include "quick_sort.h"

int quick_sort(int Array[], int p, int r)
{
   int q = 0;
   if (p < r){
      q = partition(Array, p, r);
      if (q == -1){
	 printf("quich_sort error!\n");
	 return -1;
      }
      quick_sort(Array, p, q - 1);
      quick_sort(Array, q + 1, r);
   }
   return 1;   
}

int partition(int Array[], int p, int r)
{
   int x = 0,
       i = 0,
       j = 0,
       temp = 0;

   x = Array[r - 1];
   i = p - 1;

   for (j=p; j<=r - 1; j++){
      if (Array[j - 1] <= x){
	 i = i + 1;
	 //exchange A[i], A[j]
	 temp = Array[i - 1];
	 Array[i - 1] = Array[j - 1];
	 Array[j - 1] = temp;
      }

   }
   temp = Array[i];
   Array[i] = Array[r - 1];
   Array[r - 1] = temp;
   return i + 1;
}

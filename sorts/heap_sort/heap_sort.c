/*
 * heap_sort.c
 * herbertD 2010-08-18
 */
#include "heap_sort.h"

int get_parent_index(int i)
{
   return (i+1) / 2 - 1;  //debug: array start from 0
}

int get_left_index(int i)
{
   return (i+1) * 2 - 1;
}

int get_right_index(int i)
{
   return (i+1) * 2;
}

int max_heapify(int* array, int i, int array_size)
{
   int l = 0;
   int r = 0;
   int largest = 0;
   int temp = 0;
   
   l = get_left_index(i);
   r = get_right_index(i);
   //printf("array[%d] = %d, array[%d] = %d\n", l, array[l], i, array[i]);
   if (l < array_size && array[l] > array[i]){
      largest = l;
   } else {
      largest = i;
   }
   if (r < array_size && array[r] > array[largest]){
      largest = r;
   }
   if (largest != i){
      temp = array[i];
      array[i] = array[largest];
      array[largest] = temp;
      max_heapify(array, largest, array_size);
   }
   return 1;
}

int build_max_heap(int* array, int array_size)
{
   int i = 0;
   for(i=array_size / 2 - 1; i>=0; i--){
      max_heapify(array, i, array_size);
   }
   return 1;
}

int heap_sort(int* array, int array_size)
{
   int i = 0;
   int temp = 0;
   int heap_size = array_size;
   build_max_heap(array, array_size);

   for (i=array_size - 1; i>0; i--){
      temp = array[i];
      array[i] = array[0];
      array[0] = temp;
      heap_size--;
      max_heapify(array, 0, heap_size);
   }
}

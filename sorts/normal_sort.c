/**
   Normal sort: insert sort
 */
#include "normal_sort.h"

void insert_sort(int * A, int arraySize) {
  int j = 1;
  int i = 0; 

  printf("start insert sort>>>\n");

  for (j=1; j<arraySize; j++) {

    int key = A[j];

    //Insert A[j] into the sorted sequence A[1..j-1]
    i = j - 1;

    //printf("i=%d, j=%d, A[j]=%d\n", i, j, key);

    while (i >= 0 && A[i] > key) {
      A[i+1] = A[i];
      i--;
    }

    A[i+1] = key;

  }
}

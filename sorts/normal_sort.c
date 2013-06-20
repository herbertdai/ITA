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

/**
 * Counting sort, Thelta(n)
 * @param k sorted numbers is [0, k)
 */
void counting_sort(int *ArrayToSort, int *OutputArray, int arraySize, int k) {
  int *A = ArrayToSort;
  int *B = OutputArray;
  int C[k]; //[0, k)
  int i = 0, j = 0;

  for (i=0; i<k; i++) {
    C[i] = 0;
  }

  for (j=0; j<arraySize; j++) {
    C[A[j]]++;
  } // Now C[i] is the item count equals i;

  for (i=1; i<k; i++) {
    C[i] = C[i] + C[i - 1];
  } // Now C[i] is the number count of <= i

  for (j=arraySize-1; j>=0; j--) {
    B[C[A[j]] - 1] = A[j];
    C[A[j]] = C[A[j]] - 1;
  }

}

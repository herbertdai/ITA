/**
   Normal sort: insert sort
 */
#include "normal_sort.h"
#include <malloc.h>

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
  int * B = (int*) malloc(arraySize * sizeof(int));

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

  // for (j=arraySize-1; j>=0; j--) {
  for (j=0; j<arraySize; j++) {
    B[C[A[j]] - 1] = A[j];
    C[A[j]] = C[A[j]] - 1;
  }

  for (j=0; j<arraySize; j++) {
      A[j] = B[j];
  }

  if (B != NULL) {
      free(B);
      B = NULL;
  }

}

void radixSort(int *ArrayToSort, int begin, int end, int d, int radix) {

    int i = 0, j = 0, k = 0;
    int index = 0;
    int count[radix];
    //int bucket to hold temperoray:
    int * bucket = (int*) malloc((end - begin + 1) * sizeof(int));

    // start counting sort from lowerest bit:
    for (i=0; i<d; i++) {
        printf("Start sort on digit %d\n", i);
        
        // Init count[]
        for (j=0; j<radix; j++) {
            count[j] = 0;
        }

        // Count the number into count[]        
        for (j=begin; j<=end; j++) {
            index = getDigit(ArrayToSort[j], i, radix);
            count[index] ++;
        }

        // Cal count[i] to be the postion of it's indexed number
        for (j=1; j<radix; j++) {
            count[j] = count[j] + count[j-1];
        } 

        // Get the number to the correct position in bucket
        for (j=end; j>=begin; j--) {
            index = getDigit(ArrayToSort[j], i, radix);
            bucket[count[index] - 1/*index = count -1*/] = ArrayToSort[j];
            --count[index];
        }
        
        // copy bucket back to ArrayToSort:
        for (j=begin, k=0; j<=end; j++, k++) {
            ArrayToSort[j] = bucket[k];
        }
        
    }
    
    if (bucket != NULL) {
        free(bucket);
        bucket = NULL;
    }
}

int getDigit(int number, int i, int radix) {
    /* FOR loop slowed us down.
    int j = 0;
    for (j=0; j<i; j++) {
        number /= radix;
    }
    return number % radix; */

    // Pre-calculated array is much faster:
    int a[] = {1, 1, 10, 100, 1000, 10000, 100000};   
    return (number/a[i]) % 10;
}

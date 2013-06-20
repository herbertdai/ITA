/**
 Normal sorts: insert sort
 @date 20130423
 @author dwy
 */

#include <stdio.h>

/**
 * insert sort, Complexity: Thelta(n*n)
 */
void insert_sort(int * ArrayToSort, int arraySize);

/**
 * Counting sort, Thelta(n)
 * @param k the max value of sorted items
 */
void counting_sort(int *ArrayToSort, int *OutputArray, int arraySize, int k);

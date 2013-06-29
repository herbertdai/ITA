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

/**
 * Radix sort (lower poistion first)
 * Using counting sort to sort every digit from the lower bit
 * @param begin sort start index
 * @param begin sort end index
 * @param d the max digit count of number (e.g number d(5678) = 4)
 * @param begin sort end index
 * @date 20130629
 * @author dwy
 */
void radixSort(int *ArrayToSort, int begin, int end, int d, int radix);

/**
 * Get digit by index i
 * @param radix the radix of number
 */
int getDigit(int number, int i, int radix);

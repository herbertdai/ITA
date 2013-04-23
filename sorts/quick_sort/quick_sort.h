/*
 * quick_sort.h
 * HerbertD 20100831
 */
/*
 * return n(>0) success
 *	  -1    fail
 */

int quick_sort(int Array[], int p, int r);

/*
 * Partition the array into two parts: smaller and bigger  
 * return n	  the seperated position after partition  
 *	  -1	  fail
 */
int partition(int Array[], int p, int r);

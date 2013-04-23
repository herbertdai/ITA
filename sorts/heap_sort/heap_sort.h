/*
 * heap_sort.h
 * Herbertd reserve all rights. 2010
 * 20100814
 */

int get_parent_index(int i);

int get_left_index(int i);

int get_right_index(int i);

/*
 * Make the max_heapify at position i
 * param[in]: array	array to hold orign list.
 * param[in]: i		index to start making
 * param[in]: array_size array size
 * return 1		success
 *	  0		fail
 */
int max_heapify(int* array, int i, int array_size);


/*
 * Build the max_heapify from array 
 * param[in]: array	array to build.
 * param[in]: array_size array size
 * return 1		success
 *	  0		fail
 */
int build_max_heap(int* array, int array_size);

/*
 * Sort the heap
 * param[in]: array	array to build.
 * param[in]: array_size array size
 * return 1		success
 *	  0		fail
 */
int heap_sort(int* array, int array_size);

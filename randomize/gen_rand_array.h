/*
 * gen_rand_array.h
 * herbertd 
 * 20100814
 */

#include <time.h>
#include <stdlib.h>

/*
 * randomize the array
 * @param[in]:Array	  array to randomize
 * @param[in]:lenth	  lenth of array to randomize
 * @return  1	  random success
 *	    0	  fail
 */
int randomize_in_place(int* Array, int lenth);

/*
 * randomize the array
 * @param[in]:Array	  array to randomize
 * @param[in]:lenth	  lenth of array to randomize
 * @param[in]:maxNum	  maxNum of generated randoms.
 * @return  1	  random success
 *	    0	  fail
 */
int randomize_maxnum(int* Array, int lenth, int maxNum);      

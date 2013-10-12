/*
 * main.c
 * For code in Introduction to Algorithm.
 * herbertd
 * 20100816
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "randomize/gen_rand_array.h"
#include "sorts/quick_sort/quick_sort.h"
#include "sorts/heap_sort/heap_sort.h"
#include "sorts/normal_sort.h"
#include "BSTree/binary_tree.h"


#define  ARRAY_SIZE 100

int A[ARRAY_SIZE];

static clock_t startTime = 0;
static clock_t endTime = 0;

void startProfileTime();
void endProfileTime(char * title);

int print_array(int array[], int array_size)
{
  int i = 0;
  printf("\n----------------------------------------\n");
  for(i=0; i<array_size; i++){
      //      if (i%10000 == 0)		 
	  printf("%d, ", array[i]);

  }
  printf("\n----------------------------------------\n");
  return 1;
}



////////////////////////
//Heap sort
///////////////////////
void testHeapSort() {

   int i = 0;

   printf("\nNow sorting by heap sort>>>>>>>>>>\n");
   for(i=0; i<ARRAY_SIZE; i++){
      A[i] = i;
   }
   randomize_in_place(A, ARRAY_SIZE);
   printf("\nRandomized array is :  ");
   print_array(A, ARRAY_SIZE);

   startProfileTime();
   heap_sort(A, ARRAY_SIZE);

   endProfileTime("heap sort");

   printf("\nSorted array is :  ");
   print_array(A, ARRAY_SIZE);
}

////////////////////////
//Test Quick sorts
///////////////////////
void testQuickSort() {
   printf("\nNow sorting by quick sort>>>>>>>>>>\n");

   startProfileTime();
   randomize_in_place(A, ARRAY_SIZE);
   print_array(A, ARRAY_SIZE);
   endProfileTime("Gen random array");

   startProfileTime();
   quick_sort(A, 1, ARRAY_SIZE);
   endProfileTime("quick sort");

   printf("\nSorted array is :  ");
   print_array(A, ARRAY_SIZE);
}

/**
 *
 */
void testInsertSort() {
   printf("\nNow sorting by insert sort>>>>>>>>>>\n");
   startProfileTime();
   randomize_in_place(A, ARRAY_SIZE);
   print_array(A, ARRAY_SIZE);
   endProfileTime("Gen random array");

   startProfileTime();
   insert_sort(A, ARRAY_SIZE);
   endProfileTime("insert sort");

   printf("\nSorted array is :  ");
   print_array(A, ARRAY_SIZE);

}

void testCountingSort() {
   printf("\nNow is Counting sort>>>>>>>>>>\n");
   
   int maxNumber = ARRAY_SIZE;


   startProfileTime();
   randomize_maxnum(A, ARRAY_SIZE, 256);
   print_array(A, ARRAY_SIZE);
   endProfileTime("Gen random array");

   startProfileTime();
   counting_sort(A, NULL, ARRAY_SIZE, maxNumber);
   endProfileTime("counting sort");

   printf("\nSorted array is :  ");
   print_array(A, ARRAY_SIZE);
}

void testRadixSort() {
   printf("\nNow is Radix sort>>>>>>>>>>\n");
   
   startProfileTime();
   randomize_maxnum(A, ARRAY_SIZE, 256);
   print_array(A, ARRAY_SIZE);
   endProfileTime("Gen random array");

   startProfileTime();
   radixSort(A, 0, ARRAY_SIZE - 1, 5, 10); 
   endProfileTime("Radix sort");

   printf("\nSorted array is :  ");
   print_array(A, ARRAY_SIZE);

}
void test_sorts() {
   testHeapSort();   

   testQuickSort();

//   testInsertSort();

   testCountingSort();

   testRadixSort();

}

void testBSTree() {

    printf("\nNow is Create Binary tree with node size %d >>>>>>>>>>\n", ARRAY_SIZE);
    randomize_in_place(A, ARRAY_SIZE);
    //    randomize_maxnum(A, ARRAY_SIZE, ARRAY_SIZE);
    print_array(A, ARRAY_SIZE);

    startProfileTime();
    tree_t * tree = tree_create(A, ARRAY_SIZE);
    endProfileTime("Create Binary search tree ");

#if 0
    printf("\nPre order traverse:\n");
    tree_preorder_traverse(tree->root, my_treenode_key_traverse);

    printf("\nPost order traverse:\n");
    tree_postorder_traverse(tree->root, my_treenode_key_traverse);

    printf("\nIn order traverse:\n");
    tree_inorder_traverse(tree->root, my_treenode_key_traverse);
#endif

    int key = 50;
    startProfileTime();

    treenode_t * search_result = tree_search(tree->root, key);
    endProfileTime("Binary tree search");
    
    if (search_result != get_nil_node()) {
        printf("Found key:%d\n", key);
    } else {
        printf(" Not found key:%d\n", key);
    }
    
    tree_left_rotate(tree, search_result);
    tree_right_rotate(tree, search_result);

    traverse_no_recurise(tree->root, my_treenode_key_traverse);

    treenode_t * max, * min;
    max = tree_max(tree->root);
    min = tree_min(tree->root);
    printf("\nmax = %ld\n min = %ld\n", max->key, min->key);

    treenode_t * bigger = tree_successor(search_result);
    printf("successor = %ld\n", (bigger!=NULL) ? bigger->key : -1);
    treenode_t * smaller = tree_predecessor(search_result);
    printf("perdecessor = %ld\n", (smaller!=NULL) ? smaller->key : -1);
    
    //Test delete:
    treenode_t * deleted_node = tree_delete(tree, search_result);
    if (deleted_node)
        printf("del %p, key=%ld from tree.\n", deleted_node, deleted_node->key);
    tree_inorder_traverse(tree->root, my_treenode_key_traverse);
    //    traverse_no_recurise(tree->root, my_treenode_key_traverse);
    
    get_tree_height(tree->root);
    int height = get_tree_height(tree->root);
    
    printf("\nget tree h = %d\n", height);
 
    tree_destroy(tree, NULL);
}
 
typedef struct foo {
    short b;
    long i;
    char a;
    char c;
}foo_;

int main(int *argc, int **argv)
{
   printf("Running ITAlgoritms>>>>>>>>>>>\n");

#if 0
   test_sorts();
#endif

   testBSTree();
   
   printf("foo size =%lu\n", sizeof(foo_));
   return 1;
}


void startProfileTime() {
  startTime = clock();
}

void endProfileTime(char *title) {
  endTime = clock();
  double duration = (double)(endTime - startTime)/CLOCKS_PER_SEC;
  printf("%s : used %f seconds\n", title, duration);

  startTime = 0;
  endTime = 0;

}


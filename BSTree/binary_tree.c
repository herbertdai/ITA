/***************
 * binary_tree.c
 * Tree define for a Binary Tree.
 * @author herbert Dai
 * @date 20130812
 ***************/

#include "binary_tree.h"

/**
 * Allocates a empty tree from heap, this creates a new tree 
 */
tree_t* tree_create() {
    tree_t* this_tree = (tree_t*)malloc (sizeof(tree_t));
    this_tree->root = NULL;
    return this_tree;
}

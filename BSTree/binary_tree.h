/***************
 * binary_tree.h
 * Tree define for a Binary Tree.
 * @author herbert Dai
 * @date 20130812
 ***************/

#ifndef BINARY_TREE_H_INCLUDED__ 
#define BINARY_TREE_H_INCLUDED__ 

#ifdef __cplusplus
extern "C" {
#endif

#include "unistd.h"
#include <stdio.h>

typedef struct _treenode_t
{
 struct _treenode_t *left_child;
 struct _treenode_t *right_child;

 union{
  void            *data;
  struct _tree_t *tree;
  const char  *str;
  long             key;
 };
}treenode_t;

typedef struct _tree_t
{
 size_t  size; /* count of nodes */
 treenode_t *root;
}tree_t, *tree_p;

/**
 * A prototype of callbacked function called by:
 *  - tree_destroy()
 * - tree_traverse()
 * - tree_node_free()
 * NULL for no use 
 */
typedef void(*pfunc_tree_callback)(treenode_t* node); 

/**
 * An prototype example of free node data function implemented by caller:
 */
static void my_treenode_data_free(treenode_t *node)
{
  free(node->data);
  //TODO: DBG_TRACE("my_treenode_data_free/n");
}

/**
 * A prototype example of traverse implemented by caller:
 */
static void my_treenode_key_traverse(treenode_t *node)
{
 printf("    key=%ld\n", node->key);
}

/**
 * Traverses a tree, applied callback functionn for each node
 */
int tree_traverse(treenode_t *tree_root, pfunc_tree_callback pfcb_traversenode);

/**
 * Allocates a empty tree from heap, this creates a new tree 
 */
tree_t* tree_create();

/** 
 * Clears a tree and free memory, the tree cannot be used later
 */
void tree_destroy(tree_t *in_tree, pfunc_tree_callback  pfcb_freedata);

/** 
 * Creates a new node assigned with data, not allocates for data
 */
treenode_t* tree_node_create(void* data);

/** 
 * Free a tree node and it&apos;s associated nodes, the freed node cannot be used later
 */
void tree_node_free(treenode_t* node, pfunc_tree_callback  pfcb_freedata);





#ifdef __cplusplus
}
#endif

#endif  /* LIST_H_INCLUDED__ */

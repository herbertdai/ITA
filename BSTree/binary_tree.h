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
#include <stdlib.h>

#define RED 0
#define BLACK 1

typedef struct _treenode_t
{
    struct _treenode_t *left_child;
    struct _treenode_t *right_child;
    struct _treenode_t *parent;
    char color;

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
 printf("    key=%ld", node->key);
}

/**
 * Traverses a tree in preorder: root, left, right, applied callback functionn for each node
 */
int tree_preorder_traverse(treenode_t *tree_root, pfunc_tree_callback pfcb_traversenode);

/**
 * Traverses a tree in post order: left, right,root, applied callback functionn for each node
 */
int tree_postorder_traverse(treenode_t *tree_root, pfunc_tree_callback pfcb_traversenode);

/**
 * Traverses a tree in order: left, root, right, applied callback functionn for each node
 */
int tree_inorder_traverse(treenode_t *tree_root, pfunc_tree_callback pfcb_traversenode);

/**
 * Allocates a empty tree from heap, this creates a new tree 
 */
tree_t* tree_create();

    tree_t* tree_create(int * TREE_DATAS, int data_size);

/**
 * Add node to a propreiate position, smaller to left, bigger to right. recursion.
 */
void add_node(treenode_t *root, treenode_t *new_node);

/**
 * Insert a node to a propreiate position none-recursion.
 * @param[in] z the node to insert
 */
void tree_insert(tree_t * tree, treenode_t * z);

/**
 * Delete a node in tree.
 * @return the node deleted.
 */
treenode_t * tree_delete(tree_t * tree, treenode_t * z);

/** 
 * Clears a tree and free memory, the tree cannot be used later
 */
void tree_destroy(tree_t *in_tree, pfunc_tree_callback  pfcb_freedata);

int  tree_clean(treenode_t *tree_root, pfunc_tree_callback pfcb_traversenode);

/** 
 * Creates a new node assigned with data, not allocates for data
 */
treenode_t* tree_node_create(void* data);

    /**
     * Create a new node with the long key
     */
    treenode_t* tree_node_create_with_key(long key);

/** 
 * Free a tree node and it&apos;s associated nodes, the freed node cannot be used later
 */
void tree_node_free(treenode_t* node, pfunc_tree_callback  pfcb_freedata);

    /**
     * Binary tree search a key
     */
    treenode_t * tree_search(treenode_t * tree_root, int key);

/**
 * traverse the three by compare the pointer.(prev, cur, next)
 */
void traverse_no_recurise(treenode_t *tree_root, pfunc_tree_callback pfcb_travese);


/**
 * Get the minimum node of the tree
 */
treenode_t * tree_min(treenode_t * tree_root);

/**
 * Get the maximum node of the tree
 */
treenode_t * tree_max(treenode_t * tree_root);

treenode_t * tree_successor(treenode_t * tree_root);

treenode_t * tree_predecessor(treenode_t * tree_root);

//////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif  /* LIST_H_INCLUDED__ */

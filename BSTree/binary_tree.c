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

    int i = 0;

    long  TREE_DATAS[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; 

    tree_t* this_tree = (tree_t*)malloc (sizeof(tree_t));
    
    // init root node:
    treenode_t * new_node = tree_node_create(&TREE_DATAS[i]);        
    this_tree->root = new_node;
    
    treenode_t * next_root = this_tree->root;

    for (i=1; i<sizeof(TREE_DATAS) / sizeof(long); i++) {

        new_node = tree_node_create(&TREE_DATAS[i]);        
        if (i%2 == 0) {
            printf("new node at left==> i = %d ", i);
            next_root->left_child = new_node;            
        } else {
            printf("new node at right==> i = %d ", i);
            next_root->right_child = new_node;            
        }
        next_root = new_node;
    }

    return this_tree;
}

treenode_t* tree_node_create(void* data) {
    treenode_t * node = (treenode_t*) malloc(sizeof(treenode_t));
    node->data = *(long *)data;
    node->left_child = NULL;
    node->right_child = NULL;
}

/** 
 * Clears a tree and free memory, the tree cannot be used later
 */
void tree_destroy(tree_t *in_tree, pfunc_tree_callback  pfcb_freedata) {

    tree_clean(in_tree->root, pfcb_freedata);
    //TODO: free tree itself. dwy
    free(in_tree);

    printf("Tree destory.\n");
}


/**
 * Traverses a tree in root first older, applied callback functionn for each node
 */
int  tree_preorder_traverse(treenode_t *tree_root, pfunc_tree_callback pfcb_traversenode) {
    if (NULL == tree_root) 
        return -1;

     //Visit the root
    if (pfcb_traversenode) 
        pfcb_traversenode(tree_root);

    //Visit left child
    tree_preorder_traverse(tree_root->left_child, pfcb_traversenode);

    //Visit right child
    tree_preorder_traverse(tree_root->right_child, pfcb_traversenode);
}

/**
 * Traverses a tree in root last older, applied callback functionn for each node
 */
int  tree_postorder_traverse(treenode_t *tree_root, pfunc_tree_callback pfcb_traversenode) {
    if (NULL == tree_root) 
        return -1;

      //Visit left child
    tree_postorder_traverse(tree_root->left_child, pfcb_traversenode);

    //Visit right child
    tree_postorder_traverse(tree_root->right_child, pfcb_traversenode);

    //Visit the root
    if (pfcb_traversenode) 
        pfcb_traversenode(tree_root);

}

/**
 * Traverses a tree and clean every node, applied callback function for each node for free the memory if needed.
 */
int  tree_clean(treenode_t *tree_root, pfunc_tree_callback pfcb_traversenode) {
    if (NULL == tree_root) 
        return -1;

    //Visit left child
    tree_clean(tree_root->left_child, pfcb_traversenode);

    //Visit right child
    tree_clean(tree_root->right_child, pfcb_traversenode);

    //Visit the root
    if (pfcb_traversenode) 
        pfcb_traversenode(tree_root);

    printf("Clean node=%p", tree_root);
    free(tree_root);
}

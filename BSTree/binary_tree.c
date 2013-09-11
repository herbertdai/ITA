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
tree_t* tree_create(int * TREE_DATAS, int data_size) {

    int i = 0;

    //    long  TREE_DATAS[10] = {0, 8, 2, 5, 4, 7, 1, 6, 3, 9}; 

    tree_t* this_tree = (tree_t*)malloc (sizeof(tree_t));
    
    // init root node:
    treenode_t * new_node = tree_node_create_with_key(TREE_DATAS[0]);        
    this_tree->root = new_node;
    
    for (i=1; i<data_size; i++) {
        //    for (i=1; i<sizeof(TREE_DATAS) / sizeof(long); i++) {

        new_node = tree_node_create_with_key(TREE_DATAS[i]);        
        
        add_node(this_tree->root, new_node);
    }

    return this_tree;
}

void add_node(treenode_t *root, treenode_t *new_node) {

    if (new_node->key > root->key) {
        if (root->right_child != NULL) {
            add_node(root->right_child, new_node);
        } else {
            root->right_child = new_node;
        }
    } else {
        if (root->left_child != NULL) {
            add_node(root->left_child, new_node);
        } else {
            root->left_child = new_node;
        }
    }
}


treenode_t* tree_node_create(void* data) {
    treenode_t * node = (treenode_t*) malloc(sizeof(treenode_t));
    node->data = *(long *)data;
    node->left_child = NULL;
    node->right_child = NULL;
}

treenode_t* tree_node_create_with_key(long key) {
    treenode_t * node = (treenode_t*) malloc(sizeof(treenode_t));
    node->key = key;
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

int  tree_inorder_traverse(treenode_t *tree_root, pfunc_tree_callback pfcb_traversenode) {
    if (NULL == tree_root) 
        return -1;

      //Visit left child
    tree_inorder_traverse(tree_root->left_child, pfcb_traversenode);

    //Visit the root
    if (pfcb_traversenode) 
        pfcb_traversenode(tree_root);

    //Visit right child
    tree_inorder_traverse(tree_root->right_child, pfcb_traversenode);

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

    //    printf("Clean node=%p\n", tree_root);
    free(tree_root);
}

treenode_t * tree_search(treenode_t * tree_root, int key) {
    
    if (tree_root == NULL || tree_root->key == key) {
        return tree_root;
    }

    if (key > tree_root->key) {
        tree_search(tree_root->right_child, key);
    } else {
        tree_search(tree_root->left_child, key);
    }

}

/* None recursion traverse From wiki:
visit(root)
    prev    := null
    current := root
    next    := null
    
    while current != null
        if prev == current.parent //if we can go left
            prev := current
            next := current.left
        if next == null or prev == current.left // if left is empty and Pre is going from left, dump and prepare to go right
            print current.value
            prev := current
            next := current.right
        if next == null or prev == current.right // If we can't go right (leaf) and previous is right, prepare to go back to parent.
            prev := current
            next := current.parent
        current := next
*/

void traverse_no_recurise(treenode_t *tree_root, pfunc_tree_callback pfcb_traversenode) {
    treenode_t *cur = tree_root;
    
    //    while (true) {
        
    //    }
}



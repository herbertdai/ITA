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

        new_node = tree_node_create_with_key(TREE_DATAS[i]);        
        
        add_node(this_tree->root, new_node);
        //tree_insert(this_tree, new_node);
    }

    return this_tree;
}

void add_node(treenode_t *root, treenode_t *new_node) {
    //    printf("new_node key =%d, root-key=%d\n", new_node->key, root->key);

    if (new_node->key >= root->key) {
        if (root->right_child != NULL) {
            add_node(root->right_child, new_node);
        } else {
            root->right_child = new_node;
            new_node->parent = root;
        }
    } else if (new_node->key < root->key) {
        if (root->left_child != NULL) {
            add_node(root->left_child, new_node);
        } else {
            root->left_child = new_node;
            new_node->parent = root;
        }
    } 
}

void tree_insert(tree_t * tree, treenode_t * z) {
    treenode_t * y = z;
    treenode_t * x = tree->root;
    
    // Track the z's position and it's parent:y
    while (x != NULL) {
        y = x;
        if (z->key < x->key) {
            x = x->left_child;
        } else {
            x = x->right_child;
        }
    }
    printf("find pos: x = %p, key=%ld\n", y, z->key);

    // Set the z's field.
    z->parent = y;
    if (y == NULL) {
        tree->root = z;
    } else {
        if (z->key < y->key) {
            y->left_child = z;
        } else {
            y->right_child = z;
        }
    }
}

treenode_t * tree_delete(tree_t * tree, treenode_t * z) {
    if (z == NULL) {
        return NULL;
    }

    treenode_t * y = NULL;
    treenode_t * x = NULL;

    // Find the place (y) to delete:
    if ((z->left_child != NULL) || (z->right_child != NULL)) {
        y = z;
    } else {
        y = tree_successor(z);
    }
    
    // Set the node (x) next to y:
    if (y->left_child != NULL) {
        x = y->left_child;
    } else {
        x = y->right_child;
    }
    
    // skip y
    if (x) {
        x->parent = y->parent;
    }
    if (y->parent == NULL) {
        tree->root = x;
    } else {
        if (y == y->parent->left_child) {
            y->parent->left_child = x;
        } else { //y == y->parent->right_child
            y->parent->right_child = x;
        }
    }
    // if y != z, copy y to z 
    if (y != z) {
        z->key = y->key;
        //TODO: Copy y's satellite date to z.
    }
    return y;

}

treenode_t* tree_node_create(void* data) {
    treenode_t * node = (treenode_t*) malloc(sizeof(treenode_t));
    node->data = data;
    node->left_child = NULL;
    node->right_child = NULL;
    node->parent = NULL;
}

treenode_t* tree_node_create_with_key(long key) {
    treenode_t * node = (treenode_t*) malloc(sizeof(treenode_t));
    node->key = key;
    node->left_child = NULL;
    node->right_child = NULL;
    node->parent = NULL;
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
    if (!tree_root)
        return;
    treenode_t *current = tree_root;
    treenode_t *prev = NULL;
    treenode_t *next = NULL;
    
    while (current) {
        // if we can go left
        if (prev == current->parent) {
            prev = current;       //prepare to go left
            next = current->left_child;
        }
        // if left is empty and Pre is going from left, dump and prepare to go right
        if (next == NULL || prev == current->left_child) {
            pfcb_traversenode(current);
            prev = current;
            next = current->right_child;
        }
        // If we can't go right (leaf) and previous is right, prepare to go back to parent.
        if (next == NULL || prev == current->right_child) {
            prev = current;
            next = current->parent;
        }
        
        current = next;
    }


}

treenode_t * tree_min(treenode_t * tree_root) {
    if (tree_root == NULL) {
        return NULL;
    }
    
    treenode_t * cur = tree_root;
    
    while (cur->left_child != NULL) {
        cur = cur->left_child;
    }
    return cur;
}

treenode_t * tree_max(treenode_t * tree_root) {
    if (tree_root == NULL) {
        return NULL;
    }
    
    treenode_t * cur = tree_root;
    
    while (cur->right_child != NULL) {
        cur = cur->right_child;
    }
    return cur;
}

treenode_t * tree_successor(treenode_t * root){
    if (root == NULL) {
        printf("Tree is null.\n");
        return NULL;
    }
        
    treenode_t * ynode = NULL;

    if (root->right_child != NULL) {
        return tree_min(root->right_child);
    }

    ynode = root->parent;
    while (ynode && ynode->right_child == root) {
        root = ynode;
        ynode = ynode->parent;
    }
    return ynode;
}

treenode_t * tree_predecessor(treenode_t * root){
    if (root == NULL) {
        printf("Tree is null.\n");
        return NULL;
    }
        
    treenode_t * ynode = NULL;
    
    if (root->left_child != NULL) {
        return tree_max(root->left_child);
    }
    
    ynode = root->parent;
    while (ynode && ynode->left_child == root) {
        root = ynode;
        ynode = ynode->parent;
    }

    return ynode;
}


/***************
 * binary_tree.c
 * Tree define for a Binary Tree.
 * @author herbert Dai
 * @date 20130812
 ***************/

#include "binary_tree.h"

static treenode_t * gNil;

/**
 * Allocates a empty tree from heap, this creates a new tree 
 */
tree_t* tree_create(int * TREE_DATAS, int data_size) {

    int i = 0;
    gNil = tree_node_create_with_key(0);
    gNil->left_child = NULL;
    gNil->right_child = NULL;
    gNil->parent = NULL;
    gNil->key = -1;

    tree_t* this_tree = (tree_t*)malloc (sizeof(tree_t));
    treenode_t * new_node = tree_node_create_with_key(TREE_DATAS[0]);
    this_tree->root = new_node;
    this_tree->root->color = BLACK;
    
    for (i=1; i<data_size; i++) {

        new_node = tree_node_create_with_key(TREE_DATAS[i]);        
        
        //                add_node(this_tree->root, new_node);
        RBTree_insert(this_tree, new_node);
        //tree_insert(this_tree, new_node);
    }
    
    return this_tree;
}

/**
 * Recruisive insert
 */
void add_node(treenode_t *root, treenode_t *new_node) {
    //    printf("new_node key =%d, root-key=%d\n", new_node->key, root->key);

    if (new_node->key >= root->key) {
        if (root->right_child != gNil) {
            add_node(root->right_child, new_node);
        } else {
            root->right_child = new_node;
            new_node->parent = root;
        }
    } else {
        if (root->left_child != gNil) {
            add_node(root->left_child, new_node);
        } else {
            root->left_child = new_node;
            new_node->parent = root;
        }
    } 
}

/**
 * Non-Recruisive insert
 */
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
    if (z == gNil) {
        return NULL;
    }

    treenode_t * y = gNil;
    treenode_t * x = gNil;

    // Find the place (y) to delete:
    if ((z->left_child == gNil) || (z->right_child == gNil)) {
        y = z;
    } else {
        y = tree_successor(z);
    }
    
    // Set the node (x) next to y:
    if (y->left_child != gNil) {
        x = y->left_child;
    } else {
        x = y->right_child;
    }
    
    // skip y
    if (x) {
        x->parent = y->parent;
    }
    if (y->parent == gNil) {
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
    node->left_child = gNil;
    node->right_child = gNil;
    node->parent = gNil;
}

treenode_t* tree_node_create_with_key(long key) {
    treenode_t * node = (treenode_t*) malloc(sizeof(treenode_t));
    node->key = key;
    node->left_child = gNil;
    node->right_child = gNil;
    node->parent = gNil;
    node->color = BLACK;
    return node;
}

/** 
 * Clears a tree and free memory, the tree cannot be used later
 */
void tree_destroy(tree_t *in_tree, pfunc_tree_callback  pfcb_freedata) {

    tree_clean(in_tree->root, pfcb_freedata);
    free(in_tree);
    
    if (gNil) {
        free(gNil);
        gNil = NULL;
    }

    printf("Tree destory.\n");
}


/**
 * Traverses a tree in root first older, applied callback functionn for each node
 */
int  tree_preorder_traverse(treenode_t *tree_root, pfunc_tree_callback pfcb_traversenode) {
    if (gNil == tree_root) 
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
    if (gNil == tree_root) 
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
    if (gNil == tree_root) 
        return -1;

      //Visit left child
    tree_inorder_traverse(tree_root->left_child, pfcb_traversenode);

    //Visit the root
    if (pfcb_traversenode) 
        pfcb_traversenode(tree_root);

    //Visit right child
    tree_inorder_traverse(tree_root->right_child, pfcb_traversenode);

}

int get_tree_height(treenode_t *tree_root) {
    if (tree_root == gNil || tree_root == NULL) 
        return -1;

    int left_height = get_tree_height(tree_root->left_child);
    int right_height = get_tree_height(tree_root->right_child);
    if (left_height > right_height) {
        return left_height + 1;
    } else {
        return right_height + 1;
    }
    //    return MAX(get_tree_height(tree_root->left_child), get_tree_height(tree_root->right_child)) + 1; 
}


/**
 * Traverses a tree and clean every node, applied callback function for each node for free the memory if needed.
 */
int  tree_clean(treenode_t *tree_root, pfunc_tree_callback pfcb_traversenode) {
    if (gNil == tree_root) 
        return -1;

    //Visit left child
    tree_clean(tree_root->left_child, pfcb_traversenode);

    //Visit right child
    tree_clean(tree_root->right_child, pfcb_traversenode);

    //Visit the root
    if (pfcb_traversenode) 
        pfcb_traversenode(tree_root);

    //    printf("Clean node=%p\n", tree_root);
    if (tree_root != gNil) {
        free(tree_root);
    }
}

treenode_t * tree_search(treenode_t * tree_root, int key) {
    
    if (tree_root == gNil || tree_root->key == key) {
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
    treenode_t *prev = gNil;
    treenode_t *next = gNil;
    
    while (current != gNil) {
        // if we can go left
        if (prev == current->parent) {
            prev = current;       //prepare to go left
            next = current->left_child;
        }
        // if left is empty and Pre is going from left, dump and prepare to go right
        if (next == gNil || prev == current->left_child) {
            pfcb_traversenode(current);
            prev = current;
            next = current->right_child;
        }
        // If we can't go right (leaf) and previous is right, prepare to go back to parent.
        if (next == gNil || prev == current->right_child) {
            prev = current;
            next = current->parent;
        }
        
        current = next;
    }


}

treenode_t * tree_min(treenode_t * tree_root) {
    if (tree_root == gNil) {
        return gNil;
    }
    
    treenode_t * cur = tree_root;
    
    while (cur->left_child != gNil) {
        cur = cur->left_child;
    }
    return cur;
}

treenode_t * tree_max(treenode_t * tree_root) {
    if (tree_root == gNil) {
        return NULL;
    }
    
    treenode_t * cur = tree_root;
    
    while (cur->right_child != gNil) {
        cur = cur->right_child;
    }
    return cur;
}

treenode_t * tree_successor(treenode_t * root){
    if (root == gNil) {
        printf("Tree is null.\n");
        return gNil;
    }
        
    treenode_t * ynode = gNil;

    if (root->right_child != gNil) {
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
    if (root == gNil) {
        printf("Tree is null.\n");
        return gNil;
    }
        
    treenode_t * ynode = gNil;
    
    if (root->left_child != gNil) {
        return tree_max(root->left_child);
    }
    
    ynode = root->parent;
    while (ynode && ynode->left_child == root) {
        root = ynode;
        ynode = ynode->parent;
    }

    return ynode;
}

//////////////////////////////////////
// RED BLACK tree
//////////////////////////////////////
void tree_left_rotate(tree_p T, treenode_t * x) {

    if (!T || !x || x == gNil) 
        return;
    
    // Make sure x's right is not nil[T]
    if (x->right_child == gNil) {
        if (DEBUG) printf("x's right is null, no need to do left rotate\n");
        return;
    }

    treenode_t *y = x->right_child; // Set y
    x->right_child = y->left_child; // Turn y's left subtree into x's right subtree
    
    if (y->left_child != gNil) {
        y->left_child->parent = x;
    }
    y->parent = x->parent;

    if (x->parent == gNil) {
        T->root = y;
    } else {
        if (x == x->parent->left_child) {
            x->parent->left_child = y;
        } else {
            x->parent->right_child = y;
        }
    } 
    y->left_child = x;
    x->parent = y;

}

void tree_right_rotate(tree_p T, treenode_t * y) {
    //    if (DEBUG) printf("tree right rotate with node:%p\n", y);
    
    if (!T || !y || y == gNil) 
        return;

    // Make sure y's left is not nil[T]
    if (y->left_child == gNil) {
        if (DEBUG) printf("y's left is null, no need to do left rotate\n");
        return;
    }

    treenode_t *x = y->left_child;
    y->left_child = x->right_child; // Turn x's right tree to y's left tree
    
    if (x->right_child != gNil) {
        x->right_child->parent = y;
    }
    x->parent = y->parent;

    if (x->parent == gNil) {
        T->root = x;
    } else {
        if (y == y->parent->left_child) {
            y->parent->left_child = x;
        } else {
            y->parent->right_child = x;
        }
    }

    x->right_child = y;
    y->parent = x;

    //    if (DEBUG) printf("endof tree right rotate with node:%p\n", x);
}

void RBTree_insert(tree_t *T, treenode_t *z){
    if (!T || !z) {
        return;
    }
    if (DEBUG) printf("RB insert %ld\n", z->key);

    treenode_t *y = gNil;
    treenode_t *x = T->root;
    
    // Track the z's position and it's parent:y
    while (x != gNil) {
        y = x;
        if (z->key < x->key) {
            x = x->left_child;
        } else {
            x = x->right_child;
        }
    }
    if (DEBUG) printf("find pos: x = %p, key=%ld\n", y, z->key);

    // Set the z's field.
    z->parent = y;
    if (y == gNil) {
        T->root = z;
    } else {
        if (z->key < y->key) {
            y->left_child = z;
        } else {
            y->right_child = z;
        }
    }

    z->left_child = gNil;
    z->right_child = gNil;
    z->color = RED;

    RBTree_insert_fixup(T, z);
}

void RBTree_insert_fixup(tree_t *T, treenode_t *z) {
    treenode_t *y = gNil;

    while (z->parent->color == RED) {
        if (DEBUG) {
            printf (" z = %ld, z->parent->key = %ld\n", z->key, z->parent->key);
        }
        if (z->parent == z->parent->parent->left_child) {
            y = z->parent->parent->right_child;
            if (y->color == RED) { // case 1
                if (DEBUG) printf("case 1\n");
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right_child) { // case 2
                    if (DEBUG) printf("case 2\n");
                    z = z->parent;
                    tree_left_rotate(T, z);
                }
                if (DEBUG) printf("case 3\n");
                z->parent->color = BLACK;                // case 3
                z->parent->parent->color = RED;          // case 3
                tree_right_rotate(T, z->parent->parent); // case 3
            }
        } else {
            y = z->parent->parent->left_child;
            if (y->color == RED) { // case 4
                if (DEBUG) printf("case 4\n");
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left_child) { // case 5
                    if (DEBUG) printf("case 5\n");
                    z = z->parent;
                    tree_right_rotate(T, z);
                }
                if (DEBUG) printf("case 6\n");
                z->parent->color = BLACK;                // case 6
                z->parent->parent->color = RED;          // case 6
                tree_left_rotate(T, z->parent->parent); // case 6
            }
        }
    }
    T->root->color = BLACK;
}

treenode_t * RBTree_delete(tree_t *T, treenode_t *z){
    if (z == NULL || z == gNil) {
        return NULL;
    }
    
    if (DEBUG) printf("\nRBTree_delete\n");

    treenode_t * y = gNil;
    treenode_t * x = gNil;

    // Find the place (y) to delete:
    if ((z->left_child == gNil) || (z->right_child == gNil)) {
        y = z;
    } else {
        y = tree_successor(z);
    }
    
    // Set the node (x) next to y:
    if (y->left_child != gNil) {
        x = y->left_child;
    } else {
        x = y->right_child;
    }
    
    // skip y
    x->parent = y->parent;

    if (y->parent == gNil) {
        T->root = x;
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
 
    if (y->color == BLACK) {
        RBTree_delete_fixup(T, x);
    }
    
    return y;

}


void RBTree_delete_fixup(tree_t *T, treenode_t *x) {
    treenode_t * w = gNil;

    while (x != T->root && x->color == BLACK) {
        if (x == x->parent->left_child) {
            w = x->parent->right_child;
            
            if (w->color == RED) {
                //case 1
                w->color = BLACK;
                tree_left_rotate(T, x->parent);
                w = x->parent->right_child;
            }
            if (w->left_child->color == BLACK && w->right_child->color == BLACK) {
                //case 2
                w->color = RED;
                x = x->parent;
            } else {
                if ( w->right_child->color == BLACK) { //w->left_child->color == RED
                    //case 3
                    w->left_child->color = BLACK;
                    w->color= RED;
                    tree_right_rotate(T, w);
                    w=x->parent->right_child; // update new w
                }
                //case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right_child->color = BLACK;
                tree_left_rotate(T, x->parent);
                x = T->root;
            }

        } else { // x == x->parent->right_child
            w = x->parent->left_child;
            
            if (w->color == RED) {
                //case 5
                w->color = BLACK;
                tree_right_rotate(T, x->parent);
                w = x->parent->left_child;
            }
            if (w->right_child->color == BLACK && w->left_child->color == BLACK) {
                //case 2
                w->color = RED;
                x = x->parent;
            } else {
                if ( w->left_child->color == BLACK) { //w->right_child->color == RED
                    //case 3
                    w->right_child->color = BLACK;
                    w->color= RED;
                    tree_left_rotate(T, w);
                    w=x->parent->left_child; // update new w
                }
                //case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left_child->color = BLACK;
                tree_right_rotate(T, x->parent);
                x = T->root;
            }
        }
        x->color = BLACK;
    }
}

treenode_t * get_nil_node() {
    return gNil;
}


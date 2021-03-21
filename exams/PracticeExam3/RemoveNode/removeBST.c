#include <stdio.h>
#include <stdlib.h> 
#include<math.h> 
#include <assert.h>

#define TYPE double

struct BST {
   struct Node *root;
   int size;
};

struct Node{
   TYPE val;
   struct Node *left;
   struct Node *right;
};

/* interface for a BST, implemented in tree form */
TYPE getMinBST(struct BST * tree);
int containsBST(struct BST * tree, TYPE val);
int _containsNode(struct Node* current, TYPE val);
void removeBST(struct BST * tree, TYPE e);
struct Node * _removeNode(struct Node* current, TYPE e);

TYPE _leftMost(struct Node * current);
struct Node * _removeLeftmost(struct Node * current);

int main(){
    struct BSTree tree;
    initBSTree(&tree);
    /*tree from figure in earlier slides */ 
    
    
    printf("\n"); 
    return 0;
}


/* Find and return the minimum element of a given BST
   input:  tree -- pointer to BST
   output: return the minimum value found in BST
   pre-conditions: BST is well initialized, and not empty
*/
TYPE getMinBST(struct BST * tree){
   assert(tree && tree->size > 0);

   /* FIX ME */ 
   struct Node * temp = tree->root;
   TYPE minimum;

   while (temp->left != 0) {
       /* recursively call, traverse the bst to find the least value, starting from the root */

       /* we know a bst has it's least value at the left most element */

       /* keep traversing until the left is hit */
       temp = temp->left;
   }

   minimum = temp->val;

   /* return the minimum value in bst */
   return minimum;
}



int containsBST(struct BST * tree, TYPE val) {
    assert(tree);
    if (tree->root)
        return _containsNode(tree->root, val);
    else
        return 0;
}

int _containsNode(struct Node * current, TYPE val) {
    int flag = 0;

    if (!current) return flag;

    if (val == current->val) {
        flag = 1;
    }
    else if ((val < current->val) && current->left) {
        printf("Looking at LEFT of Node %f for a Node = %f \n", current->val, val);
        flag = _containsNode(current->left, val);
    }
    else if (current->right) {
        printf("Looking at RIGHT of Node %f for a Node = %f \n", current->val, val);
        flag = _containsNode(current->right, val);
    }

    return flag;
}

/* Remove the minimum element of a given BST
   input:  tree -- pointer to BST
   pre-conditions: BST is well initialized, and not empty
*/
void removeBST(struct BST * tree, TYPE e){
   assert(tree && tree->size > 0);
    /* FIX ME */ 
    if (containsBST(tree, e)) {
        tree->root = _removeNode(tree->root, e);
        tree->size--;
    }
    
}

/* helper function to return the element at the leftmost of the tree */
struct Node * _removeNode(struct Node * current, TYPE e) {
    struct Node * temp; 
    assert(current);

    /* handle the case where the val is e */
    if (current->val == e) {
        /* Found it, remove it */
        if (current->right == NULL) {
            /* special case: no right child */
            temp = current->right;
            free(current);
            return temp;
        } else {
            /* memorize the value of the leftmost descendant */
            current->val = _leftMost(current->right);
            /* remove the leftmost desc. of the right child */
            current->right = _removeLeftmost(current->right);
        }
        
    } else {
        /* not found, so recursive call */
        if (e < current->val) {
            current->left = _removeNode(current->left, e);

        } else {
            current->right = _removeNode(current->right, e);
        }
        return current;
    }

    return temp;
    
}

TYPE _leftMost(struct Node * current) {
    while (current->left != 0) {
        current = current->left;
    }
    return current->val;
}

struct Node * _removeLeftmost(struct Node * current) {
    struct Node *temp;
    if (current->left != 0) {
        current->left = _removeLeftmost(current->left);
        return current;
    } else {
        temp = current->right;
        free(current);
        return temp;
    }
    
}


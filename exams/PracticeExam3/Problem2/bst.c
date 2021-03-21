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
void removeMinBST(struct BST * tree);
struct Node * _removeLeftMost(struct Node* current);


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

/* Remove the minimum element of a given BST
   input:  tree -- pointer to BST
   pre-conditions: BST is well initialized, and not empty
*/
void removeMinBST(struct BST * tree){
   assert(tree && tree->size > 0);
    /* FIX ME */ 
    tree->root = _removeLeftMost(tree->root);
    
}

/* helper function to return the element at the leftmost of the tree */
struct Node * _removeLeftMost(struct Node * current) {
    struct Node * temp; 

    /* handle the case where the left subtree is null */
    if (temp->left == 0) {
        /* continue going to the right, assign current to the right, free it and return temp */
        current = current->right;
        free(current);
        return temp;
    } else {
        current->left = _removeLeftMost(current->left);
        return current;
    }
    
}
/* ENTER YOUR FIRST AND LAST NAME: Andrea Tongsak   */
/* TO COMPILE:  gcc -Wall -ansi -o program FinalProblem1.c */
/* TO RUN, ENTER YOUR INPUT FILE NAME:  ./program  */

/* HEAPS */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define LT(a,b) (a<b)
#define EQ(a,b) (a==b)
#define ADIFF(a,b) (abs(a - b))

/* Structs */

#define TYPE double

struct Node {
  TYPE   val;         /*node’s value*/
  struct Node *left;  /*pointer to the left child*/
  struct Node *right; /*pointer to the right child*/
};

struct Tree {
   struct Node *root;
    int size; 
};

void printBottomUp(struct Node* node);
void printLevel (struct Node* root, int level);
int getHeight(struct Node* node);

/* Breadth-last traversal of a binary tree
    - Input: tree = pointer to a binary tree.
    - Pre-conditions: tree was initialized well and exists in memory, but may be empty.
    - Constraints: time complexity <= O(n); no new data structures allowed,
                   no new memory locations can be allocated, except for a couple of integers
*/
void printBreadthLastBinaryTree(struct Tree *tree){
   assert(tree);
    /* FIX ME */ 
    if (tree->size == 0) {
        return;
    }

    printBottomUp(tree->root);

}

/* Go backwards from a node */
void printBottomUp(struct Node* node) {
    int i;
    int height = getHeight(node);

    for (i = height; i >= 1; i--) {
        printLevel(node, i);
    }
}

/* Prints out the root */
void printLevel (struct Node* root, int level){
    if (root == NULL) {
        return;
    }

    if (level == 1) {
        printf("%f ", root->val);
        
    } else if (level > 1) {
        printf("\n");
        printLevel(root->left, level-1);
        printLevel(root->right, level-1);
    }
}

int getHeight(struct Node* node) {
    if (node == NULL) {
        return 0;
    } else {
        int lh = getHeight(node->left);
        int rh = getHeight(node->right);

        /* use the larger height */
        if (rh > lh) {
            rh = rh+1;
            return rh;
        } else {
            lh = lh+1;
            return lh;
        }
    }
}



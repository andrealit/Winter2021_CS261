#include <stdio.h>
#include <stdlib.h> 
#include<math.h> 
#include <assert.h>

#define TYPE int

struct BST {
   struct Node *root;
   int size;
};


struct Node{
   TYPE val;
   struct Node *left;
   struct Node *right;
};

void _sumTreeNodes(struct Node *temp, TYPE * sum);
void addTree(struct BST * tree, TYPE val);
struct Node * _addNode(struct Node * current, TYPE val);
void initTree(struct BST *tree);

void sumTree(struct BST *tree, TYPE *sum){
    _sumTreeNodes(tree->root, sum);
}


/* -------- An excerpt of the main function ------------ */
int main(){

   struct BST myTree;
   int sum = 0;

   /* INITIALIZE THE TREE BEFORE ADDING! */
   initTree(&myTree);
   addTree(&myTree, 5);
   addTree(&myTree, 1);
   addTree(&myTree, 10);
   sumTree(&myTree, &sum);
   printf("Final sum = %d\n", sum);


   return 1;

}

void initTree(struct BST * tree) {
   assert(tree != 0);
   tree->root = 0;
   tree->size = 0;
}

void addTree(struct BST * tree, TYPE val) {

   assert(tree);

   /* add elements to a tree */
   /* allocate memory to the node */
   tree->root = _addNode(tree->root, val);

   tree->size++;
   
}


struct Node * _addNode(struct Node * current, TYPE val) {
   /* if the spot is empty, fill it */
   if (current == 0) {
      /* allocate memory */
      struct Node * new = (struct Node *) malloc (sizeof(struct Node));

      new->val = val;
      new->left = 0;
      new->right = 0;

      return new;
   }

   /* else if the size is already filled, this will find the empty spot */
   else {

      /* if less than, place to left of the tree (recursive call) */
      if (val < current->val) {
         current->left = _addNode(current->left, val); 
      }

      /* if greater than or equal, place to the right of the tree (recursive call) */
      else {
         current->right = _addNode(current->right, val);
      }
      
   }

   return current;
}

/* Recursive function for computing and printing
   a total sum of nodes in the ascending order
   input: node -- pointer to a node in BST
          sum -- the total sum of all nodes visited in BST
                 before node
Note that sum is passed by reference
*/
void _sumTreeNodes(struct Node *node, TYPE *sum){
/* FIX ME */

    /* Two cases */
    /* recursive call until the tree is summed up */

    if (node != 0) {

        /* this pointer (*) can be the dereference operator or part of the pointer declaration syntax */

        /* the result of printing running sums should be an ascending sequence. */
        /* therefore, it must go to the smaller child */
        _sumTreeNodes(node->left, sum);

        /* add the value */
        *sum += node->val;

        printf("Print the value of the sum: %d\n", *sum);

        /* call the next node for the value */
        _sumTreeNodes(node->right, sum);
    }


}

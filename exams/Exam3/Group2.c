/* ENTER YOUR FIRST AND LAST NAME:  Andrea Tongsak    */
/* TO COMPILE:  gcc -Wall -ansi -o program Group2.c */
/* TO RUN, ENTER YOUR INPUT FILE NAME:  ./program input1.txt  */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int
#define EQ(a,b) (a==b)
#define LT(a,b) (a<b)

# define TYPE int
struct Node {
  TYPE   val;
  struct Node *left;
  struct Node *right;
};

struct BST{
  struct Node *root;
  int size;
};

/****************************************/
/* Interface of BST */
void addBST(struct BST *tree, TYPE val);
struct Node * _addNode(struct Node * node, TYPE val);
void print_inorder(struct Node *node);
struct Node* _removeNode(struct Node *node, TYPE val);
TYPE _leftMost(struct Node *node);
struct Node *_removeLeftmost(struct Node *node);
int _containsNode(struct Node * current, TYPE val);
void removeAllRepsBST(struct BST * tree);
void traversePreorder(struct Node * node);
void removeAllRepsNode(struct Node * node, int rep);


/****************************************/
int main (int argc, const char * argv[]) {
   const char *filename;
   FILE *fileptr;
   struct BST *tree = (struct BST *) malloc(sizeof(struct BST));
   assert(tree);
   tree->root = 0;
   tree->size = 0;
   int value;

    if(argc == 2)
        filename = argv[1];
    else
        filename = "input.txt"; /* default file name */
    fileptr = fopen(filename,"r");

    printf("Adding nodes to BST with values from the file: %s\n", filename);
    while (!feof(fileptr)) {
      fscanf(fileptr, "%d", &value);
      addBST(tree, value);
    }
    printf("\nThere are %d nodes in input BST.\n", tree->size);
    printf("Their values printed in-order are:\n");
    print_inorder(tree->root);
    printf("\n");

    removeAllRepsBST(tree);

    printf("\nThere are %d nodes in BST after removing repeating nodes.\n", tree->size);
    printf("Their values printed in-order are:\n");
    print_inorder(tree->root);
    printf("\n");

    return 0;
}






/****************************************/
/* Add a new node to BST */
/*
    Input: tree -- pointer to BST,
           val -- value to be added to BST
    pre-conditions: BST was initialized well
*/
void addBST(struct BST *tree, TYPE val) {
   assert(tree);
   tree->root = _addNode(tree->root, val);
   tree->size++;
}

/****************************************/
/* Auxiliary recursive function to add a new node to BST */
/*
    Input: current -- pointer to a node in BST,
           val -- value to be added to BST
    pre-conditions: BST was initialized well
*/
struct Node * _addNode(struct Node * current, TYPE val){
   if (current == 0)
   {   /* we hit the leaf level */
       /*make a new node, and return new*/
       struct Node * new = (struct Node *) malloc(sizeof(struct Node));
       assert(new != 0);

      new->val = val;
      new->left = new->right = 0;
      return new;
   }
   else{ /* recursive calls left or right */
      if (val < current->val)
         current->left = _addNode(current->left, val);
      else
         current->right = _addNode(current->right, val);
   }
   return current;
}

/****************************************/
void print_inorder(struct Node *node) {
   if (node != 0){
      print_inorder(node->left);
      printf("%d ",node->val);
      print_inorder(node->right);
   }
}


/****************************************/
/* Recursively finds and removes a node 
   of BST if it has a given value
   Input: node -- pointer to a node in BST
          val -- value that should be removed
   Output: the function returns the node's pointer
   Pre-condition: node is not a NULL pointer
*/
struct Node* _removeNode(struct Node *node, TYPE val){
   struct Node* temp;
   if(EQ(node->val, val)){
       if (node->right == NULL){
          /* no right child */
          temp = node->left;
          free(node);
          return temp; 
       }
       else{
          /* right child exists */
          /* copy the value of the leftmost descendant*/
          node->val = _leftMost(node->right);
          /* remove leftmost desc. of right child */
          node->right = _removeLeftmost(node->right);
       }
    }
    else{ /* recursive search */
       if( val < node->val)
          node->left = _removeNode(node->left, val);
       else 
          node->right = _removeNode(node->right, val);

    }
    return node;
}



/****************************************/
/*Finds and returns a value of the leftmost descendant of a node
  Input: node -- pointer to a node
  Output: return the value of the node's leftmost descendant
*/
TYPE _leftMost(struct Node *node) { 
   while(node->left != 0) 
      node = node->left; 
   return node->val; 
} 

/****************************************/
/* Finds and removes the leftmost descendant of a node
  Input: node -- pointer to a node
  Output: the function returns the node's pointer
*/
struct Node *_removeLeftmost(struct Node *node) { 
   struct Node *temp; 
   if(node->left != 0){ 
      node->left = _removeLeftmost(node->left); 
      return node; 
   } 
   temp = node->right; 
   free(node);
   return temp; 
}

/****************************************/
/* Finds recursively a given value in
   a BST subtree rooted at a specified node.
   Input: current -- pointer to a root node of a subtree
   Output: returns 1 for found; or 0 for not found
   Pre-conditions: current is not NULL
*/
int _containsNode(struct Node * current, TYPE val){

  /* FIX ME */
  int flag = 0;
  if (!current) return flag;

  if (val == current->val) {
      flag = 1;
  }
  else if ((val < current->val) && current->left) {
      flag = _containsNode(current->left, val);
  }
  else if (current->right) {
    flag = _containsNode(current->right, val);
  }
  return flag;
}


/****************************************/
/* Remove all repeating nodes of BST
   Input: tree -- pointer to BST
   Constraint: complexity O(n), no new memory allocation
   Requirement: maintain the correct tree size
*/
void removeAllRepsBST(struct BST * tree){ 
   assert(tree); 

   /* FIX ME */
   struct Node* current = tree->root;
   struct Node* temp;

   


   if (current == 0) {
        return;
    }

    /* 1. start traversing the tree inorder */
    traversePreorder(current);

    /* 2. at each node, do a binary search on the subtree for the key value at the node */

    while (current) {

        /* if the key value is found at the tree, then call remove(key) and restart step 2*/
        if (EQ(current->val, current->right->val)) {
            /* temp = current->right->right; */
            /* current = _removeNode(current->right, current->val); */
           /* current->right = temp; */
           /*  current->right = _removeNode(current->right, temp->val); */

            /* decrement size of tree */
            tree->size--;

        }

        /* if the key is not found, return to step 1 */
        current = current->right;
        
    }
    /* repeat step 2 until key is not found. return to step 1*/

 
}

void traversePreorder(struct Node* current) {
    if (current == 0) {
        return;
    }

    

    /* removes all repetition nodes at the current */
    removeAllRepsNode(current, 0);

    /* goes to the left of the tree */
    traversePreorder(current->left);

    traversePreorder(current->right);
}

void removeAllRepsNode(struct Node* current, int numRep) {

    struct Node * temp;

    while (current) {

        /* if the key value is found at the tree, then call remove(key) and restart step 2*/
        if (EQ(current->val, current->right->val)) {
            current = _removeNode(current, current->val);
            numRep++;

        } /* handle the case where the value is the leftmost descendant of the right node */
        else {
            /* go to the left most descendant of the node */
            if (EQ(current->val, _leftMost(current))) {
                current = _removeNode(_leftMost(current), current->val);
            }
        }

        /* if the key is not found, continue traversing to the right */
        current = current->right;   
    }
}




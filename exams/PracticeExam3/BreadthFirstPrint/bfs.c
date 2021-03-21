/* TO COMPILE: gcc -Wall -ansi -o program bfs.c */

#include <stdio.h>
#include <stdlib.h> 
#include<math.h> 
#include <assert.h>

#define ElType double 

struct BSTree {
    struct BSTNode *root;
    int size; 
};

struct BSTNode { 
    ElType val;
    struct BSTNode *left; 
    struct BSTNode *right; 
    int processed;
};

struct link {
    struct BSTNode * val;
    struct link * next; 
};

struct listStack { 
    struct link *firstLink;
};


/* Interface for stack, implemented as linked list */
void initListStack (struct listStack * s);
void pushListStack (struct listStack *s, struct BSTNode * e); 
struct BSTNode * topListStack(struct listStack *s);
void popListStack (struct listStack *s);
int isEmptyListStack(struct listStack *s);

/* Interface for Binary search Tree*/
void initBSTree(struct BSTree *tree);
void addBSTree(struct BSTree *tree, ElType val);
struct BSTNode * _addNode(struct BSTNode * current, ElType val); 
void BreadthFirstPrint(struct BSTree *tree);
int _containsNode(struct BSTNode * node, ElType val);
int _containsBSTree(struct BSTree * tree, ElType val);

ElType searchVal = 69.0;

int main(){
    struct BSTree tree;
    initBSTree(&tree);
    /*tree from figure in earlier slides */ 
    addBSTree(&tree, 32.0); 
    addBSTree(&tree, 19.0); 
    addBSTree(&tree, 9.0); 
    addBSTree(&tree, 14.0); 
    addBSTree(&tree, 8.0); 
    addBSTree(&tree, 4.0); 
    addBSTree(&tree, 13.0); 
    addBSTree(&tree, 99.0); 
    addBSTree(&tree, 69.0); 
    addBSTree(&tree, 72.0);
    printf("DFS Print: \n");
    BreadthFirstPrint(&tree);

    printf("TESTING: containsBST \n");
    printf("Looking for Node with value = %f \n", searchVal);
   
    if (_containsBSTree(&tree, searchVal) == 1) {
        printf("> FOUND the Node with value = %f \n", searchVal);
    }
    else {
        printf("> Node with value = %f NOT FOUND\n", searchVal);
    }

    printf("\n"); 
    return 0;
}

/* Initialize stack, implemented as a list */ 
void initListStack (struct listStack * s) {
    s->firstLink = 0; 
}

/* returns 1 if the stack is empty, otherwise it returns 0*/ 
int isEmptyListStack(struct listStack *s) {
    return s->firstLink == 0; 
}

/* Returns the node at the top of the stack, implemented as a list */ 
struct BSTNode * topListStack(struct listStack *s) {
    assert (! isEmptyListStack(s));
    return s->firstLink->val; 
}

/* Adds a node to the front of the stack, implemented as a list */ 
void pushListStack (struct listStack *s, struct BSTNode * e) {
    struct link * newLink = (struct link *) malloc(sizeof(struct link)); 
    assert (newLink != 0);
    newLink->val = e;
    newLink->next = s->firstLink;
    s->firstLink = newLink; 
}

/* removes a node from the top of the stack*/ 
void popListStack (struct listStack *s) {
    struct link * lnk = s->firstLink; 
    assert (! isEmptyListStack(s)); 
    s->firstLink = lnk->next; 
    free(lnk);
}

/* Initialize binary search tree*/ 
void initBSTree(struct BSTree *tree){
    assert(tree!=0); 
    tree->root = 0; 
    tree->size = 0;
}

/* Adds a value to the binary search tree*/
void addBSTree(struct BSTree *tree, ElType val){
    assert(tree);
    tree->root = _addNode(tree->root, val); 
    tree->size++;
}

/* adds a value to the binary search tree, recursively */
struct BSTNode * _addNode(struct BSTNode * current, ElType val){

    /* FIX ME */
    if (current == 0) {
        /* allocate memory */
        struct BSTNode* new = (struct BSTNode*)malloc(sizeof(struct BSTNode));

        /* populate each value inside the node */
        new->val = val;
        new->processed = 0;
        new->left = new->right = 0;

        /* IMPORTANT, return the new */
        return new;
    }
    else {
        /* case where the node is less than the current */
        if (val < current->val) {
            current->left = _addNode(current->left, val);

        } else {
            /* case where the node is less than the current */
            current->right = _addNode(current->right, val);

        }
    }

    return current;
}

int _containsBSTree(struct BSTree* tree, ElType val) {

    assert(tree);
    if (tree->root) {
        return _containsNode(tree->root, val);
    } else {
        return 0;
    }

}


/* Displays whether or not the node is within the tree, returns 1 for true, 0 for no */
int _containsNode(struct BSTNode* current, ElType val) {
    /* flag is 0 for outcome of search */
    int flag = 0;

    /* stopping criterion!! */
    if (!current) {
        return flag;
    }

    /* if the values are equal to each other */
    if (val == current->val) {
        flag = 1;
    }

    /* Check if the node is in the left first */
    else if ((val < current->val) && current->left) {
        flag = _containsNode(current->left, val); 
    }

    /* Check if the node is in the right */
    else if (current->right) {
        flag = _containsNode(current->right, val);
    }

    /* Starts for inorder function */

    return flag;
}

/* Prints out node values of a binary search tree in depth first search, using a stack */
/* Input: binary search tree */
void BreadthFirstPrint(struct BSTree *tree){
    struct BSTNode ** queue = (struct BSTNode **) malloc (100 * sizeof(struct BSTNode));
    struct BSTNode *current = tree->root; 
    /*FIX ME*/

    /* Breadth first search requires a queue to be implemented along with it */
    
    /* store the indexes of the tree */
    int front = 0;
    int backIdx = 0;
    int i;

    /* assign the first element in the queue */
    queue[0] = current;
    backIdx++;

    /* continue printing out the tree, popping it from the queue */
    while (front < backIdx) {
        current = queue[front];
        front++;

        /* condition where the left element is present */
        if (current->left != 0) {
            /* add it to the queue, and increase the size */
            queue[backIdx] = current->left;
            backIdx++;
        }

        /* condition where the right element is present */
        if (current->right != 0) {
            /* add it to the queue, and increase the size */
            queue[backIdx] = current->right;
            backIdx++;
        }
    }

    for (i = 0; i < backIdx; i++) {
        printf("%f, ", queue[backIdx]->val);
    }

    free(queue);

    return;
}
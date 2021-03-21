#include <stdio.h>
#include <stdlib.h> 
#include<math.h> 
#include <assert.h>

#define TYPE (struct Node *)
#define ElType double

struct BST {
   struct Node *root;
   int size;
};

struct Node{
   ElType val;
   struct Node *left;
   struct Node *right;
};

struct listQueue{
   struct Link *firstLink;
   struct Link *lastLink;
};

struct Link {
   TYPE val;
   struct Link * next;
};

void initListQueue(struct listQueue *q);
void addBackListQueue(struct listQueue *q, TYPE e);
int isEmptyListQueue(struct listQueue *q);
TYPE getFrontListQueue(struct listQueue *q);
void removeFrontListQueue (struct listQueue *q);
int equalsBST(struct listQueue *q);
int _isEqual(struct Node * node1, struct Node * node2);

int equalsBSTStack (struct BST *tree1, struct BST * tree2);

void initListQueue (struct listQueue *q) {
   struct link *lnk = (struct link *) malloc(sizeof(struct link));
   assert(lnk != 0); /* lnk is the sentinel */
   lnk->next = 0; q->firstLink = q->lastLink = lnk;
}

void addBackListQueue (struct listQueue *q, TYPE e) {
   struct link *lnk = (struct link *) malloc(sizeof(struct slink));
   assert(lnk != 0);
   lnk->val = e; lnk->next = 0;
   q->lastLink->next = lnk; q->lastLink = lnk;
}

int isEmptyListQueue (struct listQueue *q) {
   return q->firstLink == q->lastLink;
}

TYPE getFrontListQueue (struct listQueue *q) {
   assert (!isEmptyListQueue(q));
   return q->firstLink->next->val;
}

void removeFrontListQueue (struct listQueue *q) {
   struct link * lnk = q->firstLink->next;
   assert ( ! isEmptyListQueue(q));
   q->firstLink->next = lnk->next;
   if(q->firstLink->next == 0)
      q->lastLink = q->firstLink;
   free (lnk);
}

/* Equal BST */
int equalsBST(struct BST * tree1, struct BST * tree2){
   if (tree1->size != tree2->size) {
      return 0;
   }

   return _isEqual(tree1->root, tree2->root);

}


int _isEqual(struct Node * node1, struct Node * node2) {

   /* recursive method */
   if (node1->val == 0 && node2->val == 0) {
      return 1;
   }

   if (node1->val != node2->val) {
      return 0;
   } 

   return (_isEqual(node1->left, node2->left) && _isEqual(node1->right, node2->right));

}

int equalsBSTStack (struct BST *tree1, struct BST * tree2) {
   struct listQueue *q1, *q2;
   struct Node *cur1 = tree1->root, *cur2 = tree2->root;
   initListQueue(q1);
   initListQueue(q2);
   addBackListQueue(q1, cur1);
   addBackListQueue(q2, cur2);

   while(!isEmptyListQueue(q1) && !isEmptyListQueue(q2)){
      cur1 = getFrontListQueue(q1);
      cur2 = getFrontListQueue(q2);
      if (cur1->val != cur2->val)
            return 0;
      removeFrontListQueue(q1);
      removeFrontListQueue(q2);
      if(cur1->left != 0)
         addBackListQueue (q1, cur1->left);
      if(cur1->right != 0) {
         addBackListQueue (q1, cur1->right);
      }

      if(cur2->left != 0) {
         addBackListQueue (q2, cur2->left);
      }
         
      if(cur2->right != 0) {
         addBackListQueue (q2, cur2->right);
      }
   }
   return 1; 


}

/* ENTER YOUR FIRST AND LAST NAME: Andrea Tongsak    */

/* TO COMPILE:  gcc -Wall -ansi -o program Group2.c */

/* TO RUN, ENTER SIZE OF SORTED BAG */
/* FOR EXAMPLE:  ./program 30 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int
#define EQ(a,b) (a == b)
#define LT(a,b) (a < b)

struct DLink {
   TYPE value;
   struct DLink * next;
   struct DLink * prev;
};

struct DList {
   int size;
   struct DLink * frontSentinel;
   struct DLink * backSentinel;
};

/*----------------------------------------------*/
/*Interface for doubly linked list*/
void initDList (struct DList *dl);
void addBackDList (struct DList *dl, TYPE val);
void _addDLink (struct DList *dl, struct DLink *lnk, TYPE val);
void _printDList(struct DList *dl);

/*----------------------------------------------*/
/*Interface for Bag implemented as doubly linked list*/
void sortBag(struct DList *bag);
void removeRepsBag(struct DList *bag);

void removeDList (struct DList *ls, struct DLink *lnk);

/*----------------------------------------------*/
int main(int argc, char **argv)
{
   /* Bag implemented as a doubly linked list */
   struct DList *bag = (struct DList *) malloc(sizeof(struct DList));
   assert(bag);

   int i;
   TYPE val;
   int  size = atoi(argv[1]); /* input argument is the size of Bag */

   assert(size >= 0);

   srand(time(NULL)); /*initialize random generator*/

   initDList(bag); /*initialize Bag*/

   for(i=1; i<=size; i++){
      val = (TYPE) rand() % 10;
      addBackDList(bag, val); /*add val to back of Bag*/
   }
   sortBag(bag);
   printf("\nSorted Bag:\n");
   _printDList(bag); /*print Bag */

   removeRepsBag(bag); /*remove all repetitions of elements in Sorted Bag*/

   printf("\nSorted Bag after removing repetitions:\n");
   _printDList(bag); /*print Bag*/

   return 0;
}


/*============= IMPLEMENTATION OF BAG =============*/
/*----------------------------------------------*/
/*Remove repetitions of elements from Sorted Bag.
  Input: bag -- pointer to Bag implemented as a doubly linked list.
  Output: void
  Pre-condition: The input bag is guaranteed to be sorted.
  Memory constraint: Except for a few local variables, no new memory can be allocated.
  Complexity constraint: no higher than O(n).
*/
void removeRepsBag (struct DList *bag){
   assert(bag);

   /*FIX ME*/
   struct DLink * lnk_rmv;
   struct DLink * current = bag->frontSentinel->next;

   /* Look for repetition and delete if there is none */

   while (current != bag->backSentinel) {

       /* Save the first element */
       if (EQ(current->value, current->next->value)) {
           /* removeDList(bag, current); */
           lnk_rmv = current->next;
           lnk_rmv->prev->next = lnk_rmv->next;
           lnk_rmv->next->prev = lnk_rmv->prev;
           
           free(lnk_rmv);
       } else {
           /* Go to the next element */
           current = current->next;

       }
       
   }

}

/*----------------------------------------------*/
/* Sort Bag in the ascending order.
   Input: pointer to Bag implemented as doubly linked list
   Output: void */
void  sortBag(struct DList *b){
   assert(b && (b->size > 0));
   struct DLink *lnk1 = b->frontSentinel->next; /* for scanning the list */
   struct DLink *lnk2; /* for scanning the list from lnk1 until the end */
   TYPE tmp; /* auxiliary variable for swapping */
   while (lnk1 != b->backSentinel->prev) {
      lnk2 = lnk1->next;
      while (lnk2 != b->backSentinel) {
         if (LT(lnk2->value, lnk1->value)){ /* test the ordering */
            /* swap the values */
            tmp = lnk1->value;
            lnk1->value = lnk2->value;
            lnk2->value = tmp;
         }
         lnk2 = lnk2->next;
      }
      lnk1 = lnk1->next;
    }
}


/*==== IMPLEMENTATION OF DOUBLY LINKED LIST ====*/
/*----------------------------------------------*/
/*Initialize doubly linked list*/
void initDList (struct DList *dl) {
   dl->frontSentinel = (struct DLink *) malloc(sizeof(struct DLink));
   assert(dl->frontSentinel != 0);
   dl->backSentinel = (struct DLink *) malloc(sizeof(struct DLink));
   assert(dl->backSentinel);
   dl->frontSentinel->next = dl->backSentinel;
   dl->backSentinel->prev = dl->frontSentinel;
   dl->size = 0;
}
/*----------------------------------------------*/
/*Add val to the back of a doubly linked list*/
void addBackDList (struct DList *dl, TYPE val)
{ _addDLink(dl, dl->backSentinel, val); }
/*----------------------------------------------*/
/*Add val before lnk to a doubly linked list*/
void _addDLink (struct DList *dl, struct DLink *lnk, TYPE val) {
   assert(dl && lnk);
   struct DLink *new = (struct DLink *) malloc(sizeof(struct DLink));
   assert(new);
   new->value = val;
   new->next = lnk;
   new->prev = lnk->prev;
   lnk->prev->next = new;
   lnk->prev = new;
   dl->size++;
}
/*----------------------------------------------*/
/*Print doubly linked list*/
void _printDList(struct DList *dl){
   assert(dl);
   struct DLink *current = dl->frontSentinel->next;
   printf("\n");
   while (current != dl->backSentinel){
      printf("%d ", current->value);
      current = current->next;
   }
   printf("\n");
}

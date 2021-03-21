/* ENTER YOUR FIRST AND LAST NAME:      */

/* TO COMPILE, ENTER:  gcc -Wall -ansi -o prog Deque.c */

/* TO RUN, ENTER PROGRAM ARGUMENTS: CAPACITY, SIZE, FLAG */
/* FOR EXAMPLE:  ./prog 10 4 -1*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int
#define EQ(a,b) (a == b)  

struct Deque{
    TYPE *data; 
    int size; /* number of elements in data */
    int capacity; /* memory capacity of the deque */
    int front; /* index of the front end of deque  */
};

/*----------------------------------------------*/
void initDeque(struct Deque * dq, int cap);
void addFrontDeque(struct Deque *dq, TYPE val);
void printDeque(struct Deque *dq);
void removeBackAllDeque(struct Deque *dq, int flag);
/*----------------------------------------------*/
void _doubleCapacityDeque (struct Deque *dq);

void removeAtDeque(struct Deque *dq, int idx);


/*----------------------------------------------*/
int main(int argc, char **argv){
   struct Deque dq;
   int i;
   TYPE val;
   int  capacity = atoi(argv[1]);
   int  size = atoi(argv[2]);
   int flag = atoi(argv[3]);

   assert(capacity > 0 && size >= 0);

   srand(time(NULL)); /*initialize random generator*/

   initDeque(&dq, capacity); /*initialize Deque*/

   for(i=1; i<=size; i++)
   {
      val = (TYPE) rand() % 5;
      addFrontDeque(&dq, val); /*add val to Deque*/
   }
 
   printf("Deque before remove:\n");
   printDeque(&dq); /*print all elements*/

   removeBackAllDeque(&dq, flag);

   printf("Deque after remove:\n");
   printDeque(&dq); /*print all elements*/

   return 0;
}


/*----------------------------------------------*/
/* Initialize Deque */
/* input arguments: 
  dq -- pointer to deque
  cap = capacity of a memory block to be allocated
*/
void initDeque(struct Deque * dq, int cap) {
   assert (dq);
   dq->capacity = cap;
   dq->size = dq->front = 0;
   dq->data = (TYPE *) malloc(dq->capacity * sizeof(TYPE));
   assert (dq->data != 0);
}

/*----------------------------------------------*/
/* input arguments: 
  dq -- pointer to deque
  val -- value of the data element to be added 
*/
void addFrontDeque(struct Deque *dq, TYPE val) {  
   assert(dq);
   if (dq->size == dq->capacity) _doubleCapacityDeque(dq); 
   dq->front--;
   if (dq->front < 0) dq->front += dq->capacity; 
   dq->data[dq->front] = val; 
   dq->size ++;
}

/*----------------------------------------------*/
/* Double the memory capacity of a deque */
void _doubleCapacityDeque (struct Deque *dq) {
  assert (dq);
  int j;
  TYPE * oldData = dq->data; /*memorize old data*/
  int oldFront = dq->front; /*memorize old index of the front end of deque*/
  int oldSize = dq->size; /*memorize old size*/
  int oldCapacity = dq->capacity; /*memorize old capacity*/
  initDeque(dq, 2 * oldCapacity); /*new memory allocation*/
  for (j = 0 ; j < oldSize; j++) {/*copy back old data*/
    dq->data[j] = oldData[oldFront++];
    if (oldFront >= oldCapacity) oldFront = 0;
  }
  free(oldData);
  dq->size = oldSize;
}



/*----------------------------------------------*/
/* Print all elements of a deque starting from the front */
/* input arguments: 
  dq -- pointer to deque
*/
void printDeque(struct Deque * dq) {
   assert (dq);

   printf("FRONT: ");
   int i;
   for (i = 0; i < dq->size; i++) {
      printf("%d  ", dq->data[(dq->front + i) % dq->capacity]);

   }

   printf(" :END\n");

/* FIX ME */

}


/*----------------------------------------------*/
/* Remove one or all element(s) from the back of Deque */
/* input arguments: 
  dq -- pointer to deque
  flag -- flag = 1:remove only one element at the back
          flag = -1:remove all repetitions of the element at the back
*/
void removeBackAllDeque(struct Deque *dq, int flag)
{ 
   assert(dq && (flag == 1 || flag == -1)); 

   /* The variable to remove */

   assert(dq->size != 0 || dq != 0);


   /* Remove just the last element */
   if (flag == 1) {

      dq->size--;
      
   }

   /* Remove all occurances of the element at the back */
   if (flag == -1) {

      /* store the back, but also remove it */
      int back; 
      back = dq->front + dq->size - 1;
      TYPE val = dq->data[back];
      printf("val %i\n", val);
      dq->size--;

      printf("front %i\n", dq->front);
      int oldSize = dq->size;

      /* check if there are repeats */
      int i; 
      for (i = dq->front; i < (dq->front+oldSize); i++) {

         if (EQ(val, dq->data[i])) {
            printf("found a repeat! \n");
            printf("repeat: %i\n", dq->data[i]);
            removeAtDeque(dq, i);
         }
         
      }


      
   }
 
/* FIX ME */

}


void removeAtDeque(struct Deque * dq, int idx) {
   /* assert((dq != NULL) && (dq->size != 0) && (idx < dq->size && idx >= 0)); */
   
   printf("removing...\n");
   int i; 
   for (i = idx; i < (dq->front+dq->size) - 1; i++) {
     
      dq->data[i] = dq->data[i + 1];

      
   }

   dq->size--;

}


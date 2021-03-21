/* ENTER YOUR FIRST AND LAST NAME: Andrea Tongsak */

/* TO COMPILE, ENTER:  gcc -Wall -ansi -o program Group2.c */

/* TO RUN, ENTER PROGRAM ARGUMENTS: SIZE, FLAG */
/* FOR EXAMPLE:  ./program 20 -1 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int
#define EQ(a,b) (a == b)  

struct Deque{
    TYPE *data; 
    int size; /* number of elements in data */
    int capacity; /* memory capacity of deque */
    int front; /* index of the front element of deque  */
};


/* INTERFACE -----------------------------------*/
void initDeque(struct Deque * dq, int cap);
void addFrontDeque(struct Deque *dq, TYPE val);
void addBackDeque(struct Deque *dq, TYPE val);
void printDeque(struct Deque *dq);
void removeAllDeque(struct Deque *dq, int flag);
void _doubleCapacityDeque (struct Deque *dq);


/*----------------------------------------------*/
int main(int argc, char **argv){
   struct Deque dq;
   int i, j, reps;
   TYPE val;
   int  capacity = 1;
   int  size = atoi(argv[1]);
   int flag = atoi(argv[2]);

   if(size < 0){
     printf("\nInvalid value for the size of Deque; size must be a nonnegative integer.\n");
     return 0;
   }
   if(flag != 1 && flag != -1){
     printf("\nInvalid value for the flag; flag must be either -1 or 1.\n");
     return 0;
   }

 
   initDeque(&dq, capacity); /*initialize Deque*/

   /* Generate integers in [0,100] and add them to deque */
   srand(time(NULL)); /*initialize the random generator*/
   i = 0;
   while(i<size)
   {
      val = (TYPE) rand() % 101;
      reps = ((int) rand() % 4) + 1; /* number of repetitions, at least 1*/
      j = 0;
      while(i<size && j<reps){
         if(flag == 1)
            addFrontDeque(&dq, val); /*add val to front of Deque*/
         else
            addBackDeque(&dq, val); /*add val to back of Deque*/
         i++;
         j++;
      }
   }

   printf("Deque before remove:\n");
   printDeque(&dq); /*print all elements*/

   if (size > 0) removeAllDeque(&dq, flag);

   printf("Deque after remove:\n");
   printDeque(&dq); /*print all elements*/

   return 0;
}


/*----------------------------------------------*/
/* Initializes a deque 
   Input arguments:
     dq -- pointer to a deque implemented as a dynamic array
     cap -- capacity of memory block allocated to the deque
*/
void initDeque(struct Deque * dq, int cap) {
   assert (dq);
   dq->capacity = cap;
   dq->size = dq->front = 0;
   dq->data = (TYPE *) malloc(dq->capacity * sizeof(TYPE));
   assert (dq->data != 0);
}

/*----------------------------------------------*/
/* Prints out all elements of a deque starting from the front 
   Input argument: 
       dq -- pointer to a deque implemented as a dynamic array 
*/
void printDeque(struct Deque * dq) {
   assert (dq);
   int i;

   printf("FRONT: ");
   for(i=0; i< dq->size; i++)
      printf("%d ", dq->data[(dq->front + i) % dq->capacity]);
 
   printf(" :END\n");
}

/*----------------------------------------------*/
/* Doubles the memory capacity of a deque.
   Deque is implemented as a dynamic array, where indices of elements 
   wrap around the block of memory.
   Input argument: 
      dq -- pointer to a deque implemented as a dynamic array 
*/
void _doubleCapacityDeque (struct Deque *dq) {
  assert (dq);
  int j;
  TYPE * oldData = dq->data; /*memorize old data*/
  int oldFront = dq->front; /*memorize old index of the front end of deque*/
  int oldSize = dq->size; /*memorize old size*/
  int oldCapacity = dq->capacity; /*memorize old capacity*/
  initDeque(dq, 2 * oldCapacity); /*new memory allocation*/
  for (j = 0 ; j < oldSize; j++)  /* copy back old data */
     dq->data[j] = oldData[(oldFront++) % oldCapacity];
  free(oldData);
  dq->size = oldSize;
}


/*----------------------------------------------*/
/* Adds a new element to a deque at front.
   Deque is implemented as a dynamic array, where indices of elements 
   wrap around the block of memory.
   Input arguments: 
     dq -- pointer to a deque implemented as a dynamic array 
     val -- value of the data element to be added 
*/
void addFrontDeque(struct Deque *dq, TYPE val) {  
   assert(dq);
   if (dq->size == dq->capacity) _doubleCapacityDeque(dq); 

   /* FIX ME */
   dq->front--;

   /* make sure the start index wraps around */
   if (dq->front < 0) {
       dq->front = dq->front + dq->capacity;
   }
   dq->data[dq->front] = val;
   dq->size++;

}

/*----------------------------------------------*/
/* Adds a new element to a deque at back.
   Deque is implemented as a dynamic array, where indices of elements 
   wrap around the block of memory.
   Input arguments: 
     dq -- pointer to a deque implemented as a dynamic array 
     val -- value of the data element to be added 
*/
void addBackDeque(struct Deque *dq, TYPE val) {  
   assert(dq);
   if (dq->size == dq->capacity) _doubleCapacityDeque(dq); 

   /* FIX ME */
   int backIndex = (dq->front + dq->size) % dq->capacity;

   dq->data[backIndex] = val;

   dq->size++;

}


/*----------------------------------------------*/
/* Removes the front or back element of a deque, depending on the flag.
   Also, removes all consecutive repetitions of the front or back element. 
   Deque is implemented as a dynamic array, where indices of elements 
   wrap around the block of memory.
   Input arguments: 
     dq -- pointer to a deque implemented as a dynamic array 
     flag -- flag = 1 remove from front; flag = -1 remove from back
*/
void removeAllDeque(struct Deque *dq, int flag)
{ 
   assert(dq && (flag == 1 || flag == -1) && dq->size > 0); 

   TYPE val; /*auxiliary variable*/

   if(flag == 1)
   {  /* remove from the front */  
         /* FIX ME */
         val = dq->data[dq->front];

         /* remove all repetitions*/
         while (EQ(val, dq->data[dq->front]) && dq->size >= 0) {
             /* increase front index, since exiting from top */
             dq->front++;

            /* if the front equals the last element, wrap around to start */
             if (dq->front == dq->capacity) {
                 dq->front = 0;
             }

             dq->size--;

         }
   }
   else
   { /* remove from the back */ 
         /* FIX ME */
         int backIndex = (dq->front + dq->size - 1) % dq->capacity;
         val = dq->data[backIndex];

         /* check for repetitions */
         while (EQ(val, dq->data[backIndex]) && dq->size >= 0) {
             /* decrease back index and size */
             backIndex--;

            /* wrap around to the back*/
             if (backIndex < 0) {
                 backIndex = dq->capacity - 1;
             }
             dq->size--;
         }

   }

}



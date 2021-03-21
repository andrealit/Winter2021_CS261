/* ENTER YOUR FIRST AND LAST NAME:      */

/* TO COMPILE, ENTER:  gcc -Wall -ansi -o prog Queue.c */

/* TO RUN, ENTER PROGRAM ARGUMENTS: CAPACITY, SIZE */
/* FOR EXAMPLE:  ./prog 10 4*/


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
void addQueue(struct Deque *q, TYPE val);
TYPE removeQueue(struct Deque *q);

/*----------------------------------------------*/
void _doubleCapacityDeque (struct Deque *dq);
void _printDeque(struct Deque *dq);

/*----------------------------------------------*/
int main(int argc, char **argv){
   struct Deque q;
   int i;
   TYPE val;
   int  capacity = atoi(argv[1]);
   int  size = atoi(argv[2]);

   assert(capacity > 0 && size >= 0);

   srand(time(NULL)); /*initialize random generator*/

   initDeque(&q, capacity); /*initialize Queue*/

   for(i=1; i<=size; i++)
   {
      val = (TYPE) rand() % 5;
      addQueue(&q, val); /*add val to Deque*/
   }
 
   printf("Queue before remove:\n");
   _printDeque(&q); /*print all elements*/

   val = removeQueue(&q);

   printf("The first element of Queue was  %d\n", val);

   printf("Queue after removing the first element:\n");
   _printDeque(&q); /*print all elements*/

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
void _printDeque(struct Deque * dq) {
   assert (dq);
   int i;

   printf("FRONT: ");
   for(i=0; i< dq->size; i++)
      printf("%d ", dq->data[(dq->front + i) % dq->capacity]);
 
   printf(" :END\n");
}


/*----------------------------------------------*/
/* Return and remove the first element of Queue */
/* input arguments:  q -- pointer to Queue
   output :  val -- value of the first element of Queue
 */
TYPE removeQueue(struct Deque *q){ 
   TYPE val; /*auxiliary variable*/

   assert(q->size != 0 && q);

    /* get the first element, store in val */
    val = q->data[q->front];

    /* increment the front point to the second element */
    q->front++;

    if (q->front == q->capacity) {
        q->front = 0;
    }

    q->size--;

    return val;

}


/*----------------------------------------------*/
/* Add a new element to Queue */
/* input arguments: 
  q -- pointer to Queue
  val -- value of the data element to be added 
*/
void addQueue(struct Deque *q, TYPE val) {  

    assert(q);

    if (q->size >= q->capacity) {
        _doubleCapacityQueue(q);
    }

    /* compute the back index */
    int backIndex = (dq->front + dq->size) % dq->capacity;

    /* assign new value*/
    q->data[backIndex] = val;

    /* increment the new size */
    q->size++;

}




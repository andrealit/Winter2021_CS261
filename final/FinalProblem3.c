/* ENTER YOUR FIRST AND LAST NAME: Andrea Tongsak   */
/* TO COMPILE:  gcc -Wall -ansi -o finalout FinalProblem3.c */
/* TO RUN, ENTER YOUR INPUT FILE NAME:  ./program 2.3 input1.txt  */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Structs */

struct Element{
   int priority; /* the lower value the higher priority */
   char string[100];
};

#define TYPE struct Element

struct DynArr{
   TYPE *data;  /* pointer to the data array */
   int size;  /* number of elements in the array */
   int capacity;  /* capacity of the array */
};

/* Interface */
void _adjustHeap(DynArr *heap, int max, int pos);

/* Percolate down a node of Heap
   Input: heap -- pointer to the heap
          index -- index of a node for percolating down
*/
void percolateDownHeap(struct DynArr *heap, int index) {
    assert(heap && index < heap->size);
    int higher;
    TYPE tmp;
    int maxIdx = heap->size;
    int leftIdx = index * 2 + 1; /* left child index */
    int rghtIdx = index * 2 + 2; /* right child index */
    while (leftIdx < heap->size) {
        if (rghtIdx < maxIdx)
            higher = heap->data[leftIdx].priority < heap->data[rghtIdx].priority ? leftIdx : rghtIdx;
        else
            higher = leftIdx;
        if(heap->data[higher].priority < heap->data[index].priority){
            tmp = heap->data[higher];
            heap->data[higher] = heap->data[index];
            heap->data[index] = tmp;
            index = higher;
            leftIdx = index * 2 + 1;
            rghtIdx = index * 2 + 2;
		} else
            leftIdx = heap->size;
	} 

}
/* Remove from Heap elements with lower priority than a threshold
    - Input: heap = pointer to a heap implemented as a dynamic array.
             threshold =  positive integer.
    - Pre-conditions: heap was initialized well and exists in memory, but may be empty.
      Also, heap correctly established the priority relationships among all of its elements.
    - Constraints: time complexity <= O(n log n); no new data structures allowed,
                   no new memory locations can be allocated, except for a couple of integers
*/
void removeThresholdHeap(struct DynArr *heap, int threshold){
   assert(heap && threshold > 0);
	/* FIX ME */ 
	int i;

	/* check if there are elements in the heap that are less than the treshold */

	max = heap->size;

	/* while elements that are lower priority still exist*/
	for(i = 0; i < heap->size; i++) {
		percolateDownHeap(heap, 0);

		/* check for lower priority */
		if (heap->data[i].priority < threshold) {
			/* remove the element */
			removeHeap(heap, i);

			/* adjust the heap */
			_adjustHeap(heap, max, i);


		}

	}
	


}

void removeHeap(DynArr *heap, int i)
{
  	/* FIXME */

    /* Step 1: Copy the last element to the first */
    if (heap->size) {
        heap->data[i] = heap->data[heap->size - 1];
    }

    /* Step 2: Reduce the size of the heap */
    heap->size--;
    
    /* Step 3: Percolate down the new root */
    _adjustHeap(heap, 0, heap->size - 1);
}

/* Recursive function */
int _findIndexHeap(DynArr * heap, TYPE e, int currentIdx) {
	/* */
	if (currentIdx < heap->size) {
		if (EQ(heap->data[currentIdx], e) {
			return currentIdx;
		} else if (LT(heap->data[currentIdx], e)) {

			/* left index: 2*current + 1 and right index: 2*current + 2 */
			leftChildIdx = _findIndexHeap(heap, e, 2*currentIdx+1);
			rightChildIdx = _findIndexHeap(heap, e, 2*currentIdx+2);

			return (leftChildIdx > rightChildIdx) ? leftChildIdx : rightChildIdx;
		}
	}
	return -1;
}

/*	Adjust heap to maintain heap property
	
	param: 	heap	pointer to the heap
	param: 	max		max index of the heap nodes in the dynamic array
	param: 	pos		position index where the adjustment starts
	pre:	none
	post:	heap property is maintained for nodes from index pos to index max
*/
void _adjustHeap(struct DynArr *heap, int max, int pos)
{
  	/* FIXME */
	
	/* assert(max < sizeDynArr(heap)); */

    int leftIdx = pos * 2 + 1; /* left child index */
    int rghtIdx = pos * 2 + 2; /* right child index */
    int smallIdx;

    if (rghtIdx < max) { /* there are 2 children */

        /* compare and swap with the smaller child */
        smallIdx = _smallerIndexHeap(heap, leftIdx, rghtIdx);

        if (LT(heap->data[smallIdx].priority, heap->data[pos].priority)) {
            swapDynArr(heap, pos, smallIdx);
            _adjustHeap(heap, smallIdx, max);
        }

    } else if (leftIdx < max) { /* there is 1 child */
        /* compare and swap if the left child is smaller */
        if (LT(heap->data[leftIdx].priority, heap->data[pos].priority)) {
            swapDynArr(heap, pos, leftIdx);
            _adjustHeap(heap, leftIdx, max);
        }

    }
    /* else, no children */
}

int main(int argc, char** argv) {
    
	
	return 0;

}
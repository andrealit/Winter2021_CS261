#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int

struct dynArr {
    TYPE *data; /* TYPE is the name of a data type */
    int size;
    int capacity;
};

/* Initializes a bag */
void initDynArr(struct dynArr * da, int cap) {
   da->capacity = cap;
   assert (cap > 0);
   da->size = 0;
   da->data = (TYPE *) malloc(da->capacity * sizeof(TYPE));
   assert (da->data != 0);
}
/* Adds element e to the end of a bag */
/* Time complexity: O(1) */
void addDynArr(dynArr *da, TYPE e){
    if (da->size >= da->capacity) _dynArrDoubleCapacity(da);
    da->data[da->size] = e;
    da->size++;
}
/* Checks if element e occurs in a bag */
int containsDynArr(dynArr *da, TYPE e){
    int i;
    for (i = 0; i < da->size; i++)
        if(da->data[i] == e) return i;  /* returns the index of e */
    return -1;
}
/* Removes the first occurrence of element e from a bag */
void removeDynArr(dynArr *da, TYPE e){
    int index = containsDynArr(da,e); /* checks if e is in the bag */
    if (index >= 0) removeAtDynArr(da,index); /* removes at index */
}


/* Time complexity: O(n) */
void _dynArrDoubleCapacity (struct dynArr * da) {
    TYPE * oldbuffer = da->data;
    int oldsize = da->size;
    int i;
    int cap;

    /* take the old capacity and multiply by two */
    if (oldsize == 0) {
        cap = 50;
    } else { 
        cap = da->capacity * 2;
    }

    /* initialize the capacity */
    initDynArr(da, cap);

    /* copy over elements */
    for (i = 0; i < da->size; i++) {
        da->data[i] = oldbuffer[i];
    }

    da->size = oldsize;

    /* free the old buffer */
    free(oldbuffer);
    
}

/* Time complexity: O(1) */
TYPE getDynArr(dynArr *da, int idx) {
    assert(idx > 0 && idx < da->size);

    return da->data[idx];

}

/* Time complexity: O(n) */
void removeAtDynArr(dynArr *da, int idx) {
    assert(da != NULL && (da->size != 0) && (idx > 0 && idx < da->size));

    int i;
    for (i = idx; i < da->size - 1; i++) {
        da->data[i] = da->data[i+1];
    }

    da->size--;
}

/* Time complexity: O(n^2) */
void bag2set(struct dynArr *da) {
    int i;
    TYPE temp;
    struct dynArr *auxBag; /* auxiliary bag */
    /* initialize auxBag */
    initDynArr(auxBag);

    /* iterate over elements of the input bag */
    int i;
    for (i = 0; i < da->size; i++) {
        /* get an element at index i from the bag */
        temp = da->data[i];

        /* copy the element to auxBag if unique (4 pts) */
        /* -1 means it is unique */
        if (-1 == containsDynArr(auxBag, temp)) {
            addDynArr(auxBag, temp);
        }

    }

	free(auxBag->data); 	/* free the space on the heap */
	da = auxBag;
}
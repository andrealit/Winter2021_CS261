#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int
#define EQ(a,b) (a == b)  

struct dynArr{
    TYPE *data; /* TYPE is the name of a data type */
    int size;
    int capacity;
};


/* binary search of e in a sorted array */
/* returns the index of e, or where e can be inserted */
int binarySearch (TYPE * data, int size, TYPE e) {
   int low = 0;
   int high = size;
   int mid;
   while (low < high) {
        mid = (low + high) / 2;
        if (LT(data[mid], e)) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low; 
}


/* Initializes a set */
void initDynArray(struct dynArr * da, int cap) {
   da->capacity = cap;
   assert (cap > 0);
   da->size = 0;
   da->data = (TYPE *) malloc(da->capacity * sizeof(TYPE));
   assert (da->data != 0);
}


/* Adds element e to a set */
void sortedArrayAdd (struct dynArr *da, TYPE e) {
   int index = binarySearch(da->data, da->size, e);
   _dynArrayAddAt (da, index, e);
}


/* Removes element e from a set */
int sortedArrayRemove (struct dynArr *da, TYPE e) {
   int index = binarySearch(da->data, da->size, e);
   if (index < da->size && da->data[index] == e) {
       _dynArrayRemoveAt(da, index);
   }
      
}


/* Checks if element e occurs in a set */
int sortedArrayContains (struct dynArr *da, TYPE e){
    int index = binarySearch(da->data, da->size, e);
    if (index < da->size && da->data[index] == e) {
        return 1;
    }
    return 0; 
}


/* Removes element e from an array at index */
void _dynArrayRemoveAt (struct dynArr * da, int index) {
   int i;
   assert(index < da->size);  assert(index >= 0);
   /* Remove, and fill out the gap */
    for (i = index; i < da->size-1; i++) {
       da->data[i] = da->data[i+1];
   }
   da->size--;
}


/* Adds element e to an array at index */
void _dynArrayAddAt (struct dynArr * da, int index, TYPE e) {
   int i;
   if (da->size >= da->capacity)
      _dynArrSetCapacity(da, 2*da->capacity);
   for (i=da->size; i > index; i--)  {
       da->data[i] = da->data[i-1];
   }
   da->data[index] = e;
   da->size++;
}


/* Set the capacity of an array */
void _dynArraySetCapacity (struct dynArr * da, int newCap) {
   TYPE * oldbuffer = da->data;
   int oldsize = da->size;
   int i;
   initDynArr(da, newCap);
   for (i = 0; i < oldsize; i++)  {
       da->data[i] = oldbuffer[i];
   }
   da->size = oldsize;
   free(oldbuffer);
}

struct dynArr* intersection (struct dynArr *set1, struct dynArr *set2) {
    int i;
    int j;
    TYPE temp;
    struct dynArr * interSet;

    /* initialize interSet  (4 pt) */
    initDynArr(interSet, set1->capacity);

    /* iterate over elements of two input sets (2 pt) */
    int i = set1->size;
    int j = set2->size;
    while (i > 0 && j > 0) {

        /* check for repeats */
        if (set1->data[i-1] > set2->data[j-1]) {
            /* assign temp to set 1 */
            temp = set1->data[i-1];
            i--;
        } else if (set1->data[i-1] < set2->data[j-1]) {
            /* assign temp to set 2 */
            temp = set2->data[j-1];
            j--;
        } else {
            /* assign temp to second */
            temp = set2->data[j-1];
            i--, j--;
        }

        /* copy the element from either set1 or set2 by binary search */
        int k = binarySearch(interSet->data, interSet->size, temp);

        /* if k is not less than size and there is no match */
        if (!(k < interSet->size && EQ(interSet->data, temp))) {
            /* Add the element at k */
            _dynArrayAddAt(interSet, k, temp);
        }
    
    }

    return interSet;

}

struct dynArr * difference(struct dynArr *set1, struct dynArr *set2) {
    int i;
    int j;
    TYPE temp;
    struct dynArr * diffSet;

    /* initialize diffSet (4pt) */
    initDynArray(diffSet, set1->capacity);

    /* iterate over elements of two input sets (2 pt)*/
    i = set1->size;
    while (i > 0) {
        /* copy element from set1 to diff set if unique from set 2 */
        j = binarySearch(set2->data, set2->size, set1->data[i]);

        if (!(j < set2->size && EQ(set2->data[j], set1->data[i]))) {
            sortedArrayAdd(diffSet, set1->data[i]);
        }
        i--;
    }
}


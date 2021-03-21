/* Deques Linked Lists */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int

struct dlink {
    TYPE value;
    struct dlink * next;
    struct dlink * previous;
};

struct dlist {
    int size; 
    struct dlink * frontSentinel;
    struct dlink * backSentinel;
};

/* Interface for the linked lists */
int isEmpty();
void addFront(TYPE val);
void addBack(TYPE val);
void removeFront();
void removeBack();
TYPE front();
TYPE back();

/* Interface for Queue implemented as a doubly linked list */
void addFrontQueue (struct DList *dq, TYPE val);
void addBackQueue(struct DList *dq, TYPE val);

/* Queue definitions */
void addFrontQueue (struct DList * q, TYPE val) {
    /* The front of the queue is added to the last sentinel */
    _addDLink(dq, dq->sentinel->next, e);
}

/* Adding the link to the queue */
void _addDLink(struct DList dq, struct DLnk *lnk, TYPE val) {
    /* Step 1: allocate memory for the new link, assign a value */
    struct DLink * newlink = (struct DLink *) malloc (sizeof(struct DLink));
    assert(newlink != 0);
    newlink->value = val;

    /* Step 2: attach the newlink into the deque */
    newlink->prev = lnk->prev;
    newlink->next = lnk;

    /* Step 3: properly attach the deque into the new link */
    lnk->prev->next = newlink;
    lnk->prev = newlink;

    /* Step 4: increase size */
    dq->size++;

}

/* Front of the deque */
void addFrontDeque (struct DList *dq, TYPE val) {
    /* why reinvent the adding? */
    _addDLink(dq, dq->frontSentinel->front, dq);
}

/* Back of the deque */
void addBackDeque (struct DList * dq, TYPE val) {
    /* Add to the back of the queue */
    _addDLink(dq, dq->backSentinel->prev, dq);
}


/** Book version **/

/* Add doubly linked list */
void addDList(struct DList *dq, struct DList *lnk, TYPE val) {

    /* assert that dq, lnk, etc */
    assert(dq);
    assert(lnk);
    assert(lnk != frontSentinel);

    /* 1. the actual creation of a link is made */
    struct dlink* newlink = (struct dlink*) malloc (sizeof(struct dlink));
    assert(newlink != 0);
    newlink->value = e;

    /* 2. The new link of the previous is assigned to the previous link */
    newlink->prev = lnk->prev;
    newlink->next = lnk;

    /* 3. The previous element is assigned to the new link */
    lnk->prev->next = newlink;
    lnk->prev = newlink;

    /* 4. increase the size of the link */
    dq->size++;

}

/* Remove from Front */
void removeFrontDeque (struct dlist * dq) {
   _removeDeque(dq, dq->frontSentinel->next);
}

/* Remove from Back */
void removeBackDeque (struct dlist * dq) {
    _removeDeque(dq, dq->backSentinel->prev);
}

/* Remove Linked List */
/* the link before the lnk is removed */
void removeDList (struct dlist *ls, struct dlist *lnk) {
    
    assert(ls && !isEmptyDeque(ls));
    /* 1. assign prev's next to link's next */
    lnk->prev->next = lnk->next;

    /* 2. assign the next's previous to the previous of the one before*/
    lnk->next->prev = lnk->prev;

    /* 3. free in memory */
    free(lnk);

    /* 4. decrement the size */
    ls->size--;
}








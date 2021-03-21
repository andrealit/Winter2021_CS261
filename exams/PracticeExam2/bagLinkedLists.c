/* Worksheet 17 Linked Lists and List Stack*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int

struct link {
    EleType value;
    struct link * next;
};

struct linkedListsBag {
    struct link *firstLink;
}

/* This initializes the bag */
void LinkedListBagInit (struct linkedListsBag * s) {
    s->firstLink = 0;
}

/* This algorithm allocates memory, assigns the value to the parameter, and then assigns the next to the link before it */
struct link * _newLink (EleType v, struct link * n) {
    struct link * lnk = (struct link *) malloc(sizeof(struct link));
    assert(lnk != 0);
    lnk->value = v;
    lnk->next = n;
    /* will return the link that was added */
    return lnk;
}

/* Add an element to the place before it */
void linkedListBagAdd(struct linkedListBag * s, EleType d) {
    s->firstLink = _newLink(d, s->firstLink);
}


/* Check if the bag contains an element of this type */
int linkedListBagContains (struct linkedListBag *s, EleType d) {
    struct link * temp = s->firstLink;
    while (temp->next != NULL) {
        if (EQ(temp->value, e)) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

/* Remove element from bag once it is found */
void removeBag(struct linkedListBag *s, EleType d) {
    /* assign the previous value to the first element in the bag */
    struct link * prevLink = s->firstLink;
    /* the current will be the next element in the sentinel */
    struct link * current = s->firstLink->next;

    /* iterate through the current and make sure is not iterating through */
    for (current = s->firstLink->next, current != 0, current = current->next) {
        if (EQ(current, value)) {
            prevLink->next = current->next;
            free(current);
            return;
        }
        previous = current->next;
    }
}


struct Link {
    TYPE value;
    struct Link * next;  
};

struct ListStack {
    struct Link * sentinel;
};

/* Initialize the empty stack */
void initStack (struct ListStack *stk) {
    /* initialize the sentinel */
    struct Link * sentinel = (struct Link *) malloc(sizeof(struct Link));
    /* make sure the sentinel is not equal to null */
    assert(sentinel != 0);
    /* Have the next equal the NULL element, since it's the stack is currently empty. */
    sentinel->next = NULL;
    /* The global sentinel is now a sentinel */
    stk->sentinel = sentinel;
}

/* Push an element onto the stack */
void pushStack (struct listStack *stk, TYPE val) {
    /* 1. create the memory for the link */
    struct Link * new = (struct Link *) malloc (sizeof(struct Link));
    assert(new != 0);
    new->value = val;

    /* 2. link the element to the next */
    new->next = sentinel->next;

    /* 3. assign the sentinel front to the new element */
    stk->sentinel->next = new;
}

/* Pop the first element from the stack */
void popStack (struct listStack * stk) {
    /* 1. get the first element */
    struct Link * current = stk->sentinel->next;

    if (current != NULL) {
        /* 2. assign the sentinel front to the next element after the removed one */
        stk->sentinel->next = stk->sentinel;

        /* 3. free the memory of the element */
        free(current);
    }
}

/* Worksheet 17 */

/* topStack */
EleType topStack (struct listStack * stack) {
    assert(!linkedListStackIsEmpty(stack));

    return s->firstLink->value;
}

/* isEmptyStack will return an int */
int isEmptyStack (struct listStack * stack) {
    /* check if its null */
    return s->firstLink == 0;
}
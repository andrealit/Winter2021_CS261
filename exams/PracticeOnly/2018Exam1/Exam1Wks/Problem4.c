#define TYPE double

#define EQ(a, b) (a==b)

struct Link {
    TYPE value;
    struct Link * next;
};

struct ListStack {
    struct Link * sentinel;
};

/* Initializes a stack */
void initStack(struct ListStack * stk) {
    /* initialize the sentinel & memory */
    struct Link * sentinel = (struct Link*) malloc (sizeof(struct Link));

    assert(sentinel != 0);

    /* linked list is empty */
    sentinel->next = NULL;
    stk->sentinel = sentinel;
}

/* input: stk -- pointer to the stack, val -- value of the new data element to be added */
void pushStack(struct ListStack *stk, TYPE val) {
    assert(stk->sentinel != NULL);

    /* allocate the new link */
    struct Link * temp = (struct Link*) malloc (sizeof(struct Link));
    
    assert(temp != 0);

    temp->value = val;
    /* linked lists end points at the sentinel */
    temp->next = stk->sentinel->next;
    stk->sentinel->next = temp;

}

/* input: stk -- pointer to the stack */
void removeStack (struct ListStack *stk, TYPE val) {
    /* check if the stack is empty */
    if (stk->sentinel != NULL) {
        if (EQ(stk->sentinel->next->value, val)) {
            popStack(stk);
        }
    }
}

/* input: stk -- pointer to the stack */
void popStack (struct ListStack *stk) {
    /* check if the stack is empty */
    struct Link * lnk = stk->sentinel->next;

    if (lnk != NULL) { /* the top element exists */
        /* sentinel now points to the second element */
        stk->sentinel->next = lnk->next;
        /* free the first element */
        free(lnk);
    }
    
}

void popAllStack (struct ListStack * stk, TYPE val) {
    /* make sure the stack exists */
    assert(stk);
    struct Link * lnk = stk->sentinel->next;

    /* check if stack is empty */

    /* if the next sentinel is still equal to the value we wish to remove */
    while (lnk && EQ(lnk->value, val)) {
        /* connect the sentinel the the second element */
        stk->sentinel->next = lnk->next;

        /* free the link (3 pts) */
        free(lnk);

    }

} 
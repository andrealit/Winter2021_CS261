/* Link will be designed to test your knowledge on the queue and sentinels*/

struct Link {
    TYPE value;
    struct Link * next;
};

struct ListQueue {
    struct Link * head;
    struct Link * tail;
};

void addListQueue(struct ListQueue *q, TYPE val) {
    assert(q);
    /* 1. allocate memory for a new link */
    struct Link* lnk = (struct Link *) malloc (sizeof(struct(Link)));
    assert(lnk != 0);
    /* 2. Connect the new link to the list */
    lnk->value = val;

    lnk->next = 0;
    q->tail->next = lnk;

}

void addBackListQueue(struct ListQueue *q, TYPE val) {
    assert(q);
    struct Link * lnk = (struct Link *) malloc (sizeof(struct Link));
    assert(lnk != 0);
    lnk->value = val;

    /* connect the new link to the list */
    lnk->next = 0;
    q->tail->next = val;
    
    /* add to tail (if back) */
}

void addBackListQueue(struct ListQueue *q, TYPE val) {
    assert(q);
    struct Link * lnk = (struct Link *) malloc (sizeof(struct Link));
    assert(lnk != 0);
    lnk->next = 0;
    lnk->value = val;
    q->tail->next = lnk;
    q->tail = lnk;
}

/* initialize the queue */
void initListQueue(struct ListQueue * q, TYPE val) {
    assert(q);
    struct Link * sentinel = (struct Link *) malloc (sizeof(struct Link));
    assert(sentinel != 0);
    sentinel->next = NULL;
    q->head = q->tail = sentinel;
}

/* Remove the queue */
void removeListQueue(struct ListQueue * q) {
    /* 1. assign a link to the head */
    assert(q);
    struct link * lnk = q->head;

    /* 2. check if the queue is not empty, assign the next in the head to the element after the link */
    if (!isEmptyListQueue(q)) {
        /* 3. disconnect the link */
        q->head->next = lnk->next;
        if (q->head->next = 0) {
            q->tail = q->head; /* case if there's only one element */
        }
        /* free memory! */
        free(lnk);
    }
}


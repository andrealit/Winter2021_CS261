
struct Customer {
    int ID;
    int time;
};

struct Deque {
    TYPE * data;
    int capacity;
    int size;
    int start;
};

/* Merging two distinct queues into one queue dynamic array */
void mergeQ(struct Deque * q1, struct Deque * q2, struct Deque * q3) {
    assert(q1 && q2 && q3);
    int cap;
    cap = (q1->capacity > q2->capacity) ? q1->capacity : q2->capacity;

    initDeque(q3, cap);

    int q1_i = 0, q2_i = 0;
    int q1_iw, q2_iw;

    while (q1_i < q1->size && q2_i < q2->size) {
        /* compute the absolute index modulo capacity */
        q1->iw = (q1_i + q1->start) % q1->capacity;
        q2->iw = (q2_i + q2->start) % q2->capacity;

        if (q1->data[q1_iw].time < q2->data[q2_iw].time) {
            addBackDeque(q3, q1->data[q1_iw]);
            q1_i++;
        } else if (q1->data[q1_iw].time > q2->data[q2_iw].time) {
            addBackDeque(q3, q1->data[q])
            q2_i++;
        } else {
            addBackDeque(q3, q1->data[q1_iw]);
            q1_i++;
            addBackDeque(q3, q2->data[q2_iw]);
            q2_i++;
        }

        if (q1_i == q1->size) {
            while (q2_i < q2->size) {
                q2_iw = (q2_i + q2->start) % q2->capacity;
                addBackDeque(q3, q2->data[q2_iw]);
                q2_i++;
            }
        } else {
            while (i < q1->size) {
                q1_iw = (q1_i + q1->start) % q1->capacity;
                addBackDeque(q3, q1->data[q1_iw]);
                q1_i++;
            }
        }

        free(q1->data);
        free(q2->data);
        q1->capacity = q1->size = q1->start = 0;
        q1->capacity = q1->size = q1->start = 0;
    }
}


/* Difference of queue*/
void diffQ(struct Deque * q1, struct Deque * q2) {
    assert (q1 && q2);
    int q2_i, q2_iw;
    for (q2_i = 0; q2_i < q2->size; q2_i++) {
        q2_iw = (q2_i + q2->start) % q2->capacity;
        removeAllQueue(q1, q2->data[q2_iw]);
    }
    
}

/* Psuedo code for merging two queues */
/* 1. check if q1 and q2 have valid arguments */
/* 2. init q3 (memory for 3rd queue) */
/* 3. loop simultaneously through q1 and q2 */
/* 4. pick a customer from q1 or q2 that is smallest */
/* 5. add rest of queue to q3 */
/* 6. remove q1 and q2 from memory */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TYPE int

struct customerJob{
    TYPE customerData[100]; /* TYPE is the data type */
    int customerDataSize; /* number of elements in customerData array */
    int customerID;   /* identifies VIP or ordinary customers */
};

struct dlink{
    struct customerJob *job;   /* pinter to customer data and ID */
    struct dlink *next;  /* points to next dlink in the list */
    struct dlink *prev;  /* points to previous dlink in the list */
};

struct myList{
    int size;   /* the number of elements in the list */
    struct dlink *head;  /* points to front Sentinel */
    struct dlink *tail;   /* points to back Sentinel */
};

/* Initializes a list */
void initList(struct myList * list){
   assert(list != 0);
   list->tail = (struct dlink *) malloc(sizeof(struct dlink));
   list->head = (struct dlink *) malloc(sizeof(struct dlink));
   list->tail->next = NULL;
   list->head->prev = NULL;
   list->tail->prev = list->head;
   list->head->next = list->tail;
   list->size = 0;
}
/*  Adds a job to the list after a link */
void  _addAfterLink(struct myList *list, struct dlink *link,
                          struct customerJob *job){
   int i;
   struct dlink *temp = (struct dlink *) malloc(sizeof(struct dlink));
   temp->job = (struct customerJob *) malloc(sizeof(struct customerJob));
   assert(list != 0); assert(link != 0);
   assert(temp != 0); assert(temp->job != 0);
   temp->job->customerDataSize =  job->customerDataSize;
   temp->job->customerID =  job->customerID;
   for (i=0;i<job->customerDataSize;i++)
       temp->job->customerData[i] = job->customerData[i];
   link->next->prev = temp;
   temp->next = link->next;
   temp->prev = link;
   link->next = temp;
   (list->size)++;
}
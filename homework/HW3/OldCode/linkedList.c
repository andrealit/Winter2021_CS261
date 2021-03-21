#include <assert.h>
#include <stdlib.h>
#include "structs.h"
#include "linkedList.h"

/*
	initLinkedList
	param: l the linked List
	pre: l is not null
	post: the head of the linked list is initialized to null, isEmpty returns true
*/
void initLinkedList(LinkedList *l) 
{ 
   l -> head = NULL;
}

/*
	isEmptyLinkedList
	param: l the linked list
	pre: l is not null
	post: none
*/
int isEmptyLinkedList(LinkedList *l) 
{ 
   return (l->head == NULL); 
}


/*----------------------------------------------------------------------------*/
/* Note: Free gets rid of all links but keeps the head of the list around, so 
   the list itself still exists and is initialized.
*/

void freeLinkedList(LinkedList *l) {

  while (!isEmptyLinkedList(l)) 
  { 
     popLinkedList(l);
  }
}

/* Stack Interface */

/*
	pushLinkedList
	param: l the linked list
	param: val the value to be pushed
	pre: l is not null
	post: l is not empty, l size has increased by one
*/

/*----------------------------------------------------------------------------*/
void pushLinkedList(LinkedList *l, TYPE val) {
  struct Link *link = (struct Link *)malloc(sizeof(struct Link));
  assert(link != NULL);

  link->next = l->head;  
  link->val = val;
  l->head = link;
}

/*
	topLinkedList
	params: l the linked list
	pre:  l is not null
	pre: l is not empty
	post: none
*/

/*----------------------------------------------------------------------------*/
TYPE topLinkedList(LinkedList *l) {
  assert(!isEmptyLinkedList(l));
  return l->head->val;
}

/* 	
	popLinkedList
	param: l the linked list
	pre: l is not null
	pre: l is not empty
	post: l size has decremented by one
*/
/*----------------------------------------------------------------------------*/
void popLinkedList(LinkedList *l) {
  struct Link *link = l->head;
  assert(!isEmptyLinkedList(l));

  l->head = link->next;
  free(link);
}

/* Bag */

void addLinkedList (LinkedList *l, TYPE val)
{
  pushLinkedList(l,val);
}

int containsLinkedList(LinkedList *l, TYPE val)
{
	/* write this function */
	struct Link *cur;
	assert (!isEmptyLinkedList(l));
	cur = l->head;	
	while(cur!=NULL)
	{
		if(EQ(cur->val, val))
		  return 1;
		else cur = cur->next;
	}
	return 0;
}

void _removeLink(struct Link *prev, struct Link *cur)
{
	prev->next = cur->next;
	free(cur);
}

void removeLinkedList (LinkedList *l, TYPE val)
{

	struct Link *cur;
	struct Link *prev;

	assert(containsLinkedList(l, val));

	/* special case for head */
	if (l->head->val == val) {
			/* in this case, value is at the front */
			cur = l->head;
			l->head = l->head->next;
			free(cur);
	} else {	
		/* write this part of the function */

		/* assign the previous to the head */
		prev = l->head;	
		/* assign the new current to the next */
		cur = l->head->next;

		/* while the next is not null, iterate into the list*/
		while(cur != NULL) {

			/* case where the value and current match */
			if (EQ(val, cur->val)) {
				_removeLink(prev, cur);
			} else {
				/* if link is not found, then assign the previous to the current */
				prev = cur;	
				/* the current is now the next */
				cur = cur->next;
			}
			
		}
	}
		
}

#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht)
{  /*write this*/
	struct hashLink* currentNode;
	struct hashLink* nextNode;
	int i;
	/* iterate through the table with each index */
	for (i = 0; i < ht->tableSize; i++) {
		/* store the current node of the table slot */
		currentNode = ht->table[i];

		/* keep the next node, free the current node, and repeat until no more nodes */
		while (currentNode != 0) {
			nextNode = currentNode->next;
			free(currentNode->key);
			free(currentNode);
			currentNode = nextNode;
		}
	}
	/* deallocate memory, reinitialize all struct elements to 0 */
	free(ht->table);
	ht->tableSize = 0;
	ht->table = 0;
	ht->count = 0;

}


/*
 insert the following values into a hashLink, you must create this hashLink but
 only after you confirm that this key does not already exist in the table. you
 cannot have two hashLinks for the word "taco".

 if a hashLink already exists in the table for the key provided you should
 replace that hashLink (really this only requires replacing the value v).
 */
void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  /*write this*/

	/* define the hashLink to help with holding a value */
	struct hashLink* newHashLink;

	/* step 1. hashing index for where to insert the node */
	int hashIdx = stringHash1(k) % ht->tableSize;

	/* step 2. allocate memory */
	newHashLink = (struct hashLink*)malloc(sizeof(struct hashLink));

	/* step 3: insert element if not there, else shift over all elements by one */
	if (ht->table[hashIdx] == 0) {
		/* the table slot at the index is empty, then populate the table slot */
		ht->table[hashIdx] = newHashLink;
		ht->table[hashIdx]->key = k;
		ht->table[hashIdx]->value = v;
		ht->table[hashIdx]->next = 0;
	}
	else {
		/* THIS IS A COLLISION */
		newHashLink->key = k;
		newHashLink->value = v;

		newHashLink->next = ht->table[hashIdx];

		ht->table[hashIdx] = newHashLink;

	}

	/* step 4. increment the count */
	ht->count++;


}


/*
 this returns a POINTER to the value stored in a hashLink specified by the key k.

 if the user supplies the key "taco" you should find taco in the hashTable, then
 return a pointer to the value member of the hashLink that represents taco. keep
 in mind we are storing an int for value, so you don't use malloc or anything.

 if the supplied key is not in the hashtable return NULL.
 */
ValueType* atMap (struct hashMap * ht, KeyType k)
{ /*write this?*/
	/* Define a temporary hash link to help with searching the key */
	struct hashLink* tempHashLink;

	int hashIdx = stringHash1(k) % ht->tableSize;

	/* check if the table value is empty */
	if (ht->table[hashIdx] == 0) {
		return 0;
	} else {
		/* collision situation */
		
		/* hold the content of that element in the table to the temp hashLink */
		tempHashLink = ht->table[hashIdx];

		/* loop through linked lists from that slot */
		while (tempHashLink != 0) {
			if (strcmp(tempHashLink->key, k) != 0) {
				/* assign temp holder to the next */
				tempHashLink = tempHashLink->next;
			}
			else {
				/* return address of the temp link */
				return (&tempHashLink->value);
			}
		}
	}

    return 0;
}


/*
 a simple yes/no if the key is in the hashtable. 0 is no, all other values are
 yes.
 */
int containsKey (struct hashMap * ht, KeyType k)
{  /*write this*/
	if (atMap(ht, k) == 0) {
		return 0;
	}
	else {
		return 1;
	}
}

/*
 find the hashlink for the supplied key and remove it, also freeing the memory
 for that hashlink. it is not an error to be unable to find the hashlink, if it
 cannot be found do nothing (or print a message) but do not use an assert which
 will end your program.
 */

/* 
1. Hash to get the index of the table
2. Loop through the linked list of that index
3. Have the temp node be the same as the first element
4. Compare the key to the key of the temp node
4.1 If they match, check if the node has a "next".
4.1.1 If they have a next node, assign the NEXT node to the currentNode->next
4.1.2 Free the currentNode (for removal)
4.1.3 Assign the new current to the nextNode

4.2 If they don't match, move to the next node
4.2.1 Now, current node is the nextNode, 
repeat the check
*/

void removeKey (struct hashMap * ht, KeyType k)
{  /*write this?*/

    /* iterate inside the hashMap */
    struct hashLink* currentNode;
	struct hashLink* prevNode;

    int hashIdx = stringHash1(k) % ht->tableSize;

	/* nothing is here, so do no nothing */
    if (ht->table[hashIdx] == 0) {
		return;
	} else {
		/* loop through hash table from that slot */
		currentNode = ht->table[hashIdx];
		prevNode = ht->table[hashIdx];
		
		while (currentNode != 0) {

			/* compare the words, the words are not equal */
			if (strcmp(currentNode->key, k) != 0) {
				
				currentNode = currentNode->next;
				
			}
			else { /* They are equal, so remove the element*/
				if (currentNode->next != 0) { /* case where there are values after the element */

					/* assign the ht->table[idx] to the next */
					/* store the next element in the current node */
					prevNode = currentNode; 
					ht->table[hashIdx] = currentNode->next;
					free(prevNode);

				} else { /* case where there are no values after the element */
					/* just remove it */
					free(currentNode);
				}

			}
		}
	}
    
    
    /* once the key in the hashMap is found, release the memory */

}

/*
 returns the number of hashLinks in the table
 */
int sizeMap (struct hashMap *ht)
{  /*write this*/
	return ht->count;
}

/*
 returns the number of buckets in the table
 */
int capacityMap(struct hashMap *ht)
{  /*write this*/
	return ht->tableSize;
}

/*
 returns the number of empty buckets in the table, these are buckets which have
 no hashlinks hanging off of them.
 */
int emptyBuckets(struct hashMap *ht)
{  /*write this*/
	int numEmptyBuckets = 0;
	
	int i;
	for (i = 0; i < ht->tableSize; i++) {

		if (ht->table[i] == 0) {
			numEmptyBuckets++;
		}
	}

	return numEmptyBuckets;
}

/* Formula for table load is */
float tableLoad(struct hashMap *ht)
{  /*write this*/
	float load = (float)sizeMap(ht) / (float)capacityMap(ht);
	return load;
}
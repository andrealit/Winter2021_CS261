#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++) {
		r += str[i];
		/* for debugging purpose */
		/* printf(" str[i] = %s  i = %d r = %d \n", &str[i], i, r); */
	}
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++) {
		r += (i + 1) * str[i]; /*the difference between 1 and 2 is on this line*/
		/* for debugging purpose */
		/* printf(" str[i] = %s  i = %d r = %d \n", &str[i], i, r); */
	}
	return r;
}


/* The function initMap() initializes the hash table with a given table size. */
void initMap(struct hashMap* ht, int tableSize)
{
	/* step 1 - allocate memory to the array of links, each representing the head of a linked list */
	int index;
	if (ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);

	/* step 2 - initialize all headers of the linked list */
	ht->tableSize = tableSize;
	ht->count = 0;
	for (index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht)
{  /*write this*/
	int i;
	struct hashLink *temp;
	struct hashLink *temp2;
	for(i = 0; i < ht->tableSize; i++){
		temp = ht->table[i];

		while(temp != NULL){
			temp2 = temp->next;
			free(temp);
			temp = temp2;
		}
	}
	free(ht->table);
	ht->count = 0;
	ht->table = 0;
	ht->tableSize = 0;	
}

/* The function insertMap() overwrites any previous value associated with the input key. */
void insertMap (struct hashMap* ht, KeyType k, ValueType v)
{  /*write this*/

	/* define a hash link for the newHashLink to help with the insertion of the element */
	struct hashLink *newHashLink; 

	/* step 1: compute the index of element in the hash table from the key and table size using stringHash2 function */
	int hashIndex = (stringHash2(k) % ht->tableSize);

	/* step 2: allocate memory for the element to be inserted to the hash map table  */
	newHashLink = (struct hashLink*)malloc(sizeof(struct hashLink));

	/* step 3: insert new element into the hash map table */
	if(ht->table[hashIndex] == 0){
		/* here, there is NO element on that hash table slot */
		/* assign newHashLink to that slot of the hash table */
		ht->table[hashIndex] = newHashLink;
		/* now populate key and value into that slot of the hash table*/
		ht->table[hashIndex]->key = k;
		ht->table[hashIndex]->value = v;
		ht->table[hashIndex]->next = 0;
	}

	/* case for a collision */
	if (ht->table[hashIndex] != 0) {
		newHashLink->key = k;
		newHashLink->value = v;
		/* re-link the the new populated element where newHashLink becomes the front of that slot */
		newHashLink->next = ht->table[hashIndex];
		ht->table[hashIndex] = newHashLink;
	}

	/* step 4 - increment the hash table counter after insert */
	ht->count++;

}

/* The function atMap() returns a POINTER to VALUE associated with the input key k, or returns NULL if the key is not found. */
ValueType* atMap (struct hashMap * ht, KeyType k)
{ /*write this?*/

	/* define a hash link to help with the search of the key */
	struct hashLink* currentHashLink;

	/* get index to the hash map table using stringHash2 function */
	int hashIndex = stringHash2(k) % ht->tableSize;

	/* get the pointer to value associated with the input key in the hash map table via hash link currentHashLink */
	/* if the key at the calculated hash index is NULL that means key is not found; then return NULL */
	/* if the key is found then traverse the hash link to get the pointer to the value*/
	if (ht->table[hashIndex] == 0) {
		/* here, the slot of the hashTable is EMPTY, then we return 0 or NULL */
		return 0;
	}

	/* handle case where the hashtable has a collision */
	if (ht->table[hashIndex] != 0) {
		/* here, the slot of the hashTable is OCCUPIED, then copy element of that slot to currentHashLink */
		currentHashLink = ht->table[hashIndex];
		/* then traverse the linked list of that slot by comparing the given Key/Word to what is in the existing hashLink */
		/* return the POINTER to Value of that hashLink once the Key/Word is FOUND */
		while (currentHashLink !=0) {

			if(strcmp(currentHashLink->key,k) == 0) {
				return &(currentHashLink->value);
			}else{
				/* go to the next link in the hash tables*/
				currentHashLink = currentHashLink->next;
			} 
		}
		return 0;
	}
}

/* The function containsKey() returns a non-zero integer if the key is found in the hash table, and zero, otherwise. */
int containsKey (struct hashMap * ht, KeyType k)
{  /*write this*/

	/* use atMap() function to check if the key K is in the has map table */

	if (atMap(ht,k) == NULL) {
		return 0;
	}
	
	if (atMap(ht, k) != NULL) {
		return 1;
	}
}

/*  The function removeKey() removes an element with a given key from the hash table. */
void removeKey (struct hashMap * ht, KeyType k)
{  /*write this?*/

	/* define two hash links to help with the removing of the element */
	struct hashLink* currentHashLink;
	struct hashLink* prevHashLink;

   /* get index to the hash map table using stringHash2 function */
	int hashIndex = stringHash2(k) % ht->tableSize;

   /* remove the element from the table */
	if(ht->table[hashIndex] == 0){
		return;
	}
	
	if (ht->table[hashIndex] != 0) {

		currentHashLink = ht->table[hashIndex];                    /* for iteration  */
		prevHashLink = ht->table[hashIndex];                       /* to help remove */

		while(currentHashLink != 0) {

			if (strcmp(currentHashLink->key,k) == 0) {

				if(currentHashLink == ht->table[hashIndex]){       /* handle the special case */
					ht->table[hashIndex] = currentHashLink->next;
				} else {
					prevHashLink->next = currentHashLink->next;
				}
				free(currentHashLink);
				ht->count--;
				
				return;
			} else {
				prevHashLink = currentHashLink;
				currentHashLink = currentHashLink->next;

			}
			
		}
	}
}

/* The function sizeMap() returns the number of elements in the map. */
int sizeMap (struct hashMap *ht)
{  /*write this*/
	return ht->count;
}

/*  The function capacityMap() returns the table size of the map.*/
int capacityMap(struct hashMap *ht)
{  /*write this*/
	return ht->tableSize;
}

/*  The function emptyBuckets() returns number of empty buckets or slots of the map. */
int emptyBuckets(struct hashMap *ht)
{  /*write this*/
	int emptyBuckets = 0;
	int i;

	for(i=0; i < ht->tableSize; i++){

		/* the spot is empty */
		if(ht->table[i] == 0){
			emptyBuckets++;
		}
	}
	return emptyBuckets;
}

/*  The function tableLoad() returns the calculated load factor of the map. */
float tableLoad(struct hashMap *ht)
{  /*write this*/
	float tableLoad = (float)sizeMap(ht)/(float)capacityMap(ht);
	return tableLoad;
}
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers separated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file); /* prototype */
void printHashMap(struct hashMap* ht); /* prototype */
void printWordCount(struct hashMap* ht); /* prototype */

/****************************************/

int main (int argc, const char * argv[]) {
    /*Write this function*/

	const char* inputFileName;
	FILE* fileptr;
	struct hashMap hashTable;
	KeyType eachWord;
	int tableSize = 70;

	ValueType* ptrToValue;	/* define a ptr to the value in a hash map link*/
	
	if (argc == 2) {
		inputFileName = argv[1];
	}
	else {
		inputFileName = "input.txt";
		printf("Input File Name = %s\n", inputFileName);
	}

	/* Initialize the hashMap */
	initMap(&hashTable, tableSize);

	/* Open the input file to read */
	fileptr = fopen(inputFileName, "r");

	/* Loop through the file and read each word, place into map, until EOF */

	while (!feof(fileptr)) {
		/* read each word */
        eachWord = getWord(fileptr);

		if (!eachWord) {
			break;
		}

		/* at map searches the tree and returns the POINTER to the value of the word */
		ptrToValue = atMap(&hashTable, eachWord);

		/* if the ptr to the slot is not empty, add the word into the map */
		if (ptrToValue == 0) {
			/* inserting the node to the table for the first time */
			insertMap(&hashTable, eachWord, 1);
			
		} else {
			(*ptrToValue)++;
			free(eachWord);
		}

	}

	/* close the file */
	fclose(fileptr);

	/* print the hash table */
	printHashMap(&hashTable);

	/* print the word counts */
	printWordCount(&hashTable);

    printf("\n");
	
	/* free the memory */
	freeMap(&hashTable);
	
    return 1;

}

void printHashMap(struct hashMap* ht) {
	struct hashLink* hashLink;
    int i;

	/* Print out a header */
	printf("HASH TABLE CONTENT: \n");

	for (i = 0; i < ht->tableSize; i++) {
		hashLink = ht->table[i];
		printf("Index: %d | ", i);
		while (hashLink != 0) {
			printf("%s:%d | ", hashLink->key, hashLink->value);
			hashLink = hashLink->next;
		}
		printf("\n");
	}
}


void printWordCount(struct hashMap* ht) {
    struct hashLink* hashLink;
    int i;

    printf("\nHASH WORD FREQUENCIES: \n");

    for (i = 0; i < ht->tableSize; i++) {
        hashLink = ht->table[i];
        while (hashLink != 0) {
            printf("    %s: %d\n", hashLink->key, hashLink->value);
            hashLink = hashLink->next;
        }
    }

}

char* getWord(FILE *file)
{
	
	int length = 0;
	int maxLength = 16;
	char character;
    
	char* word = (char*)malloc(sizeof(char) * maxLength);
	assert(word != NULL);
    
	while( (character = fgetc(file)) != EOF)
	{
		if((length+1) > maxLength)
		{
			maxLength *= 2;
			word = (char*)realloc(word, maxLength);

		}
		if((character >= '0' && character <= '9') || /*is a number*/
		   (character >= 'A' && character <= 'Z') || /*or an uppercase letter*/
		   (character >= 'a' && character <= 'z') || /*or a lowercase letter*/
		   character == 39) /*or is an apostrophy*/
		{
			word[length] = character;
			length++;
		}
		else if(length > 0)
			break;
	}
    
	if(length == 0)
	{
		free(word);
		return NULL;
	}
	word[length] = '\0';
	return word;
}

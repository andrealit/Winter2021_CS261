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
void printHashMap(struct hashMap * ht);

/****************************************/

int main (int argc, const char * argv[]) {
    /*Write this function*/

	/* Variable definitions */
	const char* fileName; 
	/* file ptr */
	FILE * fileptr;
	/* hash map struct */
	struct hashMap hashTable;
	struct hashLink * temp;
	char * word;
	int j;
	
	/* set the table size */
	int tableSize = 70;
	
	int * keyPos;

	if (argc != 1) {
		return 0;
	} else if (argc == 1) {
		fileName = "input.txt";
	}

	/* open the input text file */
	if (argc == 1) {
		printf("Input File Name: %s\n", fileName);
	}

	/* init hashtable */
	initMap(&hashTable, tableSize);

	/* open the input file, read word one by one, and insert the word */
	/* open the input file, read "r" */

	/* use atMap function to get the pointer to the value and keep it in keyPos */
	fileptr = fopen(fileName, "r");

	while (!feof(fileptr)) {
		word = getWord(fileptr);

		if (!word) {
			break;
		}

		/* discover where the key position is */
		keyPos = atMap(&hashTable, word);

		if (keyPos != 0) {
			(*keyPos)++;
		} else {
			insertMap(&hashTable, word, 1);
		}
	}

	for(j=0; j < hashTable.tableSize; j++){
		temp = hashTable.table[j];
			
		while(temp!=0){
			printf("%s:%d\n", temp->key,temp->value);
			temp=temp->next;
			
		}
	}

	fclose(fileptr);

	/* Print the hashtable after its sorted */

	printf("===================================================================\n");
	printf("	H A S H  M A P  T A B L E  P E R F O R M A N C E \n");
	printf("===================================================================\n");

	printf("	HashMap Table Size = %d\n", sizeMap(&hashTable));
	printf("	HashMap Table Capacity = %d\n", capacityMap(&hashTable));
	printf("	HashMap Table Load = %f\n", tableLoad(&hashTable));

	/* Calculate empty buckets */
	printf("	HashMap Table has %i empty buckets!\n\n", emptyBuckets(&hashTable));

	/* Print the hash map */
	printHashMap(&hashTable);

	/* Free */
	freeMap(&hashTable);

	return 0;
}


void printHashMap(struct hashMap *ht) {
	int i;

	printf("===================================================================\n");
	printf("	H A S H  M A P  T A B L E  C O N T E N T \n");
	printf("===================================================================\n");

	for (i = 0; i < ht->tableSize; i++) {
		printf("	Index = %d | ", i);
		
		while (ht->table[i] != NULL) {
			printf("%s:%d | ", ht->table[i]->key, ht->table[i]->value);
			ht->table[i] = ht->table[i]->next;
		}
		printf("\n");
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


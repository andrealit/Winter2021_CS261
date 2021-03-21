#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.
 
 when there are no more words in the input file this function will return NULL.
 
 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file);                /* prototype */

/* the printHashMap function takes the hash table and preform content printout.*/
void printHashMap(struct hashMap* ht);     /* prototype */

/****************************************/

int main (int argc, const char * argv[]) {
    const char* filename;                 /* define ptr to input filename  */
	FILE* fileptr;                        /* define ptr to that input file */
	struct hashMap hashTable;             /* define hash map table         */
    char *eachWordKey;                    /* define ptr of temp word holder 
										     while reading input file      */
    int tableSize = 70;                   /* set hash map table size       */
	clock_t startTime, finishTime;        /* define start and finish times */
	int *ptrValueofHashLink;              /* define ptr to Value a hash Link */
	int numWordRead = 0;
	int numWordInserted = 0;
	int countRepeatWord = 0;
    
	/* Handle input file & initialize the hash map table:
	   Take the filename either from user input or from the default input file.
	   Echo out what file to open to read.
	   Keep the start time of program run so we can calculate Concordance performance.
	   Then initialize hash map table.
	*/
	if(argc == 2)
        filename = argv[1];
    else
        filename = "input.txt";           /* assign the file name         */
    
	printf("===================================================================\n");
    printf(" The Input File Name: %s\n", filename);
	printf("-------------------------------------------------------------------\n\n");
    
    startTime = clock();                  /* keep program run start time  */

	
    initMap(&hashTable, tableSize);       /* initialize hash map table    */
   
	/* for debugging purpose
	printf("===================================================================\n");
	printf(" Before Reading Input File \n");
	printf("-------------------------------------------------------------------\n\n");
	printHashMap(&hashTable);
	*/

	 /* Open input file, read word one-by-one, and insert word to the hash map table:
	    Open the input file for read "r".
		Read each word until the end of file via while-loop.
		Use atMap function to get the POINTER to the value stored 
		  in a hashLink specified by the key eachWordKey and keep it in ptrValueofHashLink; 
		  if the supplied key is not in the hashtable ptrValueofHashLink will be NULL.
		If ptrValueofHashLink is NOT NULL then increment *ptrValueofHashLink to the next
		  else call insertMap function to insert the eachWordKey.
     */
	fileptr = fopen(filename,"r");       
	
	while (!feof(fileptr)) {	

		/* free(eachWordKey); */

		/* read each Word or Key from the input file */
		eachWordKey = getWord(fileptr);
		numWordRead++;

		/* if error in reading the Word, then stop */
		if(!eachWordKey){
			break;
		}

		/* get the pointer to value of HashLink containing the Word in the Hash table using atMap() function */
		/* ptrValueofHashLink is 0 or NULL if the Word or Key is NOT FOUND by atMap()  */
		ptrValueofHashLink = atMap(&hashTable, eachWordKey);
		
		/* If the Word/Key is FOUND then ONLY INCREMENT the Value of that Word/Key of that HashLink of the Hash Table */
		/* or we are adding the count (or value) of the Word/Key that we read from input file that is already on the Hash table */
		/* Else the Word is NOT FOUND, we then insert the Word/Key as HashLink to the Hash Table */
		if(ptrValueofHashLink != 0){
			countRepeatWord++;
			(*ptrValueofHashLink)++;
		}else{
			insertMap(&hashTable, eachWordKey,1);
			numWordInserted++;
		}

		
	}

	/* Close the input file */
	fclose(fileptr);

	printf("===================================================================\n");
	printf(" H A S H  M A P  T A B L E  R U N  P E R F O R M A N C E \n");
	printf("-------------------------------------------------------------------\n");

	/* Calculate final run time and provide after run information*/
	finishTime = clock() - startTime;
	printf(" Concordance ran in %f seconds\n", (float)finishTime / (float)CLOCKS_PER_SEC);

	/* Show number of words read from the input file  */
	printf(" Number of words read from Input file = %d\n", numWordRead);
	printf(" Number of words inserted to the hash table = %d\n", numWordInserted);
	printf(" Number of words read that already exist in the hash table = %d\n", countRepeatWord);


	/* Calculate Loading Performance to Hash Map Table */
	printf(" Hash Map Table Size = %d\n", sizeMap(&hashTable));
	printf(" Hash Map Table Capacity = %d\n", capacityMap(&hashTable));
	printf(" Hash Map Table load = %f out of 1.0\n", tableLoad(&hashTable));

	/* Calculate Empty Buckets Left in the Hash Map Table */
	printf(" Hash Map Table has %d empty table buckets!\n\n",emptyBuckets(&hashTable));
	
	/* Print the hash map */
	printHashMap(&hashTable);

	/* Free memory used for the Hash Table */
	freeMap(&hashTable);

    return 0;
}


void printHashMap(struct hashMap *ht) {
	
	int i;
	struct hashLink* hashLink;

	printf("===================================================================\n");
	printf(" H A S H  M A P  T A B L E  C O N T E N T \n");
	printf("-------------------------------------------------------------------\n");

	for (i = 0; i < ht->tableSize; i++) {
		printf(" Index = %d | ", i);
		hashLink = ht->table[i];
		while (hashLink != 0) {
			printf("%s:%d | ", hashLink->key, hashLink->value);
			hashLink = hashLink->next;
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
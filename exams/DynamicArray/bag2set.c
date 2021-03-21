/* bag2set.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynArray.h"


/* Converts the input bag into a set using dynamic arrays 
	param: 	da -- pointer to a bag 	
	return value: void
        result: after exiting the function da points to a set 		
*/
void bag2set(struct DynArr *da){
    
    TYPE temp;
    struct DynArr * bag = (struct DynArr*) malloc (sizeof(struct DynArr));

    initDynArr(bag, da->capacity);

    int i;
    for (i = 0; i < da->size; i++) {
        temp = da->data[i];

        if (containsDynArr(auxBag, temp) == -1) {
            addDynArr(auxBag, temp);
        }
    }

    free(da->data);
    da->data = auxBag->data;
    da->size = auxBag->data;

}

int main(int argc, char* argv[]){

	int i;
        struct DynArr da;  /* bag */
        
        initDynArr(&da, 100);
        da.size = 10;
        	da.data[0] = 1.3;
	for (i=1;i<da.size;i++){
	    da.data[i] = 1.2;
	 }
    
        printf("Bag:\n\n");
	for (i=0;i<da.size;i++){
          printf("%g  \n", da.data[i]);
        }
        
        printf("\n\n\n");
        printf("Set:\n\n");
        bag2set(&da);
	for (i=0;i<da.size;i++){
          printf("%g ", da.data[i]);
        }
        printf("\n");
        
	return 0;	
}


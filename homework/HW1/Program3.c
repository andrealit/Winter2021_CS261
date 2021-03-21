/* CS261- HW1 - Program3.c*/

/* Name: Andrea Tongsak
 * Date: 1/6/2021
 * Solution description: This program uses bubble sort to sort an array of ints. It's filled and tested in main()
 * We are sorting integers in ascending order
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void sort(int* number, int n){
    /*Sort the array of integers by length n*/

    /* bubble sort method, ascending (low to high) */
    int k;
    for (k = 0; k < n - 1; k++) {

        int j;
        for (j = 0; j < n - k - 1; j++) {

            /* swap the values */
            if (number[j] > number[j+1]) {
                int temp = number[j];
                number[j] = number[j+1];
                number[j+1] = temp;

            }
        }
    }

}

int main() {
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;

    /*Allocate memory for an array of n integers using malloc.*/
    int * array = (int *) malloc(n * sizeof(int));
    
    /*Fill this array with random numbers, using rand().*/
    srand(time(NULL));

    int i;
    for (i = 0; i < n; i++) {
        array[i] = rand() % 101;    /* filling numbers from 0 to 100, unspecified */
    }
    
    /*Print the contents of the array.*/
    printf("Generated unsorted array: \n");
    for (i = 0; i < n; i++) {
        printf("%d  ", array[i]);
    }
    printf("\n\n");

    /*Pass this array along with n to the sort() function of part a.*/
    sort(array, n);
    
    /*Print the contents of the array.*/
    printf("Sorted array: \n");
    for (i = 0; i < n; i++) {
        printf("%d  ", array[i]);
    }
    printf("\n");

    /* Free memory */
    free(array);
    
    return 0;
}

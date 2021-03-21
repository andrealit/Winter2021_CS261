/* CS261- HW1 - Program4.c*/

/* Name: Andrea Tongsak
 * Date: 1/6/2021
 * Solution description: This program utilizes concepts on structs and points from Program2.
 * However, we are now sorting students by intitials.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct student{
	char initials[2];
	int score;
};

void sort(struct student* students, int n){
    /*Sort n students based on their initials*/   

    /* Let's utilize bubble sort again, just with initials */
    int i;
    for (i = 0; i < n - 1; i++) {

        int j;
        for (j = 0; j < n - i - 1; j++) {

            /* compare first initial, ascending order */
            if (students[j].initials[0] > students[j+1].initials[0]) {
                struct student temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
            } 
            /* compare second initial if they're the same */
            if (students[j].initials[0] == students[j+1].initials[0]) {
                if (students[j].initials[1] > students[j+1].initials[1]) {
                    struct student temp = students[j];
                    students[j] = students[j+1];
                    students[j+1] = temp;
                }
            }
        }
    }
}

int main(){
    /*Declare an integer n and assign it a value.*/
    int n = 20;

    if (n == 0) {
        printf("There are no students, it's an empty array. Exiting...\n");
        exit(0);
    }

    /*Allocate memory for n students using malloc.*/
    struct student * students;
    students = (struct student*) malloc(n * sizeof(struct student));

    /*Generate random IDs and scores for the n students, using rand().*/
    srand(time(NULL));

    int i;
    for (i = 0; i < n; i++) {
        /* code to generate random characters */
        students[i].initials[0] = 'A' + (rand() % 26);
        students[i].initials[1] = 'A' + (rand() % 26);

        students[i].score = rand() % 101;
    }

    /*Print the contents of the array of n students.*/
    printf("Unsorted array of students: \n");
    for (i = 0; i < n; i++) {
        printf("%d.  %c%c  %i\n", i+1, students[i].initials[0], students[i].initials[1], students[i].score);
    }
    printf("\n");

    /*Pass this array along with n to the sort() function*/
    sort(students, n);

    /*Print the contents of the array of n students.*/
    printf("Sorted array of students: \n");
    for (i = 0; i < n; i++) {
        printf("%d.  %c%c  %i\n", i+1, students[i].initials[0], students[i].initials[1], students[i].score);
    }

    /*Deallocate memory*/
    free(students);
    
    

    
    return 0;
}

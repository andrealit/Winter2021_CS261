/* CS261- HW1 - Program2.c*/

/* Name: Andrea Tongsak
 * Date: 1/6/2021
 * Solution description: Write functions that uses structs of students and prints out content.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	char initials[2];
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student *student_ptr = (struct student*) malloc(10 * sizeof(struct student));
     
     /*return the pointer*/
     return student_ptr;

}

void generate(struct student* students){
     /*Generate random initials and scores for ten students.
	The two initial letters must be capital and must be between A and Z. 
	The scores must be between 0 and 100*/

     srand(time(NULL));

     /* "students" is a pointer to a struct of structs */
     int i;
     for (i = 0; i < 10; i++) {
          /* code to generate random characters */
          students[i].initials[0] = 'A' + (rand() % 26);
          students[i].initials[1] = 'A' + (rand() % 26);

          students[i].score = rand() % 101; /* score from 0 to 100 */
     }

}

void output(struct student* students){
     /*Output information about the ten students in the format:
              1. Initials  Score
              2. Initials  Score
              ...
              10. Initials Score*/

     int i;
     for (i = 0; i < 10; i++) {
          printf("%d.  %c%c  %i\n", i+1, students[i].initials[0], students[i].initials[1], students[i].score);
     }

}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
     
     int minimum = students[0].score;
     int maximum = students[0].score;

     int sum = 0;
     double average;

     /* find minimum, maximum, and sum */
     int i;
     for (i = 1; i < 10; i++) {
          if (students[i].score < minimum) {
               minimum = students[i].score;
          }

          if (students[i].score > maximum) {
               maximum = students[i].score;
          }

          sum += students[i].score;
     }

     average = sum / 10;

     printf("Minimum: %d\nMaximum: %d\nAverage: %.2f\n", minimum, maximum, average);
     
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
     if (stud == NULL) {
          printf("Memory not allocated...\n");
          return;
     } else {
          free(stud);
          printf("Memory successfully deallocated.\n");
     }
}

int main(){
     struct student* stud = NULL;
    
     /*call allocate*/
     stud = allocate();
    
     /*call generate*/
     generate(stud);
     
     /*call output*/
     output(stud);
     
     /*call summary*/
     summary(stud);

     /*call deallocate*/
     deallocate(stud);
     
     return 0;
}

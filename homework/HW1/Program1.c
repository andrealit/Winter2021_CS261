/* CS261- HW1 - Program1.c */

/* Name: Andrea Tongsak
 * Date: 1/6/2021
 * Solution description: Program 1 focuses on writing a function and manipulating integers with pointers
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int *a, int *b, int c){
	
    /* Increment a */
    (*a)++;
	
    /* Decrement  b */
	(*b)--;

    /* Assign a-b to c */
	c = (*a) - (*b);

    /* Return c */
	return c;
}

int main() {

    int x, y, z;
    int result;

    srand(time(NULL));

    /* Will pick a range of numbers from 0-10 */
    x = rand() % 11;
    y = rand() % 11;
    z = rand() % 11;

    /* Print the values of x, y and z */

    /* %d means a decimal value */
    printf("Before calling foo():\n");
    printf("x: %d\n", x);
    printf("y: %d\n", y);
    printf("z: %d\n", z);

    /* Call foo() appropriately, passing x,y,z as parameters */
    result = foo(&x, &y, z);
	
    /* Print the values of x, y and z */
    printf("After calling foo():\n");
    printf("x: %d\n", x);
    printf("y: %d\n", y);
    printf("z: %d\n", z);

    printf("Notice that z hasn't changed, since we didn't pass the address!\n");
	
    /* Print the value returned by foo */
    printf("Return value foo(): %d\n", result);
	
    /* Is the return value different than the value of z?  Why? */
    
    /**
     * Yes, the returned value is different. "foo" is a mathematical function which produces its own return value.
     * foo = x+1 - (y-1) = x - y + 2
     * z is already its own value that doesn't change throughout the program (due to being passed directly), 
     * and foo calls x and y within the function calculation. They aren't related.
     */ 

    return 0;
}

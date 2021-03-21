#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include "avl.h"


int FindMinPath(struct AVLTree *tree, TYPE *path);
void printBreadthFirstTree(struct AVLTree *tree);
void preorder(TYPE parent_val, struct AVLnode * node, TYPE * min_cost, TYPE * min_path, int * p_length, TYPE * current_path, int * cp_length, TYPE sumOfDiff);


/* -----------------------
The main function
  param: argv = pointer to the name (and path) of a file that the program reads for adding elements to the AVL tree
*/
int main(int argc, char** argv) {

	FILE *file;
	int len, i;
	TYPE num; /* value to add to the tree from a file */
	struct timeval stop, start; /* variables for measuring execution time */
	int pathArray[100];  /* static array with values of nodes along the min-cost path of the AVL tree. The means that the depth of the AVL tree cannot be greater than 100 which is  sufficient for our purposes*/

	struct AVLTree *tree;
	
	tree = newAVLTree(); /*initialize and return an empty tree */
	
	file = fopen(argv[1], "r"); 	/* filename is passed in argv[1] */
	assert(file != 0);

	/* Read input file and add numbers to the AVL tree */
	while((fscanf(file, "%i", &num)) != EOF){
		addAVLTree(tree, num);		
	}
	/* Close the file  */
	fclose(file);

        printf("\nThe AVL tree has %d nodes.\n",tree->cnt);
	
	printf("\nPrinting the AVL tree breadth-first : \n");
	printBreadthFirstTree(tree);

	gettimeofday(&start, NULL);

	/* Find the minimum-cost path in the AVL tree*/
	len = FindMinPath(tree, pathArray);
	
	gettimeofday(&stop, NULL);

	/* Print out all numbers on the minimum-cost path */
	printf("\n\nThe minimum-cost path has %d nodes printed top-down from the root to the leaf: \n", len);
	for(i = 0; i < len; i++)
		printf("%d ", pathArray[i]);
	printf("\n");

	printf("\nYour execution time to find the mincost path is %f microseconds\n", (double) (stop.tv_usec - start.tv_usec));

        /* Free memory allocated to the tree */
	deleteAVLTree(tree); 
	
	return 0;
}
  
/* --------------------
Finds the minimum-cost path in an AVL tree
   Input arguments: 
        tree = pointer to the tree,
        path = pointer to array that stores values of nodes along the min-cost path, 
   Output: return the min-cost path length 

   pre: assume that
       path is already allocated sufficient memory space 
       tree exists and is not NULL
*/
int FindMinPath(struct AVLTree *tree, TYPE *path)
{
    /* FIX ME */

	/* length of the min-cost path */
	int path_min = 0;
	struct AVLnode * current = tree->root;

	/* lengths of the current path */
	TYPE min_cost = (TYPE) 50000; /* just a really large number. compare the sums of one path */
	int possible_path = 0;
	TYPE candidate_path[70];

	/* Set the first element in the array to the root */
	path[path_min] = tree->root->val;
	path_min++;

	/* if the tree has more than its root */
	if (tree->cnt > 1) {
		/* traverse the tree and find the min cost path */
		preorder(-1, current, &min_cost, path, &path_min, candidate_path, &possible_path, 0);

	}
	return path_min;
}

/* preorder function to iterate through the tree from a certain node */

/* input args:
	parent_val = the value of parent node
	node = pointer to the node currently visiting
	min_cost = pointer to minimum cost record to compare against
	min_path = pointer to array that stores values of nodes along the min-cost path
	p_length = pointer to number of nodes in the smallest path
	current_path = pointer to an array that stores values of nodes of current path
	cp_length = POINTER to the number of nodes in the current path (use to move through tree)
	sumOfDiff = the current sum of path differences
*/
void preorder(TYPE parent_val, struct AVLnode * node, TYPE * min_cost, TYPE * min_path, int * p_length, TYPE * current_path, int * cp_length, TYPE sumOfDiff) {
	int i;

	/* put the current node value in the current path, increment cp_length */
	current_path[*cp_length] = node->val;
	(*cp_length)++;

	/* update the cumulative cost of the path, taking sums of differences */
	sumOfDiff += (TYPE)abs(parent_val - node->val);

	/* check if the current sum is larger than the min. if so, then backtrack */
	if (sumOfDiff > *min_cost) {
		(*cp_length)--;
		return;
		
	} else if (node->left || node->right) {
		/* if the left or right exists, recursive case */

		if (node->left) {
			preorder(node->val, node->left, min_cost, min_path, p_length, current_path, cp_length, sumOfDiff);
		}

		if (node->right) {
			preorder(node->val, node->right, min_cost, min_path, p_length, current_path, cp_length, sumOfDiff);
		}

	} else if (*min_cost > sumOfDiff) {
		/* updates the min cost path and the min path length */
		*min_cost = sumOfDiff;
		*p_length = *cp_length;
		/* replace the min path array */
		for (i = 0; i < (*p_length); i++) {
			min_path[i] = current_path[i];
		}
	} 

	/* decrement the current path length pointer to go back up the tree */
	(*cp_length)--;

}



/* -----------------------
Printing the contents of an AVL tree in breadth-first fashion
  param: pointer to a tree
  pre: assume that tree was initialized well before calling this function
*/
void printBreadthFirstTree(struct AVLTree *tree)
{
   
    /* FIX ME */
	/* breadth first search traverses each level of the tree */

	/* indexes of the beginning and end of the queue */
	int front = 0;
	int backIdx = 0; /* the index where the last element is */

	/* in this method, we will be printing the tree using a queue */
	struct AVLnode ** queue = (struct AVLnode **) malloc(tree->cnt * sizeof(struct AVLnode));
	struct AVLnode * current = tree->root;

	/* assign the first element in the queue */
	queue[backIdx] = current;
	backIdx++;

	/* continue printing out the tree */
	while (LT(front,backIdx)) {

		/* popped the front from the queue */
		current = queue[front];
		front++;

		printf("%d | ", current->val);

		/* condition where the left element is present, add to back */
		if (current->left) {
			queue[backIdx] = current->left;
			backIdx++;
		}

		/* condition where the right element is present, add to back */
		if (current->right) {
			queue[backIdx] = current->right;
			backIdx++;
		}
		
	}

	/* free the queue */
	free(queue);
	return;
}

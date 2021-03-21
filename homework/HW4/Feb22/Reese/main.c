#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include "avl.h"


int FindMinPath(struct AVLTree *tree, TYPE *path);
	/*Auxiliary functions for MinCost*/
	void findPath(struct AVLnode* current, int* current_min,  int current_cost, int* min_path, int* min_path_size, int* current_path, int* current_path_size);

void printBreadthFirstTree(struct AVLTree *tree);
	/*Auxiliary functions for BFS*/
	void printLevel(struct AVLnode* current, int level, int* printed_count);

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
    int current_min = 1000000; /*Set to arbitrarily high number so not comparing too low*/
	int current_path[100];
	int min_path_size = 0;
	int current_path_size = 0;

	findPath(tree->root, &current_min, 0, path, &min_path_size, current_path, &current_path_size);

	return min_path_size;
}

void findPath(struct AVLnode* current, int* current_min,  int current_cost, int* min_path, int* min_path_size, int* current_path, int* current_path_size)
{
	/*Break traversal branch if cost > min*/
	current_path[*current_path_size] = current->val;
	(*current_path_size)++;
	if(current_cost > *current_min) /*If current path cost is already more than minimum cost, go back immediately*/
	{
		(*current_path_size)--;
		return;
	}
	else if(current->left == NULL && current->right == NULL) /*If current is leaf, compare costs*/
	{
		if(current_cost < *current_min)
		{
			int i;
			(*current_min) = current_cost;
			for(i = 0; i < *current_path_size; i++) /*copy current path to minimum-cost path*/
				min_path[i] = current_path[i];
			(*min_path_size) = (*current_path_size);
		}
	}
	else /*Otherwise continue down tree*/
	{
		if(current->left != NULL)
		{
			current_cost += abs(current->val - current->left->val);
			findPath(current->left, current_min, current_cost, min_path, min_path_size, current_path, current_path_size);
		}
		if(current->right != NULL)
		{
			current_cost += abs(current->val - current->right->val);
			findPath(current->right, current_min, current_cost, min_path, min_path_size, current_path, current_path_size);
		}
	}
	(*current_path_size)--;
}


/* -----------------------
Printing the contents of an AVL tree in breadth-first fashion
  param: pointer to a tree
  pre: assume that tree was initialized well before calling this function
*/
void printBreadthFirstTree(struct AVLTree *tree)
{
    /* FIX ME */
	int height = h(tree->root);
	int i;
	int printed_count = 0;
	for(i = 0; i <= height; i++)
		printLevel(tree->root, i, &printed_count);
	
	printf("\nTree height: %d\n%d nodes printed\n", h(tree->root), printed_count);
}

/*Prints nodes at a given level*/
void printLevel(struct AVLnode* current, int level, int* printed_count)
{
	if(current == NULL)
		return;
	if(level == 0)
	{
		printf("%d ", current->val);
		(*printed_count)++;
	}
	else if(level > 0)
	{
		printLevel(current->left, level - 1, printed_count);
		printLevel(current->right, level - 1, printed_count);
	}
}
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include "avl.h"


int FindMinPath(struct AVLTree *tree, TYPE *path);
void printBreadthFirstTree(struct AVLTree *tree);
int minPathSum(struct AVLnode* root, TYPE* path, int index, int sum, TYPE* oPath, int oIndex, int oSum);


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

int FindMinPath(struct AVLTree* tree, TYPE* path) {
  /* FIX ME */
  TYPE* oPath;
  int index;
  index = minPathSum(tree->root, path, 0, 100000, path, 0, 10000);
  path = oPath;
  return index;
}

/*convert this into a while loop */

int minPathSum(struct AVLnode* root, TYPE* path, int index, int sum, TYPE* oPath, int oIndex, int oSum) {
  /*
  get the root value and the right and left child values
  find the abs difference, traverse to the lowest value
  update the path to the path
  */

  /* add to the root value to the index and increment the index */
  /* if we are at the leaf */
  int i;
  if (root != NULL) {
     path[index] = root->val;
      index++;

    if (root->right == NULL && root->left == NULL) {
      /* if the output sum is greater than the current sum, update the output sum */
      for (i = 1; i < index - 1; i++) {
        sum +=abs(path[i-1]- path[i]);
      }
      printf("%s%d\n", "calcSum", sum);
      printf("%s%d\n", "oSum", oSum);
      if (oSum > sum) {
        oPath = path;
        oSum = sum;
        oIndex = index;
        sum = 0;
        index = 0;
      }
      for (i = 0; i < index; i++)
        printf("%d ", path[i]);
      printf("\n");
      /* idea, make another function that compares and stores the new path, sum and index? */
    }

    /* if the left node is not null */
    if (root->left != NULL && root != NULL) {
      /*update the cost recursive call */
      sum = abs(root->val - root->left->val);
      printf("%s%d\n", "left", sum);
      minPathSum(root->left, path, index, sum, oPath, oIndex, oSum);
    }
    /* if the right node is not null */
    if (root->right != NULL && root != NULL) {
      /*update the cost recursive call */
      sum = abs(root->val - root->right->val);
      printf("%s%d\n", "right", sum);
      minPathSum(root->right, path, index, sum, oPath, oIndex, oSum);
    }
  }
  return oIndex;
}
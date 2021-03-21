#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sinisa_dijkstra.h"
#define INFINITY 9999
#define MAX 10

/* -----------------------
The main function
  param: argv = pointer to the name (and path) of a file that the program reads
*/
int main(int argc, char** argv) {
    int A[MAX][MAX],i,j,n,u;
	printf("Enter no. of vertices:");
	scanf("%d",&n);
	printf("\nEnter the adjacency matrix:\n");
	
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&A[i][j]);
	
	printf("\nEnter the starting node:");
	scanf("%d",&u);
	Dijkstra(A, 0, 0);
	
	return 0;
}

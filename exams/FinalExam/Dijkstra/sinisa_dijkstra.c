#include<stdio.h>
#include<curses.h>
#include "sinisa_dijkstra.h"
#define INFINITY 9999
#define MAX 10

/* check whether the node is visited */
bool allVisited(int* visit, int size) {
    int i;
    for (i = 0; i < size; i++) {
        if (visit[i] != 1) {
            return false;
        }
    }
    
    return true;
}

/* find unprocessed node closest to source */
int findMin(int* visited, int* dist, int size)
{
	int min = INFINITY, min_index, v;
	for (v = 0; v < size; v++)
		if (!visited[v] && dist[v] < min) {
			min = dist[v];
			min_index = v;
		}
	return min == INFINITY ? INFINITY : min_index;
}

int * Dijkstra(TYPE ** A, int size, int start) {
    /* Three auxiliary arrays */
    /* min distance of every node to start */
    TYPE dist[size];
    /* flag: min-cost is already computed for that node */
    int visited[size];
    /* index of the previous node in the path to start */
    int previous[size];
    int i, j;

    /* Step 1: initialize dist[] and processed[] */
    for (i = 0; i < size; i++) {
        visited[i] = 0;
        previous[i] = start;
        /* set distance from the source */

        /* if node i is not connected to source: */
            /* dist[i] = INFINITY */
        /* else: */
            /* dist[i] = A[start][i]; adjacent*/

        dist[i] = A[start][i] ? A[start][i] : INFINITY;        
    }

    /* Step 2: Loop until all nodes are visited */
    while (!allVisited(visited, size)) {
        /* find unprocessed node closest to source */
        i = findMin(visited, dist, size); /* i has min cost */
        visited[i] = 1; /* do not visit node i again */

        /* update distances of neighbors j of i */
        for (j = 0; j < size; j++) {
            if (!visited[j] && A[i][j]) {
                if (dist[j] > dist[i] + A[i][j]) {
                    dist[j] = dist[i] + A[i][j];
                    previous[j] = i;
                }
                
            }
        }
    }

    return previous; /* step 3 */
}


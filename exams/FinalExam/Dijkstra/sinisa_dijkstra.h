#include <stdbool.h>

# ifndef TYPE
# define TYPE   int
# endif

bool allVisited(int* visit, int size);
int findMin (int * visited, TYPE * dist, int size);
int * Dijkstra(TYPE ** A, int size, int start);
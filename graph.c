#include<stdlib.h>
#include<stdio.h>
#include"List.h"
#include"graph.h"

/* TODO: implement graph constructor
Instantiate a graph given the number of vertices
There are no edges at instantiation
*/

graph createGraph(int num) {
	graph G = (graphObj*)malloc(sizeof(graphObj));
	G -> n = num;
	G -> matrix = (int**)malloc(num * sizeof(int*));
	for (int i = 0; i < num; i++) {
		G -> matrix[i] = (int*)malloc(num * sizeof(int));
	}

	// Fill initial graph with 0 (no vertices)
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			G -> matrix[i][j] = 0;
		}
	}

	return G;
}


/* TODO: implement graph destructor
destruct graph and free allocated memory as appropriate
*/

void destructGraph(graph g) {
	for (int i = 0; i < (g -> n); i++) {
		free(g -> matrix[i]);
	}
	free(g -> matrix);
	free(g);
}



// TODO: implement addEdge function

void addEdge(graph g, int i, int j) {
	g -> matrix[i][j] = 1;
	g -> matrix[j][i] = 1;
}




// TODO: implement removeEdge function

void removeEdge(graph g, int i, int j) {
	g -> matrix[i][j] = 0;
	g -> matrix[j][i] = 0;
}


// TODO: implement hasEdge function

int hasEdge(graph g, int i, int j) {
	int x = g -> matrix[i][j];
	if (x == 1) {
		return 1;
	}
	return 0;
}


// TODO: implement outEdges function

void outEdges(graph g, int i, node** list) {
	for (int j = 0; j < (g -> n); j++) {
		if (g -> matrix[i][j] == 1) {
			node *n = createList(j);
			insertList(list, n);
		}
	}
}


// TODO: implement inEdges function

void inEdges(graph g, int j, node** list) {
	for (int i = 0; i < (g -> n); i++) {
		if (g -> matrix[i][j] == 1) {
			node *n = createList(i);
			insertList(list, n);
		}
	}
}


// TODO: implement getNumVer

int getNumVer(graph g) {
	return g -> n;
}




// TODO: implement printGraph

void printGraph(graph g) {
	if (g == NULL) {
		return;
	}

	printf("\nPRINTING GRAPH");
	for (int i = 0; i < (g->n); i++) {
		printf("\n");
		for (int j = 0; j < (g->n); j++) {
			printf("%d ", g -> matrix[i][j]);
		}
	}
}

int isTaken(graph g, int pIndex) {
	for (int i = 0; i < (g->n); i++) {
		if ( g->matrix[pIndex][i] == 1 ) {
			return 1;
		}
		if ( g-> matrix[i][pIndex] == 1) {
			return 1;
		}
	}
	return 0;
}

int pullMatchIndex(graph g, int i) {
	if (isTaken(g, i)) {
		for (int j = 0; j < (g->n); j++) {
			if ( g->matrix[i][j] == 1 ) {
				return j;
			}
		}
	}
	return -1;
}




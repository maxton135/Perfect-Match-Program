#include<stdio.h>
#include"List.h"
#include"graph.h"
#include<stdlib.h>
#include<string.h>

/* Helper Functions */

// Print all edges (matches) of a graph
void printGraphPairs(graph g) {
	int numPairs = (g->n)/2;
	printf("\nM-Optimal matches are: ");
	for (int i = 0; i < numPairs; i++) {
		for (int j = numPairs; j < (g->n); j++) {
			if (hasEdge(g, i, j)) {
				printf(" (%d, %d)", i, j);
			}
		}
	}
}

/* TODO: implement the deferred acceptance/Gale-Shapley algorithm
- Note that we want to find the M-optimal set of stable matches
- You can write your own helper functions	
*/

void galeshapley(int numVer, node **pref) {
	// Create graph (everything set to 0)
	graph g = createGraph(numVer);

	int numMales = numVer/2;
	int done = 0;

	while (!done) {

		// Check if there are any single males
		for (int i = 0; i < numMales; i++) {
			if (!isTaken(g, i)) {

				// Iterate through all females
				node *ptr = pref[i];

				// Traverse to end of linked list for 1st priority
				while (ptr -> next != NULL) {
					ptr = ptr -> next;
				}
				while (ptr != NULL) {
					int femaleIndex = getValue(ptr);
					if (!isTaken(g, femaleIndex)) {
						// Match
						addEdge(g, i, femaleIndex);
						break;
					}
					else {
						// Check if woman has i as higher priority than her current match
						int currentMatch = pullMatchIndex(g, femaleIndex);

						node *temp = pref[femaleIndex];
						int count = 0;
						int c1 = numVer;
						int c2 = numVer;
						while (temp != NULL) {
							if (getValue(temp) == i) {
								c1 = count;
							}
							if (getValue(temp) == currentMatch) {
								c2 = count;
							}
							count++;
							temp = temp -> next;
						}

						// Compare indexes in priority and switch match if higher prioirty
						if (c1 > c2) {
							// delete current match
							// add this new match
							removeEdge(g, femaleIndex, currentMatch);
							addEdge(g, femaleIndex, i);
							break;
						}

					}
					ptr = ptr -> prev;
				}
			}
		}
		// Check if any males have no match, if everyone has match then terminate loop
		int x = 0;
		for (int i = 0; i < numMales; i++) {
			if (!isTaken(g, i)) {
				x = 1;
			}
		}
		if (x == 0) {
			done = 1;
		}
	}
	// print matches
	printGraphPairs(g);
	destructGraph(g);
	return;
}




/* TODO: implement the main() function
Here, you would read in the input (from stdin) and execute deferred acceptance algorithm
and print out the set of M-optimal stable matches.
*/
int main(void)
{
	// Find number of people (vertices)

	int personIndex = 0;
	int done = 0;
	char line[100];
	char *token;

	fgets(line, 100, stdin);
	int verNum = atoi(line);

	node **pref = (node**)malloc(verNum * sizeof(node*));
	for (int i = 0; i < verNum; i++) {
		pref[i] = NULL;
	}

	while (!done) {
		if ( fgets(line, 100, stdin) != NULL ) {
			token = strtok(line, " ");
			while( token != NULL ) {
				int num = atoi(token);

				node *new = createList(num);
				insertList(&pref[personIndex], new);

				token = strtok(NULL, " ");
			}
			personIndex++;
		}
		else {
			done = 1;
		}
	}

	// Call matching function - prints best matches
	galeshapley(verNum, pref);

	// Free preference list
	for (int i = 0; i < verNum; i++) {
		free(pref[i]);
	}
	free(pref);

	return 0;
}
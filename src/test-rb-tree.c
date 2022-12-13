#include "rb-tree.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define READFILE "RBTree_input.txt"
#define DRAWFILE "RBTree_drawing.svg"

#define MAX_KEY 1000000000
#define MAX_NODE 100000000

// a function to copy a random number into a variable
void randInt(int min, int max, int *x) {
	int range = max - min + 1;
	int limit = RAND_MAX - RAND_MAX % range;
	int rnd;
	do {
		rnd = rand();
	} while (rnd >= limit);
	*x = min + rnd % range;
}

// a function to calculate the complexity of a red-black tree
/**
 * @param n the number of nodes
 * @param time the time it took to insert the nodes
 * @return the complexity of the algorithm
 */
double complexityRBTree(int n, double time) {
	return time / (n * log10(n));
}

void populateTree(RBTree tree, int *tab, int n) {
	for (int i = 0; i < n; i++) {
		RBTree_insert(tree, tab[i]);
		//printf("inserted %d\n", tab[i]);
	}	
}

void populateTabWithRandomNumber(int *tab, int n, int max_key) {
	for (int i = 0; i < n; i++) {
		// Scale the random number to the desired range (0 to 1000)
		int x;
		randInt(0, max_key, &x);
		tab[i] = rand() % max_key;
	}
}

void testInsertion(RBTree tree, int *tab, int n, int max_key, int number_of_run) {
	double total_time = 0;

	for(int i = 0; i < number_of_run; i++) {
		if (tree != NULL) {
			RBTree_free(tree);
		}
		RBTree_destroy();
		tree = RBTree_create();

		clock_t debut = clock();
		populateTree(tree, tab, n);
		clock_t fin = clock();

		double temps = (double)(fin - debut) / CLOCKS_PER_SEC;
		temps *= 1000;
		total_time += temps;

		//printf("temps [%d]: %f ms (%d nodes, 0 - %d max key)\n", i, temps, n, max_key);

		//printf("temps [%d]: %f ms\n", i, temps);
		char filename[200];
		sprintf(filename, "results/RBTree_drawing_%d.svg", i + n);
		//RBTree_draw(tree, filename);
		//printf("finished %d\n", i + n);q
	}

	printf("total time: %f ms\n", total_time);
	printf("number of run: %d\n", number_of_run);
	printf("number of node: %d\n", n);
	printf("max key: %d\n", max_key);
	double average_time = total_time / number_of_run;
	printf("average time: %f ms\n", average_time);

	double c = 100000.0;
	printf("log(n) c: %f\n", log10(n));
	printf("\ttime / (log(n)): %f ms\n", total_time / log10(n));
	printf("\tavg_time / (log(n)): %f ms\n", average_time / log10(n));

	printf("n log(n): %f\n", n * log10(n));
	printf("\ttime / (n * log(n)): %f ms\n", total_time / (n * log10(n)));
	printf("\tavg_time / (n * log(n)): %f ms\n", average_time / (n * log10(n)));


	printf("n log2(n): %f\n", n * log10(n));
	printf("\ttime / (n * log2(n)): %f ms\n", complexityRBTree(n, total_time));
	printf("\tavg_time / (n * log2(n)): %f ms\n", complexityRBTree(n, average_time));

	// complexite theorique
	printf("\n\n\n");
}

void testSearch(RBTree tree, int *tab, int n, int max_key, int number_of_run) {
	double total_time = 0;
	if (tree != NULL) {
		RBTree_free(tree);
	}
	RBTree_destroy();
	tree = RBTree_create();

	populateTree(tree, tab, n);

	for(int i = 0; i < number_of_run; i++) {
		clock_t debut = clock();
		RBTree_search(tree, x);
		clock_t fin = clock();

		double temps = (double)(fin - debut) / CLOCKS_PER_SEC;
		temps *= 1000;
		total_time += temps;

		//printf("temps [%d]: %f ms (%d nodes, 0 - %d max key)\n", i, temps, n, max_key);

		//printf("temps [%d]: %f ms\n", i, temps);
		char filename[200];
		sprintf(filename, "results/RBTree_drawing_%d.svg", i + n);
		//RBTree_draw(tree, filename);
		//printf("finished %d\n", i + n);q
	}

	printf("total time: %f ms\n", total_time);
	printf("number of run: %d\n", number_of_run);
	printf("number of node: %d\n", n);
	printf("max key: %d\n", max_key);
	double average_time = total_time / number_of_run;
	printf("average time: %f ms\n", average_time);

	double c = 100000.0;
	printf("log(n) c: %f\n", log10(n));
	printf("\ttime / (log(n)): %f ms\n", total_time / log10(n));
	printf("\tavg_time / (log(n)): %f ms\n", average_time / log10(n));

	printf("n log(n): %f\n", n * log10(n));
	printf("\ttime / (n * log(n)): %f ms\n", total_time / (n * log10(n)));
	printf("\tavg_time / (n * log(n)): %f ms\n", average_time / (n * log10(n)));
}

int main(int argc, char *argv[]) {
	printf("Test of the red-black tree\n");
  srand(time(NULL));
	
	RBTree tree = NULL,
		tmp = NULL;
	int cmd = 0;


	
	/*if (tree != NULL) {
		RBTree_free(tree);
	}
	tree = RBTree_create();
	populateTree(&tree, 50, 1000);
	RBTree_draw(tree, DRAWFILE);*/

	char *endptr1, *endptr2, *endptr3;

	//int max_key = 1000;
	//printf("max key : %d\n", max_key);

	//long int number_of_run = strtol(argv[3], &endptr3, 10);
	int number_of_run = 100;
	//printf("number of run : %d\n", number_of_run);

	int *tab = malloc(sizeof(int) * MAX_NODE);
	//printf("tab created\n");
	for (int i = 0; i < MAX_NODE; i++) {
		tab[i] = rand() % MAX_KEY;
	}
	printf("tab created\n");

	//testInsertion(tree, tab, 10, MAX_KEY, 100);
	//testInsertion(tree, tab, 100, 100000000, 100);
	//testInsertion(tree, tab, 1000, 100000000, 100);
	//testInsertion(tree, tab, 10000, 100000000, 100);
	//testInsertion(tree, tab, 100000, 100000000, 100);
	testInsertion(tree, tab, 1000000, 100000000, 100);
	testInsertion(tree, tab, 10000000, 100000000, 100);
	//testInsertion(tree, tab, 100000000, 100000000, 100);

	/* We need to free the tree. */
	if (tree != NULL) {
		RBTree_free(tree);
	}
	RBTree_destroy();

	return 0;
}

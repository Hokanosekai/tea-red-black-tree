#include "rb-tree.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define READFILE "RBTree_input.txt"
#define DRAWFILE "RBTree_drawing.svg"

#define MAX_KEY 10000
#define MAX_NODE 1000000

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
	
}

void populateTabWithRandomNumber(int *tab, int n, int max_key) {
	for (int i = 0; i < n; i++) {
		// Scale the random number to the desired range (0 to 1000)
		int x;
		randInt(-max_key, max_key, &x);
		tab[i] = rand() % max_key;
	}
}

void testRBTree(RBTree tree, int *tab, int n, int max_key, int number_of_run) {
	double total_time = 0;

	double total_time_search = 0;
	double total_time_delete = 0;
	double total_time_insert = 0;

	for(int i = 0; i < number_of_run; i++) {
		if (tree != NULL) {
			RBTree_free(tree);
		}
		RBTree_destroy();
		tree = RBTree_create();

		// Mesure du temps d'exécution de l'algorithme d'insertion
		clock_t start_insert = clock();
		for (int i = 0; i < n; i++) {
			RBTree_insert(tree, tab[i]);
		}	
		clock_t end_insert = clock();

		// Mesure du temps d'exécution de l'algorithme de recherche
		clock_t start_search = clock();
		for (int i = 0; i < n; i++) {
			RBTree_search(tree, tab[i]);
		}
		clock_t end_search = clock();

		// Mesure du temps d'exécution de l'algorithme de suppression
		clock_t start_delete = clock();
		for (int i = 0; i < n; i++) {
			RBTree_delete(tree, tab[i]);
		}
		clock_t end_delete = clock();


		double temps_insert = (double)(end_insert - start_insert) / CLOCKS_PER_SEC;
		temps_insert *= 1000;

		double temps_search = (double)(end_search - start_search) / CLOCKS_PER_SEC;
		temps_search *= 1000;

		double temps_delete = (double)(end_delete - start_delete) / CLOCKS_PER_SEC;
		temps_delete *= 1000;

		total_time_insert += temps_insert;
		total_time_search += temps_search;
		total_time_delete += temps_delete;

		total_time += temps_insert + temps_search + temps_delete;
	}

	double average_time_insert = total_time_insert / number_of_run;
	double average_time_search = total_time_search / number_of_run;
	double average_time_delete = total_time_delete / number_of_run;

	double average_time = total_time / number_of_run;

	// I want to print the result in a CSV file


	FILE *f = fopen("../data/data_100k_1M_char.csv", "a");
	if (f == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	fprintf(f, "%d;%d;%d;%f;%f;%f;%f;%f;%f;%f;%f;%f\n", n, max_key, number_of_run, total_time, average_time, average_time_insert, average_time_search, average_time_delete, total_time_insert, total_time_search, total_time_delete, log10f(n));
	fclose(f);
	/*
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
	printf("\n\n\n");*/
}

int main(int argc, char *argv[]) {
	//printf("Test of the red-black tree\n");
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
	int number_of_run = 10;
	//printf("number of run : %d\n", number_of_run);

	int *tab = malloc(sizeof(int) * MAX_NODE);
	//printf("tab created\n");
	for (int i = 0; i < MAX_NODE; i++) {
		tab[i] = rand() % MAX_KEY;
	}
	printf("tab filled\n");
	//printf("tab created\n");

	FILE *f = fopen("../data/data_100k_1M_char.csv", "w");
	if (f == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	fprintf(f, "n;max_key;number_of_run;total_time;average_time;average_time_insert;average_time_search;average_time_delete;total_time_insert;total_time_search;total_time_delete;Ologn\n");
	fclose(f);

	//testRBTree(tree, tab, 10, MAX_KEY, number_of_run);
	//testRBTree(tree, tab, 100, MAX_KEY, number_of_run);
	//testRBTree(tree, tab, 1000, MAX_KEY, number_of_run);
	//testRBTree(tree, tab, 10000, MAX_KEY, number_of_run);
	int start = 0;
	int step = 10000;
	for (int i = 0; i < 100; i++) {
		start += step;
		printf("[WORKING] testing RBT for %d nodes\n", start);
		testRBTree(tree, tab, start, MAX_KEY, number_of_run);
		printf("[DONE] testing RBT for %d nodes\n", start);
	}

	printf("[END] tests\n");

	//testInsertion(tree, tab, 100000, 100000000, 100);
	//testRBTree(tree, tab, 1000000, 100000000, 100);
	//testRBTree(tree, tab, 10000000, 100000000, 100);
	//testInsertion(tree, tab, 100000000, 100000000, 100);

	return 0;
}

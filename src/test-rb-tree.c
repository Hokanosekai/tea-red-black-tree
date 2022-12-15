#include "rb-tree.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define RANDOM_MAX 1000000
#define FILENAME "../data/data_100k.csv"

void testRBTree(RBTree tree, int *tab, int n, int number_of_run) {
	double total_time = 0;

	double total_time_search = 0;
	double total_time_delete = 0;
	double total_time_insert = 0;


	for(int i = 0; i < number_of_run; i++) {
		printf("Run %d / %d\n", i + 1, number_of_run);
		if (tree != NULL) {
			RBTree_free(tree);
		}
		tree = RBTree_create();

		// Mesure du temps d'exécution de l'algorithme d'insertion
		clock_t start_insert = clock();
		for (int j = 0; j < n; j++) {
			RBTree_insert(tree, tab[j]);
		}
		clock_t end_insert = clock();

		// Mesure du temps d'exécution de l'algorithme de recherche
		clock_t start_search = clock();
		for (int j = 0; j < n; j++) {
			RBTree_search(tree, tab[j]);
		}
		clock_t end_search = clock();

		// Mesure du temps d'exécution de l'algorithme de suppression
		clock_t start_delete = clock();
		for (int j = 0; j < n; j++) {
			RBTree_delete(tree, tab[j]);
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

		/*if (tree != NULL) {
			RBTree_free(tree);
			RBTree_destroy();
		}*/
	}

	double average_time_insert = total_time_insert / number_of_run;
	double average_time_search = total_time_search / number_of_run;
	double average_time_delete = total_time_delete / number_of_run;

	double average_time = total_time / number_of_run;


	FILE *f = fopen(FILENAME, "a");
	if (f == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	fprintf(f, "%d;%d;%d;%f;%f;%f;%f;%f;%f;%f;%f;%f\n", n, RANDOM_MAX, number_of_run, total_time, average_time, average_time_insert, average_time_search, average_time_delete, total_time_insert, total_time_search, total_time_delete, log10f(n));
	fclose(f);
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
	
	RBTree tree = NULL,
		tmp = NULL;

	char *endptr1, *endptr2;

	long int n = strtol(argv[1], &endptr1, 10);
	long int number_of_run = strtol(argv[2], &endptr2, 10);

	if (n <= 0 || number_of_run <= 0) {
		printf("Error: the number of nodes and the number of run must be positive integers");
		exit(1);
	}

	int *tab = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		tab[i] = rand() % RANDOM_MAX;
	}
	
	printf("tab filled\n");

	/*FILE *f1 = fopen(FILENAME, "w");
	if (f1 == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	fprintf(f1, "n;max_key;number_of_run;total_time;average_time;average_time_insert;average_time_search;average_time_delete;total_time_insert;total_time_search;total_time_delete;logn\n");
	fclose(f1);*/

	printf("[WORKING] testing RBT for %d nodes\n", n);
	testRBTree(tree, tab, n, number_of_run);
	printf("[DONE] testing RBT for %d nodes\n", n);

	printf("[END] tests\n");
	return 0;
}

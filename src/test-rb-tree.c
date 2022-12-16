#include "rb-tree.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define RANDOM_MAX 1000000
#define FILENAME "../data/rbtree/data_output.csv"

void createFileWithRandomNumbers(int n, char *filename) {
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	for (int i = 0; i < n; i++) {
		fprintf(file, "%d", rand() % RANDOM_MAX);
		if (i != n - 1) {
			fprintf(file, ",");
		}
	}
	fclose(file);
}

void createFileWithRandomChars(int n, char *filename) {
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	for (int i = 0; i < n; i++) {
		fprintf(file, "%c%c%c%c%c%c%c%c%c%c", rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a', rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a');
		if (i != n - 1) {
			fprintf(file, ",");
		}
	}
	fclose(file);
}

void createFileWithSortedNumbers(int n, char *filename) {
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	for (int i = 0; i < n; i++) {
		fprintf(file, "%d", i);
		if (i != n - 1) {
			fprintf(file, ",");
		}
	}
	fclose(file);
}

int compare_strings(const void* a, const void* b) {
    // Convert the pointers to char* and dereference them
    const char* s1 = *(const char**)a;
    const char* s2 = *(const char**)b;
    // Compare the strings using strcmp
    return strcmp(s1, s2);
}

void createFileWithSortedChars(int n, char *filename) {
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	char **tab = malloc(sizeof(char) * 10 * n);

	for (int i = 0; i < n; i++) {
		char *str = malloc(sizeof(char) * 10);
		sprintf(str, "%c%c%c%c%c%c%c%c%c%c", rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a', rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a');
		tab[i] = str;
	}

	qsort(tab, sizeof(tab) / sizeof(char*), sizeof(char*), compare_strings);

	for (int i = 0; i < n; i++) {
		fprintf(file, "%s", tab[i]);
		if (i != n - 1) {
			fprintf(file, ",");
		}
	}

	fclose(file);
}

void readDataFromFile(char *filename, int *tab, int n) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	char *line = NULL;
	size_t len = 0;
	size_t read;

	while ((read = getline(&line, &len, file)) != -1) {
		char *token = strtok(line, ",");
		for (int i = 0; i < n; i++) {
			tab[i] = atoi(token);
			token = strtok(NULL, ",");
		}
	}
	fclose(file);
}

void readCharDataFromFile(char *filename, char **tab, int n) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	char *line = NULL;
	size_t len = 0;
	size_t read;

	while ((read = getline(&line, &len, file)) != -1) {
		char *token = strtok(line, ",");
		for (int i = 0; i < n; i++) {
			printf("%s\n", token);
			tab[i] = token;
			token = strtok(NULL, ",");
		}
	}
	fclose(file);
}

void testRBTree(RBTree tree, char **tab, int n, int number_of_run) {
	double total_time = 0;

	double total_time_search = 0;
	double total_time_delete = 0;
	double total_time_insert = 0;

	for(int i = 0; i < number_of_run; i++) {
		printf("Run %d / %d\n", i + 1, number_of_run);
		if (tree != NULL) {
			RBTree_free(tree);
		}
		//RBTree_destroy();
		tree = RBTree_create();


		// Mesure du temps d'exécution de l'algorithme d'insertion
		clock_t start_insert = clock();
		for (int j = 0; j < n; j++) {
			char *str = malloc(sizeof(char) * (strlen(tab[j]) + 1));
			strcpy(str, tab[j]);
			//printf("\tInserting %s elements\n", str);
			RBTree_insert(tree, str);
		}
		clock_t end_insert = clock();

		double temps_insert = (double)(end_insert - start_insert) / CLOCKS_PER_SEC;
		temps_insert *= 1000;

	  printf("\tInsert done in %f ms\n", temps_insert);

		// Mesure du temps d'exécution de l'algorithme de recherche
		clock_t start_search = clock();
		for (int j = 0; j < n; j++) {
			char *str = malloc(sizeof(char) * (strlen(tab[j]) + 1));
			strcpy(str, tab[j]);
			RBTree_search(tree, str);
		}
		clock_t end_search = clock();

		double temps_search = (double)(end_search - start_search) / CLOCKS_PER_SEC;
		temps_search *= 1000;

		printf("\tSearch done in %f ms\n", temps_search);

		// Mesure du temps d'exécution de l'algorithme de suppression
		clock_t start_delete = clock();
		for (int j = 0; j < n; j++) {
			char *str = malloc(sizeof(char) * (strlen(tab[j]) + 1));
			strcpy(str, tab[j]);
			RBTree_delete(tree, str);
		}
		clock_t end_delete = clock();

		double temps_delete = (double)(end_delete - start_delete) / CLOCKS_PER_SEC;
		temps_delete *= 1000;

		printf("\tDelete done in %f ms\n", temps_delete);

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
	
	RBTree tree = NULL;
	char *endptr1, *endptr2;

	long int number_of_node;
	long int iterations;

	char **tab;

	if (argc >= 3 && argc <= 4) {

		number_of_node = strtol(argv[1], &endptr1, 10);
		tab = malloc(sizeof(char) * 10 * number_of_node);

		if (strcmp(argv[2], "--create-random") == 0) {
			char filename[100];
			sprintf(filename, "data_%d_%d_random.txt", number_of_node, RANDOM_MAX);
			createFileWithRandomNumbers(number_of_node, filename);
			printf("File %s created\n", filename);
			exit(0);
		} else if (strcmp(argv[2], "--create-sorted") == 0) {
			char filename[100];
			sprintf(filename, "data_%d_%d_sorted.txt", number_of_node, RANDOM_MAX);
			createFileWithSortedNumbers(number_of_node, filename);
			printf("File %s created\n", filename);
			exit(0);
		} else if (strcmp(argv[2], "--create-random-char") == 0) {
			char filename[100];
			sprintf(filename, "data_%d_%d_sorted.txt", number_of_node, RANDOM_MAX);
			createFileWithRandomChars(number_of_node, filename);
			printf("File %s created\n", filename);
			exit(0);
		} else if (strcmp(argv[2], "--create-sorted-char") == 0) {
			char filename[100];
			sprintf(filename, "data_%d_%d_sorted.txt", number_of_node, RANDOM_MAX);
			createFileWithSortedChars(number_of_node, filename);
			printf("File %s created\n", filename);
			exit(0);
		} else {
			iterations = strtol(argv[2], &endptr2, 10);

			if (argc == 4) {
				readCharDataFromFile(argv[3], tab, number_of_node);
				printf("size of tab : %d\n", sizeof(tab));
				printf("Data read from file %s\n", argv[3]);
			} else {
				for (int i = 0; i < number_of_node; i++) {
					char *str = malloc(sizeof(char) * 10);
					sprintf(str, "%c%c%c%c%c%c%c%c%c%c", rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a', rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a',rand() % 26 + 'a');
					tab[i] = str;
					//tab[i] = rand() % 26 + rand() % 26 + rand() % 26 + rand() % 26 + rand() % 26 + rand() % 26 + rand() % 26;
				}
				printf("Data generated randomly\n");
			}

			// If the file already contains data header, we don't write it again
			FILE *f = fopen(FILENAME, "r");
			if (f == NULL) {
				f = fopen(FILENAME, "w");
				fprintf(f, "nodes;RANDOM_MAX;iterations;total_time;average_time;average_time_insert;average_time_search;average_time_delete;total_time_insert;total_time_search;total_time_delete;Olog(n)\n");
				fclose(f);
			} else {
				printf("File %s already exists, we don't write the header again\n", FILENAME);
				fclose(f);
			}

			printf("[WORKING] testing RBT for %d nodes\n", number_of_node);
			testRBTree(tree, tab, number_of_node, iterations);
			printf("[DONE] testing RBT for %d nodes\n", number_of_node);
		}
	} else {
		fprintf(stderr, "Usage: %s number_of_node iterations <data_input_file>", argv[0]);
		exit(1);
	}

	return 0;
}

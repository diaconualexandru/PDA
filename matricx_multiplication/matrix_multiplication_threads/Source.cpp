#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <omp.h>

#define SIZE 1000

double first[SIZE][SIZE], second[SIZE][SIZE], rez[SIZE][SIZE];

using namespace std;

int main() {


	int i, j;
	char c;


	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++) {
			first[i][j] = 0.9;
		}

	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++) {
			second[i][j] = 0.9;
		}

	/*for (i = 0; i < SIZE; i++) {
	for (j = 0; j < SIZE; j++) {
	printf(" %f", first[i][j]);
	}
	printf("\n");
	}

	printf("\n\n");

	for (i = 0; i < SIZE; i++) {
	for (j = 0; j < SIZE; j++) {
	printf(" %f", second[i][j]);
	}
	printf("\n");
	}

	printf("\n\n");*/

	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++) {
			rez[i][j] = 0;
		}
	clock_t start = clock(), diff;

#pragma omp parallel for
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				double dot = 0;
				for (int k = 0; k < SIZE; k++) {
					dot += first[i][k] * second[k][j];
				}
				rez[i][j] = dot;
			}
		}

	diff = clock() - start;
	/*for (i = 0; i < SIZE; i++) {
	for (j = 0; j < SIZE; j++) {
	printf(" %f", rez[i][j]);
	}
	printf("\n");
	}*/
	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("Time taken %d seconds %d milliseconds", msec / 1000, msec % 1000);
	
	cin >> c;

	return 0;
}
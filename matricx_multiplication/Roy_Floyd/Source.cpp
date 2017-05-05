#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 6

int main(int argc, char *argv[])
{
	int a[SIZE][SIZE] = {
		{ 0, 2, 5, 999, 999, 999 },
		{ 999, 0, 7, 1, 999 , 8 },
		{ 999, 999, 0, 4, 999, 999 },
		{ 999, 999, 999, 0, 3, 999 },
		{ 999, 999, 2, 999, 0, 3 },
		{ 999, 5, 999, 2, 4, 0 }
	};
	int result[SIZE][SIZE];
	int numprocs, rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	for (int k = 0; k < SIZE; k++)
	{
		if (k % (SIZE / numprocs) == rank)
		{
			MPI_Bcast(a[k], SIZE, MPI_INT, rank, MPI_COMM_WORLD);
		}
		for (int i = rank; i < SIZE; i = i + numprocs)
		{
			for (int j = 0; j < SIZE; j++)
			{
				if (a[i][j] > a[i][k] + a[k][j])
					a[i][j] = a[i][k] + a[k][j];
			}
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}
	MPI_Reduce(a, result, SIZE*SIZE, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
	if (rank == 0)
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				printf("%d\t", result[i][j]);
			}
			printf("\n");
		}
	}
	

	MPI_Finalize();
}

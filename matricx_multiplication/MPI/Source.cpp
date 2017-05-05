#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
#define VECTORSIZE 20

int searchNumber(int* searchArray, int start, int end, int numberSearched)
{
	int resultIterator = -1;
	for (int i = start; i < end; i++)
	{
		if (searchArray[i] == numberSearched)
		{
			resultIterator = i;
		}
	}
	return resultIterator;
}

int main(int argc, char *argv[])
{
	int numprocs, rank, sendcount, recvcount, source;
	int numberSearched = 5;
	int sendbuf[VECTORSIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	int result;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	if (numprocs == SIZE) {
		source = 1;
		sendcount = VECTORSIZE / SIZE;
		recvcount = VECTORSIZE / SIZE;
		MPI_Bcast(sendbuf, sendcount, MPI_INT, source, MPI_COMM_WORLD);
		int maxPosition = searchNumber(sendbuf, sendcount*rank, sendcount * (rank + 1), numberSearched);
		MPI_Reduce(&maxPosition, &result, 1, MPI_INT, MPI_MAX, 1, MPI_COMM_WORLD);
		if (rank == source)
		{
			if (result >= 0)
			{
				printf("Max position of number %d is %d", numberSearched, result);
			}
			else
			{
				printf("The number %d could not be found", numberSearched);
			}
		}
	}
	else
		printf("Must specify %d processors. Terminating.\n", SIZE);
	
	MPI_Finalize();
}



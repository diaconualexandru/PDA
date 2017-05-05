#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
#define VECTORSIZE 20

int* searchNumber(int* searchArray, int start, int end, int numberSearched, int rank)
{
	int iteratorArray[VECTORSIZE / SIZE];
	int iterator = 0;
	for (int i = start; i < end; i++)
	{
		if (searchArray[i] == numberSearched)
		{
			iteratorArray[iterator] = VECTORSIZE / SIZE * rank + i;
			iterator++;
		}
		else
		{
			iteratorArray[iterator] = VECTORSIZE;
			iterator++;
		}
	}
	return iteratorArray;
}

int main(int argc, char *argv[])
{
	int numprocs, rank, sendcount, recvcount, source;
	int numberSearched = 5;
	int sendbuf[VECTORSIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 5, 12, 13, 5, 5, 16, 17, 18, 19, 5 };
	int recvbuf[VECTORSIZE];
	int recvAllPosBuff[VECTORSIZE];
	int result;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	if (numprocs == SIZE) {
		source = 1;
		sendcount = VECTORSIZE;
		recvcount = VECTORSIZE / SIZE;
		MPI_Scatter(sendbuf, recvcount, MPI_INT, recvbuf, recvcount, MPI_INT, source, MPI_COMM_WORLD);
		int* sendPosBuff = searchNumber(recvbuf, 0, recvcount, numberSearched, rank);
		MPI_Gather(sendPosBuff, recvcount, MPI_INT, recvAllPosBuff, recvcount, MPI_INT, source, MPI_COMM_WORLD);
		if (rank == source)
		{
			if (sizeof(recvAllPosBuff) != 0)
			{
				for (int i = 0; i < sendcount; i++)
				{
					if (recvAllPosBuff[i] != VECTORSIZE)
					{
						printf("The number %d is found in position %d\n", numberSearched, recvAllPosBuff[i]);
					}
				}
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
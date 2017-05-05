#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
#define VECTORSIZE 20

int IsPrime(int number)
{
	if (number < 2)
	{
		return 0;
	}
	for (int i = 2; i * i <= number; i++)
	{
		if (number % i == 0)
		{
			return 0;
		}
	}
	return 1;
}

int main(int argc, char *argv[])
{
	int numprocs, rank, sendcount, recvcount, source;
	int sendbuf[VECTORSIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	int recvbuf[VECTORSIZE];
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	if (numprocs == SIZE) {
		source = 1;
		sendcount = VECTORSIZE / SIZE;
		recvcount = VECTORSIZE / SIZE;
		MPI_Scatter(sendbuf, sendcount, MPI_INT, recvbuf, recvcount, MPI_INT, source,
			MPI_COMM_WORLD);
		for (int i = sendcount * rank; i < sendcount * (rank + 1); i++)
		{
			if (IsPrime(i))
			{
				printf("rank= %d Results: %d\n", rank, i);
			}
		}

	}
	else
		printf("Must specify %d processors. Terminating.\n", SIZE);
	MPI_Finalize();
}
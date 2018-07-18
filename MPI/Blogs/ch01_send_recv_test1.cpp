/*******************************************************************************
  > File Name: send_recv_test1.cpp
  > Author: Jiang Yong
  > Mail: chiangyung@aliyun.com
  > Created Time: Wed 11 Jul 2018 05:14:10 AM PDT
  > Description:
 ******************************************************************************/

#include "mpi.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    int size, rank, value;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    do {
        if (rank == 0) {
            fprintf(stderr, "\nPlease give new value: \n");
            scanf("%d", &value);
            fprintf(stderr, "Processor %d read << %d\n", rank, value);
            if (size > 1) {
                MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                fprintf(stderr, "Processor %d send %d >> %d\n",
                        rank, value, rank + 1);
            }
        } else {
            MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
            fprintf(stderr, "Processor %d recv %d << %d\n",
                    rank, value, rank - 1);
            if (rank < size - 1) {
                MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                fprintf(stderr, "Processor %d send %d >> %d\n",
                        rank, value, rank + 1);
            }

        }
        MPI_Barrier(MPI_COMM_WORLD);
    } while (value > 0);

    MPI_Finalize();

    return 0;
}

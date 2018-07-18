/*******************************************************************************
  > File Name: send_recv_test1.cpp
  > Author: Jiang Yong
  > Mail: chiangyung@aliyun.com
  > Created Time: Wed 11 Jul 2018 05:14:10 AM PDT
  > Description:
 ******************************************************************************/

#include "mpi.h"

#include <stdio.h>

void hello();

int main(int argc, char *argv[])
{
    int rank, option, namelen, size;
    char process_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (size < 2) {
        fprintf(stderr, "System requires at least 2 processors.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    MPI_Get_processor_name(process_name, &namelen);
    fprintf(stderr, "Process %d is alive on %s\n\n", rank, process_name);

    MPI_Barrier(MPI_COMM_WORLD);

    hello();

    MPI_Finalize();

    return 0;
}

void hello()
{
    int size, rank;
    int type = 1;
    int buff[2], node;

    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        printf("\nHello test from all to all.\n");
        fflush(stdout);
    }

    for (node = 0; node < size; node++) {
        if (node != rank) {
            // 当前进程为rank，其他进程为node
            buff[0] = rank;
            buff[1] = node;

            // 当前进程向其他进程发送数据，所以这里为node
            MPI_Send(buff, 2, MPI_INT, node, type, MPI_COMM_WORLD);
            // 当前进程接收其他进程发送的数据，所以这里还是node
            MPI_Recv(buff, 2, MPI_INT, node, type, MPI_COMM_WORLD, &status);

            if (buff[0] != node || buff[1] != rank) {
                fprintf(stderr, "Hello: %d != %d or %d != %d\n",
                        buff[0], node, buff[1], rank);
                printf("Mismatch on hello process ids, node = %d\n", node);
            }

            printf("Hello from %d to %d.\n", rank, node);
            fflush(stdout);
        }
    }
}

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
    int size, rank, i, buff[1];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        for (int i = 0; i < 5 * (size - 1); i++) {
            // 这里使用了MPI_ANY_SOURCE和MPI_ANY_TAG，是指接收任意进程发送的任意
            // 标签的信息
            MPI_Recv(buff, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG,
                    MPI_COMM_WORLD, &status);
            // 这里用到了status结构的的成员，用来获取接收到的信息来自哪个进程
            printf("Msg = %d from %d with tag %d\n",
                    buff[0], status.MPI_SOURCE, status.MPI_TAG);
        }
    } else {
        for (int i = 0; i < 5; i++) {
            buff[0] = rank + i;
            MPI_Send(buff, 1, MPI_INT, 0, i, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();

    return 0;
}

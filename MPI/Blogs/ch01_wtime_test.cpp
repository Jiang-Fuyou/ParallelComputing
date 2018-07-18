/*******************************************************************************
  > File Name: wtime_test.cpp
  > Author: Jiang Yong
  > Mail: chiangyung@aliyun.com
  > Created Time: Wed 11 Jul 2018 04:35:38 AM PDT
  > Description:
 ******************************************************************************/

#include "mpi.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int err = 0;
    double t1, t2;
    double tick;

    MPI_Init(&argc, &argv);

    t1 = MPI_Wtime();
    t2 = MPI_Wtime();

    if (t2 - t1 > 0.0 || t2 - t1 < 0.0) {
        err++;
        fprintf(stderr,
                "Two successive calls to MPI_Wtime gave strange results:");
        fprintf(stderr, "(%f)(%f)\n", t1, t2);
    }

    int i;
    for (i = 0; i < 10; i++) {
        t1 = MPI_Wtime();
        sleep(1);
        t2 = MPI_Wtime();

        if (t2 - t1 >= (1 - 0.1) && t2 - t1 <= 5) {
            break;
        }
        if (t2 - t1 > 5.0) {
            i = 9;
        }
    }

    if (i == 10) {
        fprintf(stderr, "Timer around sleep(1) did not give 1 seconds.\n");
        fprintf(stderr, "Gave %f\n", t2 - t1);
    }

    tick = MPI_Wtick();

    if (tick > 1.0 || tick < 0.0) {
        err++;
        fprintf(stderr, "MPI_Wtick gave a strange result: %f\n", tick);
    }


    MPI_Finalize();

    return 0;
}

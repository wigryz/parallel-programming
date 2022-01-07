#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mpi.h"

struct rekord {
    double skalar;
    char znak;
    float wektor[3];
}

int main(int argc, char **argv)
{

    int rank, size, source, tag, i;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int number = 0;
    int number_recv = 0;
    //  SZTAFETA PIERSCIEN
    while (size > 0)
    {
        int prev = rank - 1;
        int next = rank + 1;
        if (rank == 0)
        {
            prev = size - 1;
        }
        else if (rank == size - 1)
        {
            next = 0;
        }
        if (!(rank == 0 && number == 0))
        {
            MPI_Recv(&number_recv, 1, MPI_INT, prev, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            printf("Proces %d otrzymal liczbe %d od procesu %d\n", rank, number_recv, prev);
        }
        number = number_recv + 1;
        MPI_Send(&number, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
        printf("Proces %d wyslal liczbe %d do procesu %d\n", rank, number, next);
    }

    // //  SZTAFETA OTWARTY PIERSCIEN
    //     if (size > 0) {
    //         if (rank == 0) {
    //             int next = rank + 1;
    //             MPI_Send(&number, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
    //             printf("Proces %d wyslal liczbe %d do procesu %d\n", rank, number, next);
    //         } else if (rank < size - 1) {
    //             int prev = rank - 1;
    //             int next = rank + 1;
    //             MPI_Recv(&number_recv, 1, MPI_INT, prev, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    //             printf("Proces %d otrzymal liczbe %d od procesu %d\n", rank, number_recv, prev);
    //             number = number_recv + 1;
    //             MPI_Send(&number, 1, MPI_INT, next, tag, MPI_COMM_WORLD);
    //             printf("Proces %d wyslal liczbe %d do procesu %d\n", rank, number, next);
    //         } else if (rank == size - 1) {
    //             int prev = rank - 1;
    //             MPI_Recv(&number_recv, 1, MPI_INT, prev, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    //             printf("Proces %d otrzymal liczbe %d od procesu %d\n", rank, number_recv, prev);
    //         }
    //     }

    MPI_Finalize();
    return 0;
}

#include <stdlib.h>
#include<stdio.h>
#include<math.h>

#include "mpi.h"

int main(int argc, char **argv) {

    int rank, ranksent, size, source, dest, tag, i;
    char sender[256];
    char receive_sender[256];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size > 1) {

        if (rank != 0) {
            dest = 0;
            tag = 0;
            gethostname(sender, 256);
            MPI_Send(&sender, 256, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        } else {
            for (i = 1; i < size; i++) {
                MPI_Recv(&receive_sender, 256, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                printf("Dane od procesu o randze: %d (status.MPI_SOURCE -> %d) (i=%d) (sender=%s)\n",
                       ranksent, status.MPI_SOURCE, i, receive_sender);
            }
        }
    } else {
        printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
    }

    MPI_Finalize();

    return (0);

}


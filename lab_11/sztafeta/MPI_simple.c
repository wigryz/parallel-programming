#include <stdlib.h>
#include<stdio.h>
#include<math.h>

#include "mpi.h"

int main(int argc, char **argv) {

    int rank, ranksent, size, source, dest, tag, i;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size > 0) {
        if (rank == 0) {
            int next = rank + 1;
            MPI_Send(&next, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
            printf("Proces %d wyslal liczbe %d do procesu %d\n", rank);
        } else if (rank > 0 && rank < size - 1) {
            printf("jestem srodkowym procesem o randze = %d\n", rank);
            int prev = rank - 1;
            int next = rank + 1;
            MPI_Recv(&prev, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            MPI_Send(&next, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
        } else if (rank == size - 1) {
            printf("jestem ostatnim procesem o randze %d\n", rank);
            int prev = rank - 1;
            MPI_Recv(&prev, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        }
    }

    MPI_Finalize();
    return 0;
}


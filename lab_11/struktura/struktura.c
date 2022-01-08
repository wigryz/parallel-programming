#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mpi.h"

struct record
{
    double scalar;
    int number;
    char name[8];
};

int main(int argc, char **argv)
{

    int rank, size, source, tag, i;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int number = 4;
    int number_recv = 0;

    struct record rekord;
    rekord.scalar = 5.0;
    rekord.number = 10;
    strncpy(rekord.name, "tomasz", 8);

    int aux = 0;
    MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &aux);
    int packet_size = aux;
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &aux);
    packet_size += aux;
    MPI_Pack_size(8, MPI_CHAR, MPI_COMM_WORLD, &aux);
    packet_size += aux;

    if (size > 0)
    {
        if (rank == 0)
        {
            int next = rank + 1;

            //PAKOWANIE
            int pos = 0;
            void *buffor = (void *)malloc(packet_size);
            MPI_Pack(&rekord.scalar, 1, MPI_DOUBLE, buffor, packet_size, &pos, MPI_COMM_WORLD);
            MPI_Pack(&rekord.number, 1, MPI_INT, buffor, packet_size, &pos, MPI_COMM_WORLD);
            MPI_Pack(&rekord.name, 8, MPI_CHAR, buffor, packet_size, &pos, MPI_COMM_WORLD);

            printf("Proces %d - wysyla strukture: %lf, %d, %s\n", rank, rekord.scalar, rekord.number, rekord.name);
            MPI_Send(buffor, pos, MPI_PACKED, next, tag, MPI_COMM_WORLD);
        }
        else if (rank < size - 1)
        {
            int prev = rank - 1;
            int next = rank + 1;

            void *buffor = (void *)malloc(packet_size);
            MPI_Recv(buffor, packet_size, MPI_INT, prev, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

            //ODPAKOWANIE
            int pos = 0;
            struct record recv;
            MPI_Unpack(buffor, packet_size, &pos, &recv.scalar, 1, MPI_DOUBLE, MPI_COMM_WORLD);
            MPI_Unpack(buffor, packet_size, &pos, &recv.number, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(buffor, packet_size, &pos, &recv.name, 8, MPI_CHAR, MPI_COMM_WORLD);

            printf("Proces %d - odebral strukture: %lf, %d, %s\n", rank, recv.scalar, recv.number, recv.name);
            //EDYCJA
            recv.scalar += 0.1;
            recv.number += 1;
            //PAKOWANIE
            pos = 0;
            MPI_Pack(&recv.scalar, 1, MPI_DOUBLE, buffor, packet_size, &pos, MPI_COMM_WORLD);
            MPI_Pack(&recv.number, 1, MPI_INT, buffor, packet_size, &pos, MPI_COMM_WORLD);
            MPI_Pack(&recv.name, 8, MPI_CHAR, buffor, packet_size, &pos, MPI_COMM_WORLD);

            printf("Proces %d - wysyla strukture: %lf, %d, %s\n", rank, recv.scalar, recv.number, recv.name);
            MPI_Send(buffor, pos, MPI_PACKED, next, tag, MPI_COMM_WORLD);
        }
        else if (rank == size - 1)
        {
            int prev = rank - 1;

            void *buffor = (void *)malloc(packet_size);
            MPI_Recv(buffor, packet_size, MPI_INT, prev, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            //ODPAKOWANIE
            int pos = 0;
            struct record recv;
            MPI_Unpack(buffor, packet_size, &pos, &recv.scalar, 1, MPI_DOUBLE, MPI_COMM_WORLD);
            MPI_Unpack(buffor, packet_size, &pos, &recv.number, 1, MPI_INT, MPI_COMM_WORLD);
            MPI_Unpack(buffor, packet_size, &pos, &recv.name, 8, MPI_CHAR, MPI_COMM_WORLD);

            printf("Proces %d - odebral strukture: %lf, %d, %s\n", rank, recv.scalar, recv.number, recv.name);
        }
    }

    MPI_Finalize();
    return 0;
}

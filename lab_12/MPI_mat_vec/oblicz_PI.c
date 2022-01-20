#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mpi.h"

#define SCALAR double

#ifndef M_PI // standardy C99 i C11 nie wymagają definiowania stałej M_PI
#define M_PI (3.14159265358979323846)
#endif

int main(int argc, char **argv) { // program obliczania przybliżenia PI za pomocą wzoru Leibniza
    // PI = 4 * ( 1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + itd. )

    int rank, size, source, dest, tag;
    int root = 0;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int max_liczba_wyrazow = 0;
    if(rank == 0) {
        printf("Podaj maksymalną liczbę wyrazów do obliczenia przybliżenia PI\n");
        scanf("%d", &max_liczba_wyrazow);
    }

    MPI_Bcast( &max_liczba_wyrazow, 1, MPI_INT, root, MPI_COMM_WORLD );
    int wyrazow_na_proces = max_liczba_wyrazow / size;
    int a = wyrazow_na_proces * (rank);
    int b = wyrazow_na_proces * (rank + 1);

    if(rank == size - 1)
        b = max_liczba_wyrazow;
    printf("jestem procesem %d i moj przedzial to: %d -> %d\n", rank, a, b);

    SCALAR suma_plus = 0.0;
    SCALAR suma_minus = 0.0;
    int i = 0;
    for(i=a ; i<b ; i++) {
        int j = 1 + 4 * i;

        suma_plus += 1.0 / j;
        suma_minus += 1.0 / (j + 2.0);
    }

    SCALAR suma = suma_plus - suma_minus;
    SCALAR suma_global = 0;
    MPI_Reduce( &suma, &suma_global, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);

    // wzór: PI/4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 itd. itp.

    if(rank == 0) {
        int i = 0;
        //#pragma omp parallel for default(none) shared(max_liczba_wyrazow) reduction(+:suma_plus) reduction(+:suma_minus)
        suma_plus = 0;
        suma_minus = 0;
        for (i = 0; i < max_liczba_wyrazow; i++) {

            int j = 1 + 4 * i;

            suma_plus += 1.0 / j;
            suma_minus += 1.0 / (j + 2.0);

            //printf("PI obliczone: %20.15lf, aktualna poprawka: %20.15lf\n",
            //  	 4*(suma_plus-suma_minus), 4.0/j-4.0/(j+2.0));

        }
        printf("PI obliczone: \t\t\t%20.15lf\n", 4 * (suma_plus - suma_minus));
        printf("PI rownolegle: \t%20.15lf\n", 4 * (suma_global));
        printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
    }
    //  printf("Czas obliczeń: %lf\n", t);

    MPI_Finalize();

}



// całka
/* h   = 1.0 / (SCALAR) n; */
/* sum = 0.0; */
/* for (i = 1; i <= n; i++) { */
/*   x = h * ((SCALAR)i - 0.5); */
/*   sum += 4.0 / (1.0 + x*x); */
/* } */
/* mypi = h * sum; */

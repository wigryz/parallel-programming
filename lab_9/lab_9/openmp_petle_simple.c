#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 18

int main() {
    int LICZBA_WATKOW = 4;
    double a[WYMIAR];
    int n, i;

    for (i = 0; i < WYMIAR; i++) a[i] = 1.02 * i;

    n = WYMIAR;

    // pętla sekwencyjna
    double suma = 0.0;
    for (i = 0; i < WYMIAR; i++) {
        suma += a[i];
    }

    printf("Suma wyrazów tablicy: %lf\n", suma);

    // pętla do modyfikacji - docelowo równoległa w OpenMP
    double suma_parallel = 0.0;
//#pragma omp parallel for reduction(+:suma_parallel) num_threads(LICZBA_WATKOW) schedule(static, 3) ordered
//#pragma omp parallel for reduction(+:suma_parallel) num_threads(LICZBA_WATKOW) schedule(static) ordered
//#pragma omp parallel for reduction(+:suma_parallel) num_threads(LICZBA_WATKOW) schedule(dynamic, 2) ordered
#pragma omp parallel for reduction(+:suma_parallel) num_threads(LICZBA_WATKOW) schedule(dynamic) ordered
    for (i = 0; i < WYMIAR; i++) {
        int id_w = omp_get_thread_num();
        // ...
        suma_parallel += a[i];
        // ...
#pragma omp ordered
        printf("a[%2d]->W_%1d  \n", i, id_w);
    }
    printf("\nSuma wyrazów tablicy równolegle (z klauzulą - ....: %lf\n", suma_parallel);
}

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 10
#define NUM_THREADS 3


int main() {
    double a[WYMIAR][WYMIAR];
    int n, i, j;

    for (i = 0; i < WYMIAR; i++) for (j = 0; j < WYMIAR; j++) a[i][j] = 1.02 * i + 1.01 * j;

    n = WYMIAR;

    // podwójna pętla - sekwencyjnie
    double suma = 0.0;
    for (i = 0; i < WYMIAR; i++) {
        for (j = 0; j < WYMIAR; j++) {
            suma += a[i][j];
        }
    }

    printf("Suma wyrazów tablicy: %lf\n", suma);

    omp_set_nested(1);

    // podwójna pętla - docelowo równolegle
    double suma_parallel = 0.0;
//    //1
////#pragma omp parallel for reduction(+:suma_parallel) num_threads(NUM_THREADS) private(i,j) schedule(static, 2) ordered
//    for (i = 0; i < WYMIAR; i++) {
//        int id_w = omp_get_thread_num();
//        // #pragma omp ordered
//        // ...
//        //2
//#pragma omp parallel for reduction(+:suma_parallel) num_threads(NUM_THREADS) private(j) schedule(dynamic) ordered
//        for (j = 0; j < WYMIAR; j++) {
//            suma_parallel += a[i][j];
//#pragma omp ordered
//            // dla dekompozycji 1D
//            printf("(%1d,%1d)-W_%1d ", i, j, omp_get_thread_num());
//            // dla dekompozycji 2D
//            //printf("(%1d,%1d)-W_%1d,%1d ",i,j,id_w,omp_get_thread_num());
//        }
//        // #pragma omp ordered
//        printf("\n");
//    }


    //3
//#pragma omp parallel default(none) for reduction(+:suma_parallel) num_threads(NUM_THREADS) private(i,j) schedule(static, 2) ordered
#pragma omp parallel default(none) shared(suma_parallel, a) private(i, j) num_threads(NUM_THREADS)
    {
#pragma omp for ordered schedule(static)
        for (j = 0; j < WYMIAR; j++) {
            double suma_tmp = 0.0;
            for (i = 0; i < WYMIAR; i++) {
                suma_tmp += a[i][j];
#pragma omp ordered
                printf("(%1d,%1d)-W_%1d ", i, j, omp_get_thread_num());
            }
#pragma omp atomic
            suma_parallel += suma_tmp;
            printf("\n");
        }
    }

    printf("Suma wyrazów tablicy równolegle: %lf\n", suma_parallel);

}

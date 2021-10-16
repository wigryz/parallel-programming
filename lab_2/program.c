#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>
#include "../pomiar_czasu/pomiar_czasu.h"

int zmienna_globalna = 0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku(void *argument) {
    int zmienna_lokalna = 0;
    for(int i=0 ; i < 10000000 ; i++) {
        zmienna_lokalna++;
        zmienna_globalna++;
    }
    printf("Wartosc zmiennej globalnej w watku: %d\n", zmienna_globalna);
    printf("Wartosc zmiennej lokalnej w watku: %d\n", zmienna_lokalna);
    return 0;
}

main() {

    void *stos1;
    void *stos2;
    pid_t pid1;
    pid_t pid2;

    stos1 = malloc(ROZMIAR_STOSU);
    stos2 = malloc(ROZMIAR_STOSU);
    if (stos1 == 0 || stos2 == 0) {
        printf("Proces nadrzędny - blad alokacji stosu\n");
        exit(1);
    }

    inicjuj_czas();
    pid1 = clone(&funkcja_watku, (void *) stos1 + ROZMIAR_STOSU,
                 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);

    pid2 = clone(&funkcja_watku, (void *) stos2 + ROZMIAR_STOSU,
                 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0);

    waitpid(pid1, NULL, __WCLONE);
    waitpid(pid2, NULL, __WCLONE);

    drukuj_czas();

    printf("Wartosc zmiennej globalnej w main: %d\n", zmienna_globalna);

    free(stos1);
    free(stos2);
}

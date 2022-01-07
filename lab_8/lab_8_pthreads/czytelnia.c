#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(czytelnia_t *czytelnia_p) {
    pthread_mutex_lock(&czytelnia_p->muteks);
    if(czytelnia_p->liczba_pis > 0 || czytelnia_p->liczba_czekajacych_pisarzy > 0) {
        czytelnia_p->liczba_czekajacych_czytelnikow++;
        pthread_cond_wait(&czytelnia_p->czytelnicy, &czytelnia_p->muteks);
        czytelnia_p->liczba_czekajacych_czytelnikow--;
    }
    czytelnia_p->liczba_czyt++;
    pthread_mutex_unlock(&czytelnia_p->muteks);
    pthread_cond_signal(&czytelnia_p->czytelnicy);
}


int my_read_lock_unlock(czytelnia_t *czytelnia_p) {
    pthread_mutex_lock(&czytelnia_p->muteks);
    czytelnia_p->liczba_czyt--;
    if(czytelnia_p->liczba_czyt == 0)
        pthread_cond_signal(&czytelnia_p->pisarze);
    pthread_mutex_unlock(&czytelnia_p->muteks);
}


int my_write_lock_lock(czytelnia_t *czytelnia_p) {
    pthread_mutex_lock(&czytelnia_p->muteks);
    if(czytelnia_p->liczba_pis + czytelnia_p->liczba_czyt > 0) {
        czytelnia_p->liczba_czekajacych_pisarzy++;
        pthread_cond_wait(&czytelnia_p->pisarze, &czytelnia_p->muteks);
        czytelnia_p->liczba_czekajacych_pisarzy--;
    }
    czytelnia_p->liczba_pis++;
    pthread_mutex_unlock(&czytelnia_p->muteks);
}


int my_write_lock_unlock(czytelnia_t *czytelnia_p) {
    pthread_mutex_lock(&czytelnia_p->muteks);
    czytelnia_p->liczba_pis--;
    if(czytelnia_p->liczba_czekajacych_czytelnikow > 0)
        pthread_cond_signal(&czytelnia_p->czytelnicy);
    else
        pthread_cond_signal(&czytelnia_p->pisarze);
    pthread_mutex_unlock(&czytelnia_p->muteks);
}

void inicjuj(czytelnia_t *czytelnia_p) {
    czytelnia_p->liczba_czyt = 0;
    czytelnia_p->liczba_pis = 0;
    czytelnia_p->liczba_czekajacych_czytelnikow = 0;
    czytelnia_p->liczba_czekajacych_pisarzy = 0;
    pthread_cond_init(&czytelnia_p->pisarze, NULL);
    pthread_cond_init(&czytelnia_p->czytelnicy, NULL);
    pthread_mutex_init(&czytelnia_p->muteks, NULL);
}

void czytam(czytelnia_t *czytelnia_p) {
    usleep(rand() % 300000);
    if(czytelnia_p->liczba_pis > 1 || (czytelnia_p->liczba_pis == 1 && czytelnia_p->liczba_czyt > 0)) {
        printf("Blad! piszacych: %d, czytajacych: %d.", czytelnia_p->liczba_pis, czytelnia_p->liczba_czyt);
        exit(1);
    }
}

void pisze(czytelnia_t *czytelnia_p) {
    usleep(rand() % 300000);
    if(czytelnia_p->liczba_pis > 1 || (czytelnia_p->liczba_pis == 1 && czytelnia_p->liczba_czyt > 0)) {
        printf("Blad! piszacych: %d, czytajacych: %d.", czytelnia_p->liczba_pis, czytelnia_p->liczba_czyt);
        exit(1);
    }
}



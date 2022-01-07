//
// Created by wigryz on 03.12.2021.
//
#include <pthread.h>
#include <stdio.h>

int liczba_watkow_aktualna;
int liczba_watkow_docelowa;
pthread_mutex_t muteks = PTHREAD_COND_INITIALIZER;
pthread_cond_t warunek;


void bariera_init(int liczba_watkow) {
    liczba_watkow_aktualna = 0;
    liczba_watkow_docelowa = liczba_watkow;
    pthread_mutex_init(&muteks, NULL);
    pthread_cond_init(&warunek, NULL);
}

void bariera() {
    pthread_mutex_lock(&muteks);
    liczba_watkow_aktualna++;
    if(liczba_watkow_aktualna != liczba_watkow_docelowa) {
        pthread_cond_wait(&warunek, &muteks);
    }
    else {
        liczba_watkow_aktualna = 0;
        pthread_cond_broadcast(&warunek);
    }
    pthread_mutex_unlock(&muteks);
}


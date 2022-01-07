#ifndef _czytelnia_
#define _czytelnia_

#include <pthread.h>

/*** Definicje typow zmiennych ***/
typedef struct {
    int liczba_czyt;
    int liczba_pis;

    int liczba_czekajacych_pisarzy;
    int liczba_czekajacych_czytelnikow;

    pthread_cond_t pisarze;
    pthread_cond_t czytelnicy;
    pthread_mutex_t muteks;
  // <- zasoby czytelni
} czytelnia_t;

/*** Deklaracje procedur interfejsu ***/
void inicjuj(czytelnia_t* czytelnia_p);
void czytam(czytelnia_t* czytelnia_p);
void pisze(czytelnia_t* czytelnia_p);

int my_read_lock_lock(czytelnia_t* czytelnia_p);
int my_read_lock_unlock(czytelnia_t* czytelnia_p);
int my_write_lock_lock(czytelnia_t* czytelnia_p);
int my_write_lock_unlock(czytelnia_t* czytelnia_p);

#endif

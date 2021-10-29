#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

const int LICZBA_WATKOW = 10;

int zmienna_wspolna=0;

void * zadanie_watku (void * arg_wsk) {
    int id = *((int *) arg_wsk);

    printf("\t\tSystemowy id: %lu, programowy id: %d \n", pthread_self(), id);
    return (NULL);
}

int main()
{
	pthread_t tid[LICZBA_WATKOW];
    int ids[LICZBA_WATKOW];
    int tab[LICZBA_WATKOW];
    int wyniki[LICZBA_WATKOW];
    for(int i=0 ; i < LICZBA_WATKOW ; i++) {
        ids[i] = i;
    }//Wątek przyłączalny

    for(int i=0 ; i < LICZBA_WATKOW ; i++) {
        printf("\twatek glowny: tworzenie watku potomnego nr:%d\n", i);
        pthread_create(&(tid[i]), NULL, zadanie_watku, &(ids[i]));
//        pthread_create(&(tid[i]), NULL, zadanie_watku, &i);
        // tutaj jesli przesylam wartosc &i to powinno sie pojawic np 2 razy nr. 2
    }

    for(int i=0 ; i < LICZBA_WATKOW ; i++) {
        tab[i] = pthread_join(tid[i], &(wyniki[i]));
    }

	sleep(2); // czas na uruchomienie watkow
	pthread_exit(NULL); // co stanie sie gdy uzyjemy exit(0)?
}



#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include<pthread.h>
#include <unistd.h>

#define ILE_MUSZE_WYPIC 1000

int liczba_wolnych_kufli;
//inicjalizacja muteksa w przestrzeni globalnej
pthread_mutex_t straznik_kufli = PTHREAD_COND_INITIALIZER;
int l_kf;

// 1. sprawdzenie kiedy dzialanie jest nieprawidlowe
// wtedy, gdy rywalizujac o zasoby klienci wprowadzaja niespojnosci w programie

void *watek_klient(void *arg);

int main(void) {

    pthread_t *tab_klient;
    int *tab_klient_id;

    int l_kl, l_kr, i;

    printf("\nLiczba klientow: ");
    scanf("%d", &l_kl);

    printf("\nLiczba kufli: ");
    scanf("%d", &l_kf);

    pthread_mutex_init(&straznik_kufli, NULL);
    liczba_wolnych_kufli = l_kf;

    //printf("\nLiczba kranow: "); scanf("%d", &l_kr);
    l_kr = 1000000000; // wystarczająco dużo, żeby nie było rywalizacji

    tab_klient = (pthread_t *) malloc(l_kl * sizeof(pthread_t));
    tab_klient_id = (int *) malloc(l_kl * sizeof(int));
    for (i = 0; i < l_kl; i++) tab_klient_id[i] = i;

    printf("\nOtwieramy pub (simple)!\n");
    printf("\nLiczba kufli %d\n", l_kf);
    printf("\nLiczba wolnych kufli %d\n", liczba_wolnych_kufli);

    for (i = 0; i < l_kl; i++) {
        pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]);
    }
    for (i = 0; i < l_kl; i++) {
        pthread_join(tab_klient[i], NULL);
    }
    printf("\nZamykamy pub!\n");

    printf("\nLiczba kufli %d\n", l_kf);
    printf("\nLiczba wolnych kufli %d\n", liczba_wolnych_kufli);
    if (l_kf != liczba_wolnych_kufli) {
        printf("Blad! Rozna liczba kufli na starcie i na koncu pracy programu.\n");
        exit(-1);
    }
}


void *watek_klient(void *arg_wsk) {

    int moj_id = *((int *) arg_wsk);

    int i, j, kufel, result;
    int ile_musze_wypic = ILE_MUSZE_WYPIC;

//    printf("\nKlient %d, wchodzę do pubu\n", moj_id);

    for (i = 0; i < ile_musze_wypic; i++) {

//        printf("\nKlient %d, wybieram kufel\n", moj_id);

        int success = 0;
        do {
            while (pthread_mutex_trylock(&straznik_kufli) != 0) {}
            if (liczba_wolnych_kufli > 0) {
                --liczba_wolnych_kufli;
                success = 1;
            }
            pthread_mutex_unlock(&straznik_kufli);
        } while (success == 0);
        j = 0;
//        printf("\nKlient %d, nalewam z kranu %d\n", moj_id, j);
//        usleep(30);

//        printf("\nKlient %d, pije\n", moj_id);
//        nanosleep((struct timespec[]) {{0, 50000000L}}, NULL);

//        printf("\nKlient %d, odkladam kufel\n", moj_id);
        while (pthread_mutex_trylock(&straznik_kufli) != 0) {}
        ++liczba_wolnych_kufli;
        pthread_mutex_unlock(&straznik_kufli);
    }

//    printf("\nKlient %d, wychodzę z pubu\n", moj_id);

    return (NULL);
} 



/*
    Scrivere un programma in C in cui tre thread aggiornano
    la stessa variabile globale condivisa sample, inizialmente
    posta a 50. Ogni thread ciclicamente genera un numero casuale
    compreso tra 10 e 90 e prova a sovrascrivere il valore corrente
    di sample. Il thread mostra in output un messaggio che segue il
    modello “Sono il thread X: sample valeva Y, adesso vale Z”, con
    opportuni valori al posto di X, Y e Z. Se il valore casuale
    generato è uguale al valore attuale di sample il thread termina
    il suo ciclo, comunicando in output la propria terminazione.
    Quando tutti i thread sono terminati, il programma principale
    termina e mostra in output il valore finale di sample.
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>

int sample = 50;
time_t t;
pthread_mutex_t mutex;
int random_num;

void* func(void* arg)
{
    srand((unsigned) time(&t));

    while ( (random_num = (rand()%80) + 10) != sample )
    {   
        pthread_mutex_lock(&mutex);

        printf("Sono il thread %p: sample valeva %d, adesso vale %d\n", arg, sample, random_num);
        sample = random_num;

        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_lock(&mutex);
    sample = random_num;
    pthread_mutex_unlock(&mutex);

    printf("Sono il thred %p: ho terminato con sample uguale a: %d!\n", arg, sample);
    pthread_exit((void *) arg);
}




int main(int argc, char const *argv[])
{
    pthread_t tr1, tr2, tr3;
    void *thrd1_res, *thrd2_res, *thrd3_res;

    pthread_create( &tr1, NULL, func, (void *) 1);
    pthread_create( &tr2, NULL, func, (void *) 2);
    pthread_create( &tr3, NULL, func, (void *) 3);

    pthread_join(tr1, &thrd1_res);
    pthread_join(tr2, &thrd2_res);
    pthread_join(tr3, &thrd3_res);

}


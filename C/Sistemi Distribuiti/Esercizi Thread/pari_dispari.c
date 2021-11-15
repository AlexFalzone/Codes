/* Realizzare due thread A e B, che stampano rispettivamente i numeri pari e i numeri dispari (da 1 a 100). */

#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>

int num = 0;
pthread_t thr1, thr2;
pthread_mutex_t mutex;

void* pari()
{
    while (num < 100)
    {
        pthread_mutex_lock(&mutex);

        if ((num % 2) != 0)
        {
            num++;
            printf("Thread A: %d\n", num);           
        }
        
        pthread_mutex_unlock(&mutex);
    }
    exit(0);
}

void* dispari()
{
    while (num < 99)
    {
        pthread_mutex_lock(&mutex);

        if ((num % 2) == 0)
        {
            num++;
            printf("\t\t\t\tThread B: %d\n", num);            
        }
        
        pthread_mutex_unlock(&mutex);
    }
    exit(0);
}

int main(int argc, char const *argv[])
{
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&thr1, NULL, (void *)pari, NULL);
    pthread_create(&thr2, NULL, (void *)dispari, NULL);

    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);

    return 0;
}

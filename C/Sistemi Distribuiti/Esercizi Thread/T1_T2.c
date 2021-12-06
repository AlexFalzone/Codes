#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>
#include <unistd.h>

typedef struct
{
    int x; 
    pthread_mutex_t mutex;
    pthread_cond_t disponibilita;

} account_t;

account_t a;

void init_acc(account_t * a)
{
  a->x = 0;
  pthread_mutex_init(&(a->mutex), NULL);
  pthread_cond_init(&(a->disponibilita), NULL);
}


void * func_T1(account_t *a)
{
    int retcode, m, absol;

    while (1)
    {
        if ((retcode = usleep(100)) == -1)
        {
            perror("Errore usleep\n");
            exit(EXIT_FAILURE);
        }    

        m = rand()%10;
        printf("TH1 || m = %d\n", m);

        pthread_mutex_lock(&(a->mutex));

        if (a->x == -1)
        {
            pthread_mutex_unlock(&(a->mutex));
            pthread_exit(NULL);
        }
        else
        {   
            pthread_mutex_lock(&(a->mutex));
            if (m == a->x)
            {
                printf("RISPOSTA CORRETTA\n");
                a->x = -1;
                pthread_mutex_unlock(&(a->mutex));
                pthread_exit(NULL);
            }
            else 
            {   
                if ((absol = abs(m - a->x)) > 5)
                {
                    printf("risposta MOLTO sbagliata, x = %d\n", a->x);

                    pthread_mutex_unlock(&(a->mutex));
                    printf("TH1 || thread 1 sis sta per addormentare\n");
                    pthread_cond_wait( &(a->disponibilita), &(a->mutex) );
                
                    pthread_mutex_unlock(&(a->mutex));
                }
                else
                {
                    printf("risposta sbagliata, x = %d\n", a->x);
                }
            }

        }
    }
 
}

void * func_T2(account_t *a)
{
    int retcode;
    printf("\t\t\tthread 2\n");

    while (1)
    {
        if ((retcode = usleep(300)) == -1)
        {
            perror("Errore usleep\n");
            exit(EXIT_FAILURE);
        }

        pthread_cond_signal(& (a->disponibilita));
        
        printf("\t\t\tTH2 || thread 1 svegliato\n");

        pthread_mutex_lock(&(a->mutex));

        if (a->x == -1)
        {
            pthread_exit(NULL);
        }

        pthread_mutex_unlock(&(a->mutex));
    }
}

void * real_t1(void * arg)
{
    func_T1(&a);
}

void * real_t2(void * arg)
{
    func_T2(&a);
}

int main(int argc, char const *argv[])
{
    pthread_t t1, t2;

    init_acc(&a);

    pthread_create(&t1, NULL, real_t1, NULL);
    pthread_create(&t2, NULL, real_t2, NULL);

    pthread_exit(NULL);
}

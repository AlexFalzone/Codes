#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>

#define DIM_MSG 1024

typedef struct 
{
    long tipo;
    char testo[DIM_MSG];
}msg;



void IN(int num_query, int coda1)
{    
    msg messaggio;

    do
    {
        fgets(messaggio.testo, DIM_MSG, num_query);
        messaggio.tipo = 1;

        if ((msgsnd(coda1, &messaggio, strlen(messaggio.testo) + 1, 0) ) == -1)
        {
            perror("msgsend");
            exit(EXIT_FAILURE);
        }
    } while (messaggio.testo != 0);
}

void DB(int coda_in, int coda_out)
{

}

void OUT(int coda_out)
{
    msg messaggio;
    int i = 1, somma = 0;

    while (1)
    {
        if (msgrcv(coda_out, &messaggio, DIM_MSG, 0, 0) == -1)
        {
            perror("Errore su ricezione messaggi\n");
            exit(EXIT_FAILURE);
        }
        
        if (messaggio.testo == -1)
        {
            break;
        }

        printf("OUT: ricevuti n.%d valore per ... con totale %8lu\n", i, somma);
        i++;
    } 
}


int main(int argc, char const *argv[])
{   
    int coda_input, coda_output;
    int chiave_input, chiave_output;

    if (argc < 4)
    {
        printf("Usage: <lookup-database> <db-file> <query-file-1> <query-file-2>");
        exit(EXIT_FAILURE);
    }
    
    if ((coda_input = msgget(chiave_input, IPC_CREAT | 0660)) == -1)
    {
        perror("Errore su creazione coda input\n");
        exit(EXIT_FAILURE);
    }
    if ((coda_output = msgget(chiave_output, IPC_CREAT | 0660)) == -1)
    {
        perror("Errore su creazione coda input\n");
        exit(EXIT_FAILURE);
    }
    

    if (fork() != 0)
    {
        if (fork() != 0)
        {
            if (fork() != 0)
            {
                if (fork() != 0)
                {
                    wait(NULL);
                    wait(NULL);
                    wait(NULL);
                    wait(NULL);
                }
                else
                {
                    IN(argv[2], coda_input);
                    IN(argv[3], coda_input);
                }
            }
            else
            {
                DB(coda_input,coda_output);
            }
        }   
        else
        {
            OUT(coda_output);
        }
    }
    
    msgctl(coda_input, IPC_RMID, NULL);
    msgctl(coda_output, IPC_RMID, NULL);
}

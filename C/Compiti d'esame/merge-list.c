#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define DIM_MSG 1024
#define DIM_FILE 200

typedef struct
{
    long tipo;
    char testo[DIM_MSG];
}msg;


void R_func(const char* num_file, int coda)
{
    msg riga_letta;

    fgets(riga_letta.testo, DIM_MSG, num_file);



    // for (int i = 0; i < strlen(riga_letta.testo); i++)
    // {
    //     if (riga_letta.testo[i] == " " || riga_letta.testo[i] == "\n")
    //     {
    //         riga_letta.testo[i] == "\b";
    //     }
    // }
    
    riga_letta.tipo = 1;

    if (msgsnd(coda, &riga_letta, strlen(riga_letta.testo) + 1, 0) == -1)
    {
        perror("Errore msgsend\n");
        exit(EXIT_FAILURE);
    }
}

void P_func(int coda, int pipefd)
{
    char* array_duplicati[DIM_FILE];
    msg messaggio;

    if (msgrcv(coda, &messaggio, DIM_MSG, 0, 0) == -1)
    {
        perror("errore msgrcv\n");
        exit(EXIT_FAILURE);
    }

    int i;
    for (i = 0; i < DIM_FILE; i++)
    {
        if (array_duplicati[i] == messaggio.testo)
        {
            break;
        }
    }
    array_duplicati[++i] = messaggio.testo;
    
    if (write(pipefd,messaggio.testo, strlen(messaggio.testo) + 1) == -1)
    {
        perror("errore pipe sulla write\n");
    }
}

void W_func(int pipefd)
{
    char buffer[BUFSIZ];

    if (read(pipefd, buffer, BUFSIZ) == -1)
    {
        perror("errore pipe sulla lettura\n");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", buffer);
}




int main(int argc, char const *argv[])
{
    int pipefd[2];
    int ds_coda;
    int lettura_pipe = pipefd[0];
    int scrittura_pipe = pipefd[1];
    int i = 0;

    if (argc < 3)
    {
        printf("Usage: merge-lists.c <file-1> <file-2>\n");
        exit(EXIT_FAILURE);
    }

    if ((ds_coda = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL)) == -1)
    {
        perror("Errore creazione coda di messaggi\n");
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1)
    {
        perror("errore creazione pipe\n");
        exit(EXIT_FAILURE);
    }
    
    do
    {
        if (fork() == 0)
        {
            R_func(argv[1], ds_coda);
        }
        if (fork() == 0)
        {
            R_func(argv[2], ds_coda);
        }
        
        if (fork() == 0)
        {
            P_func(ds_coda, scrittura_pipe);
        }
        if (fork() == 0)
        {
            W_func(lettura_pipe);
        }
        
        wait(NULL);
        wait(NULL);
        wait(NULL);
        wait(NULL);
        i++;
    } while (i < 200);

    close(pipefd[0]);
    close(pipefd[1]);
    msgctl(ds_coda, IPC_RMID, NULL); 
}

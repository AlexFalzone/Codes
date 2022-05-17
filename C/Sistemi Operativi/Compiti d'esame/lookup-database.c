#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define DIM_MSG 1024

typedef struct 
{
    long type;
    char testo[DIM_MSG];
    int end;
}msg;


void IN_func(int coda, char* pathname)
{
    int open_file;
    FILE *in;
    msg messagges;

    if ((open_file = open(pathname, O_RDONLY)) == -1)
    {
        printf("apertura file '%s' non riuscita\n", pathname);
        exit(EXIT_FAILURE);
    }

    if ((in = fdopen(open_file, "r")) == NULL)
    {
        perror("errore conversione file to FILE in IN_func\n");
        exit(EXIT_FAILURE);
    }
    
    fgets(messagges.testo, DIM_MSG, in);

    messagges.type = 1;

    if (msgsnd(coda, &messagges, strlen(messagges.testo) + 1, 0) == -1)
    {
        perror("Errore msgsnd\n");
        exit(EXIT_FAILURE);
    }
}

void DB_func(int coda_in, int coda_out, char* pathname)
{   
    msg messagges;




    if (msgrcv(coda_in, &messagges, DIM_MSG, 0, 0) == -1)
    {
        perror("Errore msgrcv\n");
        exit(EXIT_FAILURE);
    }
    

}



int main(int argc, char *argv[])
{
    int coda_out, coda_in;
    key_t chiave_out = 50;

    if (argc < 4)
    {
        printf("Usage: lookup-database <db-file> <query-file-1> <query-file-2>");
        exit(EXIT_FAILURE);
    }
        
    if ((coda_in = msgget(IPC_PRIVATE, IPC_CREAT | 0660) == -1))
    {
        perror("Errore creazione coda_in\n");
        exit(EXIT_FAILURE);
    }
    
    if ((coda_out = msgget(chiave_out, IPC_CREAT | 0660) == -1))
    {
        perror("Errore creazione coda_out\n");
        exit(EXIT_FAILURE);
    }

    //IN1
    if (fork() == 0)
    {
       
    }

    //IN2
    if (fork() != 0)
    {
           
    }
   
    //DB
    if (fork() != 0)
    {
                
    }

    //OUT
    if (fork() != 0)
    {
                
    }
     
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    msgctl(coda_in, IPC_RMID, NULL);
    msgctl(coda_out, IPC_RMID, NULL);
}


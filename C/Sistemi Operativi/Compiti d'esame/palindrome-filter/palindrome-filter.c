#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>
#include <unistd.h>

#define MAX_LEN 64
#define S_MUTEX 0
#define S_EMPTY 1
#define S_FULL  2

int WAIT(int sem_des, int numero_semaforo)
{
    struct sembuf operazioni[1] = { {numero_semaforo, -1, 0} };
    return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, int numero_semaforo)
{
    struct sembuf operazioni[1] = { { numero_semaforo, +1, 0 } };
    return semop(sem_des, operazioni, 1);
}

void R_func(int input_si_no, int idsem, int idmem, char *pathname)
{
    FILE *in;
    int open_file;
    char buffer[MAX_LEN];
    char *p;

    if (input_si_no == 1)//è stato passato il file di input
    {
        if ((p = (char *)shmat(idmem, NULL, 0)) == (char*) -1)
        {
            perror("Errore attaccamento memoria condivisa su R_func\n");
            exit(EXIT_FAILURE);
        }
        
        if ((open_file = open(pathname, O_RDONLY)) == -1)
        {
            perror("Errore apertura file in R_func\n");
            exit(EXIT_FAILURE);
        }   

        if ((in = fdopen(open_file, "r")) == NULL)
        {
            perror("Errore conversione file to FILE in R_func\n");
            exit(EXIT_FAILURE);
        }

    }
    else
    {
        in = stdin;
    }
    
    fgets(buffer, MAX_LEN, in);

    WAIT(idsem, S_EMPTY);
    WAIT(idsem, S_MUTEX);
    
    strcpy(p, buffer);

    SIGNAL(idsem, S_MUTEX);
    SIGNAL(idsem, S_FULL);
    
}

void W_func(int input_si_no, int idsem, int idmem, char *pathname)
{
    FILE *out;
    char* p;
    int open_file;

    if (input_si_no ==1)
    {
        if ((p = (char *)shmat(idmem, NULL, 0)) == (char*) -1)
        {
            perror("Errore attaccamento memoria condivisa su W_func\n");
            exit(EXIT_FAILURE);
        }

        if ((open_file = open(pathname, O_WRONLY | O_TRUNC)) == -1)
        {
            perror("Errore apertura file in W_func\n");
            exit(EXIT_FAILURE);
        }   

        if ((out = fdopen(open_file, "w")) == NULL)
        {
            perror("Errore conversione file to FILE in W_func\n");
            exit(EXIT_FAILURE);
        }

    }
    else
    {
        out = stdout;
    }

    WAIT(idsem, S_FULL);
    WAIT(idsem, S_MUTEX);
    
    //variante con fwrite o fputs
    fprintf(out, "%s", p);

    SIGNAL(idsem, S_MUTEX);
    SIGNAL(idsem, S_EMPTY);
}


int main(int argc, char *argv[])
{
    int con_input = 1, con_output = 1;
    int idsem, idmem;
    char* p;

    // switch (argc)
    // {
    //     case 2:
    //         con_input = 1;
    //     break;
    //     case 3:
    //         con_output = 1;
    //     break;

    //     default:
    //         printf("Usage: palindrome-filter-3 [input file] [output file]\n");
    //     exit(EXIT_FAILURE);
    // }

    if ((idmem = shmget(IPC_PRIVATE, MAX_LEN * sizeof(char *), IPC_CREAT | 0660)) == -1)
    {
        perror("Errore shmget\n");
        exit(EXIT_FAILURE);
    }

    if ((p = (char *)shmat(idmem, NULL, 0)) == (char*) -1)
    {
        perror("Errore attaccamento memoria condivisa\n");
        exit(EXIT_FAILURE);
    }

    if ((idsem = semget(IPC_PRIVATE, 3, IPC_CREAT | 0660)) == -1)
    {
        perror("Errore semget\n");
        exit(EXIT_FAILURE);
    }

    semctl(idsem, S_MUTEX, SETVAL, 1);
    semctl(idsem, S_FULL, SETVAL, 0);
    semctl(idsem, S_EMPTY, SETVAL, MAX_LEN);


    for (int i = 0; i < 5; i++)
    {       
        if (fork() == 0)
        {
            R_func(con_input, idsem, idmem, argv[1]);
        }

        //padre
        WAIT(idsem, S_FULL);
        WAIT(idsem, S_MUTEX);

        char *tmp_buffer = p;

        SIGNAL(idsem, S_MUTEX);
        SIGNAL(idsem, S_EMPTY);

        int pal = 0;

        for (int i = 0; i < strlen(tmp_buffer); i++)
        {
            if (tmp_buffer[i] != tmp_buffer[strlen(tmp_buffer) - i])
            {
                pal = 0;
            }
        }

        if (pal != 0)
        {
            WAIT(idsem, S_EMPTY);
            WAIT(idsem, S_MUTEX);

            strcpy(p, tmp_buffer);

            SIGNAL(idsem, S_MUTEX);
            SIGNAL(idsem, S_FULL);
        }


        if (fork() == 0)
        {
            W_func(con_output, idsem, idmem, argv[2]);
        }
    }
}

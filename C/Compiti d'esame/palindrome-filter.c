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

#define MAX_LEN 64

void R_func(char* path, int shmid, int semid)
{
    char* buffer_memoria;
    struct stat stat_file;
    struct sembuf SIGNAL[1] = { {0, +1, 0} };


    if ((buffer_memoria = (char *)shmat(shmid, NULL, 0)) == (char*)-1)
    {
        perror("Error R_func shmat\n");
        exit(EXIT_FAILURE);
    }

    if (lstat(path, &stat_file) == -1)
    {
        perror("Error R_func lstat\n");
        exit(EXIT_FAILURE);
    }
    
    switch (path)
    {
    case (!stat_file.st_mode &  S_ISREG):
        fgets(buffer_memoria, MAX_LEN, stdin);
        semop(semid, SIGNAL, 1);
        break;

    default:
        fgets(buffer_memoria, MAX_LEN, path);
        semop(semid, SIGNAL, 1);
        break;
    }
}

void W_func()
{

}


int main(int argc, char const *argv[])
{
    int semid, shmid;
    // if (argc != 3)
    // {
    //     printf("Usage: palindrome-filter-3 [input file] [output file]\n");
    //     exit(EXIT_FAILURE);
    // }

    // struct sembuf WAIT[1] = { {0, -1,0} };
    // struct sembuf SIGNAL[1] = { {0, +1, 0} };
    // char *buffer_memoria;
    // char *inizio;
    // char *fine;

    // if ((buffer_memoria = (char *)shmat(shmid, NULL, 0)) == (char*)-1)
    // {
    //     perror("shmat\n");
    //     exit(EXIT_FAILURE);
    // }
    
    // semop(semid, WAIT, 1);
    
    // for (int i = 0; i < strlen(buffer_memoria); i++)
    // {
    //     int j = (int)strlen[buffer_memoria];
    //     if (inizio[i] != fine [j])
    //     {
    //         break;
    //     }
    //     j--;
    // }
    
    // semop(semid, SIGNAL, 1);
    





}

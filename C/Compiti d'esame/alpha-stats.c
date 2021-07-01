#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

#define DIM_STATS 26


void AL_func(int shmid_Char, int shmid_Stats, int semid)
{
    char *c;
    char *s;

    if ( (c = (char *)shmat(shmid_Char, NULL, 0)) == (char *)-1 )
    {
        perror("Errore shmat AL_func memoria_char\n");
        exit(EXIT_FAILURE);
    }

    if ( (s = (char *)shmat(shmid_Char, NULL, 0)) == (char *)-1 )
    {
        perror("Errore shmat AL_func memoria_char\n");
        exit(EXIT_FAILURE);
    }


    
}

void MZ_func()
{

}


int main(int argc, char const *argv[])
{
    int memoria_char, memoria_stats;  

    struct stat map_stat;
    int fd;
    char *mapp;
    char *op_memoria;

    if (argc < 2)
    {
        printf("Usage: alpha-stats.c <file.txt>\n");
        exit(EXIT_FAILURE);
    }

    if ( (memoria_char = shmget(IPC_PRIVATE, 1, IPC_CREAT | 0660)) == -1 )
    {
        perror("errore apertura memoria_char\n");
        exit(EXIT_FAILURE);
    }
    
    if ( (memoria_stats = shmget(IPC_PRIVATE, sizeof(long int )*DIM_STATS, IPC_CREAT | 0660)) == -1 )
    {
        perror("errore apertura memoria_stats\n");
        exit(EXIT_FAILURE);
    }


    if ( (fd = open(argv[1], O_RDONLY)) == -1)
    {
        perror("Errore apertura file.txt\n");
        exit(EXIT_FAILURE);
    
    if (fstat(fd, &map_stat) == -1)
    {
        perror("errore su fstat\n");
        exit(EXIT_FAILURE);
    }
    
    if (!S_ISREG(map_stat.st_mode))
    {
        fprintf(stderr, "%s non è un file\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if ( (mapp = mmap(NULL, map_stat.st_size, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {
        perror("Errore su map\n");
        exit(EXIT_FAILURE);
    }
    
    if ( (op_memoria = (char*)shmat(memoria_char, NULL, 0)) == (char*)-1)
    {
        perror("Errore shmat memoria_char\n");
        exit(EXIT_FAILURE);
    
    for (int i = 0; i < strlen(op_memoria); i++)
    {
        op_memoria[i] = 0;
    }
    
    for (int i = 0; i < strlen(mapp); i++)
    {
        mapp[i] = tolower(mapp[i]);
        if ( (mapp[i] >= 'a' && mapp[i] <= 'z') || (mapp[i] >= 'A' && mapp[i] <= 'Z') )
        {
            op_memoria[0] = mapp[i]; 
        }
    }

    if (op_memoria[0] >= 'a' ||)
    {
        /* code */
    }
    

    //chiusura map e file
    if ( (munmap(mapp, map_stat.st_size)) == -1)
    {
        perror("Errore dismessione mappatura\n");
    }
    close(fd);
     

    
    
    shmctl(memoria_char, IPC_RMID, NULL);
    shmctl(memoria_stats, IPC_RMID, NULL);
}

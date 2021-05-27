/*
    Homework n.1

    Scrivere un programma in linguaggio C che permetta di copiare un numero
    arbitrario di file regolari su una directory di destinazione preesistente.

    Il programma dovra' accettare una sintassi del tipo:
     $ homework-1 file1.txt path/file2.txt "nome con spazi.pdf" directory-destinazione
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>

int main(int argc, char *argv[]) 
{
    char buffer[BUFSIZ];
    struct stat stat_buffer;
    char* dir_dest = argv[argc - 1];
    int sd, fd, size;
    
    if (argc < 3)
    {
        printf("Usage: <file>, <destinazione>\n");
        exit(1);
    }

    if ((stat(dir_dest, &stat_buffer)) == -1)
    {
        perror("Error stat\n");
        exit(1);
    }

    if (!S_ISDIR(stat_buffer.st_mode))
    {
        printf("%s non è una directory\n", stat_buffer);
        exit(1);
    }
    
    for (int i = 0; i < argc - 1; i++)
    {
        if ((sd = open(argv[i], O_RDONLY)) == -1)
        {
            perror(argv[i]);
            exit(1);
        }

        /*if ((stat(sd, & stat_buffer)) == -1)
        {
            perror("Error stat2\n");
            exit(1);
        }
        
        if (!S_ISREG(stat_buffer.st_mode))
        {
            printf("%s non è un file regolare\n", stat_buffer);
            exit(1);
        } */  

        if ((fd = open(buffer, O_WRONLY | O_TRUNC | O_CREAT)) == -1)
        {
            perror(buffer);
            exit(1);
        }
        w
        do
        {
            if ((size = read(sd, buffer, BUFSIZ)) == -1)
            {
                perror(argv[1]);
                exit(1);
            }

            if (write(fd, buffer, size) == -1)
            {
                perror(argv[2]);
                exit(1);
            }
        } while (size == BUFSIZ);
        
        close(sd);
        close(fd);
        
    }
}
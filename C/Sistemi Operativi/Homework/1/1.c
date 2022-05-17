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
#include <errno.h>


int main(int argc, char const *argv[])
{
    struct stat controllo_file;
    int source_file, dest_file, size;
    char buffer[BUFSIZ];
    char *p1, *p2;

    if (argc < 3)
    {
        printf("Usage: <file> ... <directory>");
        exit(1);
    }

    for (int i = 1; i < argc - 1; i++)
    {
        if ( (source_file = open(argv[i], O_RDONLY)) == -1 )
        {
            //perror(argv[i]);
            printf("apertura file source non riuscita\n");
            exit(EXIT_FAILURE);
        }

        strncpy(buffer, argv[argc - 1], BUFSIZ);
        size = strlen(buffer);
        strncpy(buffer + size, "/", BUFSIZ - size);
        size++;

        p1 = p2 = argv[i];
        while (*p2 != '\0') 
        {
            if (*p2 == '/') p1 = p2+1;
            p2++;
        }
        strncpy(buffer + size, p1, BUFSIZ - size);

        if ( (fstat(source_file, &controllo_file)) == -1 )
        {
            perror("stat");
            exit(EXIT_FAILURE);
        }
        
        if (!S_ISREG(controllo_file.st_mode))
        {
            printf("non è un file regolare\n");
            exit(EXIT_FAILURE);
        }
        
        if ( (dest_file = open(buffer, O_WRONLY|O_TRUNC|O_CREAT, 0660)) == -1 )
        {
            perror(buffer);
            exit(EXIT_FAILURE);
        }

        do
        {
            if ( (size = read(source_file, buffer, BUFSIZ)) == -1 )
            {
                perror(argv[1]);
                exit(EXIT_FAILURE);
            }

            if (write(dest_file, buffer, size) == -1)
            {
                perror(argv[2]);
                exit(EXIT_FAILURE);
            }
        } while (size == BUFSIZ);

        close(source_file);
        close(dest_file);
    }
    
}

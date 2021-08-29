/**
 *  copia il contenuto di un file sorgente su un file di destinazione
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{   
    int sorgente, destinazione;
    char buffer[BUFSIZ];
    int size = 0;

    if (argc != 3)
    {
        printf("Usage: <sorgente>, <destinazione>\n");
        exit(1);
    }

    if ( (sorgente = open(argv[1], O_RDONLY)) == -1)
    {
        perror(argv[1]);
        exit(1);
    }
    
    if ( (destinazione = open(argv[2], O_WRONLY|O_TRUNC|O_CREAT)) == -1)
    {
        perror(argv[2]);
        exit(1);
    }
    
    
    do
    {
        if ((size = read(sorgente, buffer, BUFSIZ)) == -1)
        {
            perror(argv[1]);
            exit(1);
        }
        
        if (write(destinazione, buffer, size))
        {
            perror(argv[2]);
            exit(1);
        }
    } while (size == BUFSIZ);
    
    close(sorgente);
    close(destinazione);
    
    

    
}

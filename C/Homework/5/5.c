/*
    Homework n.5

    Estendere l'esempio 'nanoshell.c' ad una shell piu' realistica in cui
    si possono:
    - passare argomenti al comando invocato (per semplicita', assumiamo
    che questi non contengano spazi);
    - usare la redirezione dei canali di input/output/error;
    - mandare un comando in esecuzione in background (con la '&' finale).

    Esempi di invocazione che la shell dovrebbe supportare sono:
    $ cal 3 2015
    $ cp /etc/passwd /etc/hosts /tmp
    $ cat </dev/passwd >/tmp/passwd
    $ cat filechenonesiste 2>/dev/null
    $ ls -R /etc/ &
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LEN_BUFFER 1024

int main(int argc, char const *argv[])
{
    char comando[LEN_BUFFER];
    int len = 0;
    pid_t pid;
    
    while (1)
    {
        printf("Digitare un comando da eseguire ('exit' per uscire)\n");
        fgets(comando, LEN_BUFFER, stdin);
        len = strlen(comando);

        if (comando[len - 1] == '\n')
        {
            comando[len - 1] = '\0';
        }

        if (strcmp(comando, "exit") == 0)
        {
            break;
        }
        
        pid = fork();

        if (pid == -1)
        {
            perror(fork);
            exit(1);
        }
        
        if (pid == 0)
        {
            execlp(comando, comando, NULL);
            fprintf(stderr, "Errore nell'esecuzione di '%s'\n", comando);
            exit(2);
        }
        else
        {
            wait(NULL);
        }   
    }
    exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/mman.h>
#define BUFF_SIZE 4096

int P(int *pipe){
    close(pipe[1]);
}

int R(int *pipe, char const *file){
    int fdin;
    struct stat sb;
    char *src;
    char* buffer[BUFF_SIZE];
    
    close(pipe[0]);

    /* apre il file in lettura */
    if ((fdin = open(file, O_RDONLY)) == -1) {
        perror(argv[1]);
        exit(1);
    }

    /* recupera le informazioni sul file */
    if (fstat(fdin, &sb) < 0) {
        perror(argv[1]);
        exit(1);
    }

    printf("dimensione %d", sb.st_size);
   

    /* mappa il file sorgente */
    if ((src = (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fdin,
                            0)) == MAP_FAILED) {
        perror("mmap su sorgente");
        exit(1);
    }


    if (write(pipefd[1], buffer, strlen(buffer) + 1) == -1) {
            perror("pipe");
            exit(1);
    }

}

int W(){

}

int main(int argc, char const *argv[]){
    int pipeRtoP[2];
    int pipePtoW[2];

    if(argc <= 1){
        perr("inserire file\n");
        exit(0);
    }

    if(pipe(pipeRtoP) == -1) {
        perror("pipe");
        exit(1);
    }

    if(pipe(pipePtoW) == -1) {
        perror("pipe");
        exit(1);
    }


    if(fork() == 0) P(pipePtoW);        
    if(fork() == 0) W();
    R(pipeRtoP, argv[1]);
    wait(NULL);
    wait(NULL);
    
    
    exit(0);
}

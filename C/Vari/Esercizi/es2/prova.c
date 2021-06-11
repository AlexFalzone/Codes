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
#include <ctype.h>
#include <sys/mman.h>
#define BUFF_SIZE 4096

int isPalindrome(char str[]){
    int l = 0;
    int h = strlen(str) - 1;
    while (h > l){
        if (str[l++] != str[h--]){
            return 0;   //non palindroma
        }
    }
    return 1; //palindroma
}

int P(int *pipe1, int *pipe2){
    char buffer[BUFF_SIZE];

    close(pipe2[1]);
    close(pipe1[0]);

    while(read(pipe2[0], buffer, BUFF_SIZE) != 0){
        if(isPalindrome(buffer)){
            if(write(pipe1[1], buffer, strlen(buffer) + 1) == -1){
                perror("pipe");
                exit(1);
            }
        }
    }
    exit(0);
}

int R(int *pipe, char const *file){
    int fdin;
    struct stat sb;
    char *src;
    char buffer[BUFF_SIZE];
    char string[BUFF_SIZE];
    
    close(pipe[0]);

    /* apre il file in lettura */
    if ((fdin = open(file, O_RDONLY)) == -1) {
        perror(file);
        exit(1);
    }

    /* recupera le informazioni sul file */
    if (fstat(fdin, &sb) < 0) {
        perror("errore stat");
        exit(1);
    }

    /* mappa il file */
    if((src = (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fdin,0)) == MAP_FAILED) {
        perror("mmap su sorgente");
        exit(1);
    }

    int i=0;
    int j=0;
    while(i<sb.st_size){
        if(!isspace(src[i])){
            string[j]=src[i];
            i++;
            j++;
        }else{
            string[j] = '\0';
            i++;
            j=0;
            printf("Leggo dal file e invio: %s\n",string);
            if(write(pipe[1], string, strlen(string) + 1) == -1){
                perror("pipe");
                exit(1);
            }
        }
    }

    munmap(src, sb.st_size);
    exit(0);
}

int W(int* pipe){
    char buffer[BUFF_SIZE];
    close(pipe[1]);
    
    while(read(pipe[0], buffer, BUFF_SIZE) != 0){
        printf("stringa palindroma: %s\n", buffer);
    }
    exit(0);
}


int main(int argc, char const *argv[]){
    int pipeRtoP[2];
    int pipePtoW[2];

    if(argc <= 1){
        perror("parametri\n");
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

    if(fork() == 0) P(pipePtoW, pipeRtoP);  
    else if(fork() == 0) W(pipePtoW);
    else R(pipeRtoP, argv[1]);    

    wait(NULL);
    wait(NULL);
    
    exit(0);
}

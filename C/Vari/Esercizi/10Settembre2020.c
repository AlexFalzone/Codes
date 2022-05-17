#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/sem.h>
#include <time.h>
#include <ctype.h>
#include <sys/mman.h>

#define MAXLEN 1024
typedef struct {
    char line[4096];  // il numero di occorrenze trovate per ogni lettera
} msg;
void P(int* pipe1,int* pipe2){
    char buffer[MAXLEN];
    close(pipe1[1]);
    int c=0;
    while(1){
        if (read(pipe1[0], buffer, MAXLEN) == -1) {
            perror("pipe P");
            exit(1);
        }
        c++;
        if(c>10) break;
        printf("Sono il processo P e leggo dalla pipe %s\n",buffer);
        int size=strlen(buffer);
        int j=size-1;
        int send=0;
        for(int i=0;i<size/2;i++){
            if(buffer[i]!=buffer[j]){
                send=1;
                break;
            }
            j--;
        }
        if(send==0){
            printf("la stringa è palindroma e la invio\n");
        }else{
            printf("la stringa non è palindroma e non la invio\n");
        }
    }
}
void W(int* pipe2){
    exit(0);
}
void R(int pipe1[], char const * file){
    char* p;
    struct stat statbuf;
    char s[MAXLEN];
    int mem;
    int fd;
    if ((fd = open(file, O_RDONLY, 0660))== -1) {
        perror("file");
        exit(1);
    }
    close(pipe1[0]);
    stat(file,&statbuf);
    if ((p = (char*) mmap(NULL, statbuf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }
    int j=0;
    int i;
    for(i=0;i<statbuf.st_size+1;i++){
        if(!isspace(p[i])){
            s[j]=p[i];
            j++;
            printf("C: %c\n",p[i]);
        }else{
            s[j]='\0';
            printf("Leggo dal file e invio: %s\n",s);
            if (write(pipe1[1], s, strlen(s) + 1) == -1) {
                perror("pipe R1");
                exit(1);
            }
            j=0;
        }
    }
    s[j]='\0';
    printf("Leggo dal file e invio: %s\n",s);
    if (write(pipe1[1], s, strlen(s) + 1) == -1) {
        perror("pipe R2");
        exit(1);
    }
    strcpy(s,"STOP");
    if (write(pipe1[1], s, strlen(s) + 1) == -1) {
        perror("pipe R3");
        exit(1);
    }
    munmap(p, statbuf.st_size);
}

int main(int argc, char const *argv[])
{
    int pipe1[2];
    int pipe2[2];
    if(argc<=1){
        perror("argc");
        exit(0);
    }
    if(pipe(pipe1)==-1){
        perror("pipe1");
        exit(0);
    }
    if(pipe(pipe2)==-1){
        perror("pipe2");
        exit(0);
    }
    if(fork()==0) R(pipe1,argv[1]);
    if(fork()==0) W(pipe2);
    P(pipe1,pipe2);
    wait(NULL);
    wait(NULL);
    exit(0);
}

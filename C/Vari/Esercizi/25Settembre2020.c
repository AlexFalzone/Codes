#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/sem.h>
#include <time.h>
#include <ctype.h>

typedef struct 
{
   long mytype;
   char word[255];
   int eof;
} msg;

void R1(int ds_coda,const char* file){
    FILE* in;
    char *c;
    msg message;
    if ((in = fopen(file, "r")) == NULL) {
        perror(file);
        exit(1);
    }
    while ((c = fgets(c,255,in)) != NULL){
        message.mytype=1;
        message.eof=0;
        strcpy(message.word,c);
        printf("La parola letta dal processo R1 è: %s", message.word);
        if(msgsnd(ds_coda, &message, sizeof(msg) - sizeof(long), 0)==-1){
            perror("msgsnd");
        }
    }
    printf("R1 invia stop \n");
    message.mytype=2;
    message.eof=-1;
    strcpy(message.word,"");
    if(msgsnd(ds_coda, &message, sizeof(msg) - sizeof(long), 0)==-1){
        perror("msgsnd");
    }
    exit(0);
}
void R2(int ds_coda,const char* file){
    FILE* in;
    char *c;
    msg message;
    if ((in = fopen(file, "r")) == NULL) {
        perror(file);
        exit(1);
    }
    while ((c = fgets(c,255,in)) != NULL){
        message.eof=0;
        message.mytype=1;
        strncpy(message.word,c,255);
        printf("La parola letta dal processo R2 è: %s", message.word);
        if(msgsnd(ds_coda, &message, sizeof(msg) - sizeof(long), 0)==-1){
            perror("msgsnd");
        }
    }
    printf("R2 invia stop \n");
    message.mytype=2;
    message.eof=-1;
    strcpy(message.word,"");
    if(msgsnd(ds_coda, &message, sizeof(msg) - sizeof(long), 0)==-1){
        perror("msgsnd");
    }
    exit(0);
}
void W(int* pipefd){
    //close(pipefd[1]);
    char s[255];
    int c=0;
    // while(1){
        if (read(pipefd[0], s, 255) == -1) {
            perror("pipe");
            exit(1);
        }
        printf("W: %s\n",s);
        if (read(pipefd[0], s, 255) == -1) {
            perror("pipe");
            exit(1);
        }
        printf("W: %s\n",s);
    //     if(strcmp(s,"")==0){
    //         c++;
    //         printf("C: %d",c);
    //         if(c==2) break;
    //     }
    //     printf("W: %s/n",s);
    // }
    exit(0);
}
void P(const char* file1,const char* file2){
    int ds_coda;
    int c=0;
    char* dizionario[200];
    char s[255];
    msg message;
    int num_elementi=0;
    int notsend;
    int pipefd[2];
    key_t chiave = 100;
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
    //creazione della coda utilizzata per lo scambio di messaggi dal processo P, R1 e R2
    if ((ds_coda = msgget(IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0660)) == -1) {
        perror("msgget");
        exit(1);
    }
    if(fork()==0) R1(ds_coda,file1);
    if(fork()==0) R2(ds_coda,file2);
    if(fork()==0){
        close(pipefd[1]);
        if (read(pipefd[0], s, 255) == -1) {
            perror("pipe");
            exit(1);
        }
        printf("W: %s\n",s);
        if (read(pipefd[0], s, 255) == -1) {
            perror("pipe");
            exit(1);
        }
        printf("W: %s\n",s);
    }
    // printf("lol: %s",message.word);
    close(pipefd[0]);
    while(1){
        if (msgrcv(ds_coda, &message, sizeof(msg) - sizeof(long), 0, 0) == -1) {
            perror("msgrcv P");
        }
        if(message.eof == -1){
            c++;
            if(c==2) break;
        }else{
            strcpy(s,message.word);
            printf("Il processo P ha ricevuto %s\n",s);
            notsend=1;
            // for(int j=0;j<num_elementi;j++){
            // //     if(strcasecmp(s,dizionario[j])==0){
            // //         //printf("metto notsend a 0");
            // //         notsend=0;
            // //     }
            // // }
            if(notsend==1){ //se devo inviare
                dizionario[num_elementi]=s;
                num_elementi++;
                printf("Il processo P invia %s",s);
                if (write(pipefd[1], s, strlen(s) + 1) == -1) {
                    perror("pipe");
                    exit(1);
                }
            }
        }
    }
    //if(fork()==0) W(pipefd);
    wait(NULL);
    wait(NULL);
    wait(NULL);
    //chiusura della coda
    msgctl(ds_coda, IPC_RMID, NULL);
    exit(0);
}

int main(int argc, char const *argv[])
{
    if(argc<3){
        perror("Rispettare la sintassi <file-1> <file-2>");
    }
    if(fork() == 0) {
        P(argv[1],argv[2]);
    }
    wait(NULL);
    exit(0);
}

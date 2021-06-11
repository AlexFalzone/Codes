#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#define TEXT_DIM 4096
#define ID 100
#define GENITORE 300

typedef struct{
    long type;              
    char word[TEXT_DIM];    
} msg;

typedef struct{
    long type;              
    char word[TEXT_DIM];
    int numriga;    
} msgRisposta;

void children(int codaRichieste, int codaRisposte, char const *file , int id){
    FILE* in;
    msg message;
    char* buffer;
    int numriga;
    msgRisposta messageRisposta;
    if((in = fopen(file, "r")) == NULL){
        perror("file");
        exit(1);
    }
    while(1){
        if(msgrcv(codaRichieste, &message, sizeof(msg) - sizeof(long), id, 0) == -1){
            perror("msgrcv J 1");
            exit(1);
        }
        if(strcmp(message.word,"EOF")) break;
        numriga=0;
        while((fgets(buffer, TEXT_DIM, in)) != NULL){
            numriga++;
            if(strstr(buffer,message.word)==0){
                printf("Trovata parola %s nella riga %d",message.word, numriga);
                messageRisposta.numriga=numriga;
                messageRisposta.type=GENITORE;
                strcpy(messageRisposta.word,buffer);
                if(msgsnd(codaRisposte, &messageRisposta, sizeof(msg)-sizeof(long), 0) == -1){
                    perror("msgsnd J 2");
                    exit(1);
                }
            }
        }
    }
    exit(0);
}

int main(int argc, char const *argv[]){
    int codaRichieste;
    int codaRisposte;
    msg message;
    int countchildren=0;
    key_t key=50;
    if((codaRichieste = msgget(IPC_PRIVATE, IPC_CREAT|0600)) == -1){
        perror("msgget");
        exit(1);
    }
    if((codaRisposte = msgget(IPC_PRIVATE, IPC_CREAT|0600)) == -1){
        perror("msgget");
        exit(1);
    }
    int i=argc-1;
    while(strcmp(argv[i],"@")!=0){
        printf("Riscontro il file: %s ed inizializzo un figlio\n",argv[i]);
        countchildren++;
        if(fork()==0) children(codaRichieste,codaRisposte,argv[i], ID + countchildren);
        i--;
    }
    i=1;
    while(strcmp(argv[i],"@")!=0){
        printf("Riscontro della parola: %s e la invio ai figli\n",argv[i]);
        for(int j=1;j<=countchildren;j++){
            strcpy(message.word,argv[i]);
            printf("%s\n",message.word);
            message.type = ID + j;
            printf("%lu\n",message.type);
            if(msgsnd(codaRichieste, &message, sizeof(msg) - sizeof(long), 0)==-1){
                perror("msgsnd della word");
            }
        }
        i++;
        exit(0);
    }
    for(int i=1;i<=countchildren;i++){
        message.type = ID + i;
        strcpy(message.word,"EOF");
        if(msgsnd(codaRichieste, &message, sizeof(msg) - sizeof(long), 0)==-1){
            perror("msgsnd");
        }
    }
    for(int i=0;i<countchildren;i++){
        wait(NULL);
    }
    msgctl(codaRichieste, IPC_RMID, NULL);
    msgctl(codaRisposte, IPC_RMID, NULL);
    exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/mman.h>
#include <fcntl.h>
//mai usare stringhe (char*) nelle code
#define TEXT_DIM 300
typedef enum {
    CMD_IN1,
    CMD_IN2,
    CMD_DB,
    REPLY_ERROR,
    REPLY_DATA,
    REPLY_DATA_STOP
} type_payload;

typedef struct {
    long type;              
    type_payload payload;     //tipo di query da inviare  
    long valore;  
    char query[TEXT_DIM];          
} msg;

void in1(int queue,char* filename){
    FILE* f;
    char* c;
    msg message;
    int i=1;
    if ((f = fopen(filename, "r")) == NULL) {
        perror(filename);
        exit(1);
    }
    while((c=fgets(c,TEXT_DIM,f))!=NULL){
        if (c = strtok(c, ":")) { 
            message.type=1;
            message.payload=CMD_IN1;
            strncpy(message.query, c, TEXT_DIM);
            message.valore=0;
            if (msgsnd(queue, &message, sizeof(msg) - sizeof(long), 0) == -1) {
                printf("Errore durante l'inserimento del messaggio.\n");
                exit(1);
            }
            printf("IN1: Inviata query n.%d %s\n",i,message.query);
            i++;
        }
    }
    strcpy(message.query,"STOP");
    message.payload = REPLY_DATA_STOP;
    msgsnd(queue, &message, sizeof(msg) - sizeof(long), 0);
    exit(0);
}

void in2(int queue,char* filename){
    FILE* f;
    char* c;
    msg message;
    int i=1;
    if ((f = fopen(filename, "r")) == NULL) {
        perror(filename);
        exit(1);
    }
    while((c=fgets(c,TEXT_DIM,f))!=NULL){
        if(c = strtok(c, ":")) { 
            message.type=2;
            message.payload=CMD_IN2;
            strncpy(message.query, c, TEXT_DIM);
            message.valore=0;
            if (msgsnd(queue, &message, sizeof(msg) - sizeof(long), 0) == -1) {
                printf("Errore durante l'inserimento del messaggio.\n");
                exit(1);
            }
            printf("IN2: Inviata query n.%d %s\n",i,message.query);
            i++;
        }
    }
    strcpy(message.query,"STOP");
    message.payload = REPLY_DATA_STOP;
    msgsnd(queue, &message, sizeof(msg) - sizeof(long), 0);
    exit(0);
}
void database(int queueF,int queueDB,char* filename){
    FILE* f;
    char nome[TEXT_DIM];
    char valore[TEXT_DIM];
    char* prova;
    char *id;
    int val;
    msg message;
    msg message2;
    char* p;
    int fd;
    struct stat statbuf;
    if ((fd = open(filename, O_RDONLY)) == -1) {
        perror(filename);
        exit(1);
    }

    if (fstat(fd, &statbuf) == -1) {
        perror("fstat");
        exit(1);
    }
    if ((p = mmap(NULL, statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0)) ==
        MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }
    int c=0;
    while(1){
        msgrcv(queueF, &message, sizeof(msg) - sizeof(long), 0, 0);
        if(message.payload == REPLY_DATA_STOP){
            c++;
            if(c==2){
                strcpy(message.query,"STOP");
                message.payload = REPLY_DATA_STOP;
                msgsnd(queueDB, &message, sizeof(msg) - sizeof(long), 0);
                break;
            }
        }
        for (int i = 0; i < statbuf.st_size; i++){
            int j=0;
            while(p[i]!=':' && p[i]!='\0'){
                nome[j]=p[i];
                i++;
                j++;
            }
            nome[j]='\0';
            //printf("nome: %s\n",nome);
            i++;
            j=0;
            while(p[i]!='\n' && p[i]!='\0'){
            valore[j]=p[i];
                j++;
                i++;
            }
            valore[j]='\0';
            //printf("valore: %s\n",valore);
            val=atoi(valore);
            if(strcmp(nome,message.query)==0){
                //DB: query 'distesero' da IN1 trovata con valore 28809
                if(message.type==1){
                    id="IN1";
                }else{
                    id="IN2";
                }
                printf("DB: query %s da %s trovata con valore %d\n",nome,id,val);
                message2.payload=CMD_DB;
                strncpy(message2.query, nome, TEXT_DIM);
                message2.valore=val;
                message2.type=message.type;
                if (msgsnd(queueDB, &message2, sizeof(msg) - sizeof(long), 0) == -1) {
                    printf("Errore durante l'inserimento del messaggio.\n");
                    exit(1);
                }
            }
        }
    }
    if (munmap(p, statbuf.st_size) == -1) {
        perror("munmap");
        exit(1);
    }
    exit(0);
}
void out(int queueDB){
    //OUT: ricevuti n.93 valori validi per IN1 con totale 1513996
    msg message;
    long IN1=0,IN2=0;
    int i=0;
    int j=0;
    while (1){
        msgrcv(queueDB, &message, sizeof(msg) - sizeof(long), 0, 0);
        if(message.payload==REPLY_DATA_STOP) break;
        if(message.type==1){
            IN1+=message.valore;
            i++;
        }else{
            IN2+=message.valore;
            j++;
        }
    }
    printf("OUT: ricevuti n.%d valori validi per IN1 con un totale di %lu\n",i,IN1);
    printf("OUT: ricevuti n.%d valori validi per IN2 con un totale di %lu\n",j,IN2);
    exit(0);
}
int main(int argc, char const *argv[])
{
    int codaFigli;
    int codaDatabase;
    key_t chiave = 155;
    if (argc <= 3) {
        fprintf(stderr, "uso: %s <directory 1> <directory 2> ...\n", argv[0]);
        exit(1);
    }

    if ((codaFigli  = msgget(chiave, IPC_CREAT | IPC_EXCL | 0660)) == -1) {
        perror("msgget");
        exit(1);
    }
    if ((codaDatabase = msgget(chiave+1, IPC_CREAT|0660)) == -1) {
        perror("msgget");
        exit(1);
    }
    if(fork()==0) in1(codaFigli,argv[2]);
    if(fork()==0) in2(codaFigli,argv[3]);
    if(fork()==0) out(codaDatabase);
    if(fork()==0)database(codaFigli,codaDatabase,argv[1]);
    for(int i=0;i<3;i++){
        wait(NULL);
    }
    msgctl(codaDatabase, IPC_RMID, NULL);
    msgctl(codaFigli, IPC_RMID, NULL);
}

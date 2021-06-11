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
#define CARTA 1
#define FORBICE 2
#define SASSO 3
#define GIUDICE 100
#define p1 30
#define p2 40
#define p1rec 303
#define p2rec 403

typedef enum{
    REQUEST,
    SEND,
    EXIT,
} type_payload;

typedef struct{  
    long mtype; // 0=P1 e 1=P2
    type_payload payload; 
    int mossa; // 0=CARTA 1=FORBICE 2=SASSO
} msg;

void P1(int coda){
    msg messaggio;
    msg messaggioGiudice;

    while(1){
        if (msgrcv(coda, &messaggioGiudice, sizeof(msg) - sizeof(long) , p1, 0) == -1) {
            perror("msgrcv P1");
            exit(1);
        }
        if(messaggio.payload==EXIT) break;
        messaggio.mossa=1;
        messaggio.mtype=p1rec;
        messaggio.payload=SEND;
        if (msgsnd(coda, &messaggio, sizeof(msg)-sizeof(long), 0) == -1) {
            perror("msgsnd P1");
            exit(1);
        }
        //sleep(1);
        switch (messaggio.mossa)
        {
        case CARTA:
            printf("P1: mossa 'CARTA'\n");
            break;
        case FORBICE:
            printf("P1: mossa 'FORBICE'\n");
            break;
        case SASSO:
            printf("P1: mossa 'SASSO'\n");
            break;
        default:
            break;
        }
      //  exit(0);
    }
    exit(0);
}

void P2(int coda){
    srand(time(NULL));
    msg messaggio;
    msg messaggioGiudice;

    while(1){
        if (msgrcv(coda, &messaggioGiudice, sizeof(msg) - sizeof(long), p2, 0) == -1) {
            perror("msgrcv P2");
            exit(1);
        }
        if(messaggio.payload==EXIT) break;
        messaggio.mossa=1;
        messaggio.mtype=p2rec;
        messaggio.payload=SEND;
        if (msgsnd(coda, &messaggio, sizeof(msg)-sizeof(long), 0) == -1) {
            perror("msgsnd P2");
            exit(1);
        }
        switch (messaggio.mossa)
        {
        case CARTA:
            printf("P2: mossa 'CARTA'\n");
            break;
        case FORBICE:
            printf("P2: mossa 'FORBICE'\n");
            break;
        case SASSO:
            printf("P2: mossa 'SASSO'\n");
            break;
        default:
            break;
        }
       // exit(0);
    }
    exit(0);
}

void J(int coda, int numpartite){
    int numpartitesvolte=0;
    msg messaggioGiudice;
    msg messaggioProcesso1;
    msg messaggioProcesso2;
    do{
        numpartitesvolte++;
        printf("G: inizio partita n. %d\n",numpartitesvolte);
        messaggioGiudice.mossa=100;
        messaggioGiudice.payload=REQUEST;
        messaggioGiudice.mtype=p1;
        if (msgsnd(coda, &messaggioGiudice, sizeof(msg)-sizeof(long), 0) == -1) {
            perror("msgsnd J 1");
            exit(1);
        }
        messaggioGiudice.mossa=100;
        messaggioGiudice.payload=REQUEST;
        messaggioGiudice.mtype=p2;
        if (msgsnd(coda, &messaggioGiudice, sizeof(msg)-sizeof(long), 0) == -1) {
            perror("msgsnd J 2");
            exit(1);
        }
        if (msgrcv(coda, &messaggioProcesso1, sizeof(msg) - sizeof(long), p1rec, 0) == -1) {
            perror("msgrcv J 1");
            exit(1);
        }
        if (msgrcv(coda, &messaggioProcesso2, sizeof(msg) - sizeof(long), p2rec, 0) == -1) {
            perror("msgrcv J 2");
            exit(1);
        }
        int mossaP1=messaggioProcesso1.mossa;
        int mossaP2=messaggioProcesso2.mossa;
      //  sleep(2);
        if(mossaP1==CARTA && mossaP2==FORBICE){
            printf("Vince P2 FORBICE batte CARTA\n");
        }
        if(mossaP1==CARTA && mossaP2==SASSO){
            printf("Vince P1 CARTA batte SASSO\n");
        }
        if(mossaP1==CARTA && mossaP2==CARTA){
            printf("PATTA CARTA & CARTA\n");
        }
        if(mossaP1==SASSO && mossaP2==FORBICE){
            printf("Vince P1 SASSO batte FORBICE\n");
        }
        if(mossaP1==SASSO && mossaP2==CARTA){
            printf("Vince P2 CARTA batte SASSO\n");
        }
        if(mossaP1==SASSO && mossaP2==SASSO){
            printf("PATTA SASSO & SASSO\n");
        }
        if(mossaP1==FORBICE && mossaP2==FORBICE){
            printf("PATTA FORBICE & FORBICE\n");
        }
        if(mossaP1==FORBICE && mossaP2==CARTA){
            printf("Vince P1 FORBICE batte CARTA\n");
        }
        if(mossaP1==FORBICE && mossaP2==SASSO){
            printf("Vince P2 SASSO batte FORBICE\n");
        }
    }while (numpartitesvolte!=numpartite);
   // printf("Invio la fine della partita\n");
    messaggioGiudice.mossa=100;
    messaggioGiudice.payload=EXIT;
    messaggioGiudice.mtype=p1;
    if (msgsnd(coda, &messaggioGiudice, sizeof(msg)-sizeof(long), 0) == -1) {
        perror("msgsnd J");
        exit(1);
    }

    messaggioGiudice.mossa=100;
    messaggioGiudice.payload=EXIT;
    messaggioGiudice.mtype=p2;
    if (msgsnd(coda, &messaggioGiudice, sizeof(msg)-sizeof(long), 0) == -1) {
        perror("msgsnd J");
        exit(1);
    }
    exit(0);
}

int main(int argc, char const *argv[]){
    int coda;
    key_t key=100;
    if(argc <= 1){
        perror("Formato: <numero-partite>");
    }
    if ((coda = msgget(IPC_PRIVATE, IPC_CREAT | 0600)) == -1) {
        perror("msgget");
        exit(1);
    }
    if(fork()==0) P1(coda);
    if(fork()==0) P2(coda);
    printf("STAMPO IL NUMERO %d\n",atoi(argv[1]));
    if(fork()==0) J(coda, atoi(argv[1]));
   // if(fork()==0) T();  

    wait(NULL);
    wait(NULL);
    wait(NULL);
    msgctl(coda, IPC_RMID, NULL);
    exit(0);
}

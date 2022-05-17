/*
    Realizzare un server (in C o in Java) che si metta in ascolto sul port 3333, 
    sul quale accetta richieste di connessione da un client.

    Sulla connessione stabilita, il server riceve una stringa, 
    terminata dal carattere '\n' (si supponga che basti una sola operazione di l
    ettura in ricezione da parte del server, per ricevere ciascuna stringa 
    inviata dal client).

    Il server quindi scrive la stringa ricevuta sullo standard output e, 
    chiusa la connessione, si rimette in attesa di eventuali 
    richieste di connessione. 
    Testare il server server_A usando telnet.
*/

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h> 
#include <string.h>

#define FPORT 3333
#define MAXBUF 1024


int main(int argc, char *argv[])
{
    int server_socket, connect_socket, retcode;
    struct sockaddr_in server_addr, client_addr; 
    char buffer[MAXBUF];

    printf("Server in ascolto su porta %d\n", FPORT);
    
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Errore apertura socketn\n");
        printf("errno: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = FPORT;

    if ((retcode = bind(server_socket, (struct sockaddr *) 
                        &server_addr, sizeof(server_addr))) == -1)
    {
        perror("Errore bind\n");
        printf("errno: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    if ((retcode = listen(server_socket, 1)) == -1)
    {
        perror("Errore listen\n");
        printf("errno: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    printf("Server ready (CTRL-C to quit)\n");

    socklen_t client_addr_len = sizeof(client_addr);
    while (1)
    {
        printf("Posso accettare connessioni\n");

        if ((connect_socket = accept(server_socket, (struct sockaddr *)
                                    &client_addr, &client_addr_len)) == -1)
        {
            perror("Errore accept\n");
            printf("errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        
        printf("\nClient %s connesso su socket/port %d/%u.\n", inet_ntoa(client_addr.sin_addr),
                                                               connect_socket, 
                                                               (client_addr.sin_port));

        if ((retcode = read(connect_socket, buffer, MAXBUF -1)) < 0)
        {
            perror("Errore read\n");
            printf("errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        
        fprintf(stdout, "%s", buffer);

    }
    close(server_socket);
    close(connect_socket);
    exit(EXIT_SUCCESS);

}


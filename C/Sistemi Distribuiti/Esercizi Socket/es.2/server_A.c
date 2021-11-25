/*
    Realizzare un server (in C o in Java) chiamato ​Server A ​che si metta in ascolto sul ​port
    7777 ​per ricevere una stringa ​str ​composta da una sequenza di lunghezza
    arbitraria di caratteri numerici da (0 a 9)​ ​e terminata dal carattere ​\n​. Il server dovrà
    quindi stampare il messaggio ricevuto sullo standard output. Testare il server usando
    telnet.
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

#define FPORT 7777
#define MAXLEN 1024

int main(int argc, char  *argv[])
{
    int server_socket, check_bind, check_listen, connected_socket, retcode;
    struct sockaddr_in server_addr, client_addr;
    int buffer[MAXLEN];
    
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Errore apertura socketn\n");
        printf("errno: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(FPORT);

    socklen_t server_addr_len = sizeof(server_addr);
    if ((check_bind = bind(server_socket, (struct sockaddr *) &server_addr, server_addr_len)) == -1)
    {
        perror("Errore bind\n");
        printf("errno: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    if ((check_listen = listen(server_socket, 1)) == -1)
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

        if ((connected_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_addr_len)) == -1)
        {
            perror("Errore accept\n");
            printf("errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }

        printf("\nClient %s connesso su socket/port %d/%u.\n", inet_ntoa(client_addr.sin_addr),
                                                               connected_socket, 
                                                               (client_addr.sin_port));


        if ((retcode = read(connected_socket, buffer, MAXLEN - 1)) == -1)
        {
            perror("Errore read\n");
            printf("errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        
        printf("%i", buffer);
        
    }
    close(server_socket);
    close(connected_socket);
}

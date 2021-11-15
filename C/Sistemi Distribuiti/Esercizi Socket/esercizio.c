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

int mkaddr(struct sockaddr_in * addr, const char * hostname_or_ip, short port)
{
    struct hostent * host;
    size_t nbytes;

    memset(addr,0,sizeof(*addr));    // si azzera la struct puntata da ·addr
    addr->sin_family = AF_INET;      // member ·sin_family is always ·AF_INET
    addr->sin_port = htons(port);    // ·port argument assumed in host order

    // query DNS, get ·hostent with host's IP
    if ((host = gethostbyname(hostname_or_ip)) == NULL) {
        herror("querying");
        return(-1);                 // process calling mkaddr() should test
    }
                                     // memcpy() copies byte-by-byte to
    memcpy(&(addr->sin_addr),        // socket's address (addr->sin_addr)
           host->h_addr_list[0],     // host's first (index 0) IP address
           nbytes = host->h_length); // host->h_length is address length
    return((int) nbytes);            // i.e. n. of bytes to be copied
}

typedef enum  
{
    NORMALE,
    END
} MESG_T;

typedef struct 
{
    MESG_T type;
    char nome[20];
    char corpo[100];
} MESSAGE;

MESSAGE msg;

int main(int argc, char *argv[])
{
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    int connect_socket;
    int retcode, buffer;

    if (argc != 3)
    {
        printf("USage: %s <ip_address> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((connect_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Errore apertura socket\n");
        exit(EXIT_FAILURE);
    }

    
    if (fork() == 0) //server
    {
        
        mkaddr(&server_addr, argv[1], argv[2]);
        
        if ((retcode = bind(connect_socket, (struct sockaddr *) &server_addr, sizeof(server_addr))) == -1)
        {
            perror("Errore bind\n");
            exit(EXIT_FAILURE);
        }

        if ((retcode = listen(connect_socket, 1)) == -1)
        {
            perror("Errore listen\n");
            exit(EXIT_FAILURE);
        }

        printf("\nServer Ready\n");

        client_addr_len = sizeof(client_addr);
        
        while ((connect_socket = accept(connect_socket, (struct sockaddr *) &client_addr, &client_addr_len)) != -1)
        {
            printf("Connection established with %s", inet_ntoa(client_addr.sin_addr));

            while (read(connect_socket, &msg, sizeof(MESSAGE)) < 0)
            {
                perror("Errore read\n");
                exit(EXIT_FAILURE);
            }
            printf("messaggio da %s: %s", msg.nome, msg.corpo);

        }
        

    }
    else //client
    {

    }
    

}

/*
	Realizzare un server che tiene traccia della disponibilità di 10 libri, che possono essere disponibili o in prestito;
	riceve delle richieste da parte dei client del tipo "titolo del libro"
	e risponde "Disponibile", "In prestito" o "Inesistente" a seconda del titolo richiesto.
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

#define MAXBUF 1024

#define SERVERPORT 3002
#define SERVERNAME "localhost"

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


int main(int argc, char *argv[])
{
    printf("\n");
    char** libreria;
    
    libreria[0] = "Amore e Odio";
    libreria[1] = "Il Principe Azzurro";
    libreria[2] = "Manuale Java";
    libreria[3] = "La Seconda Guerra Mondiale";
    libreria[4] = "La Prima Guerra Mondiale";
    libreria[5] = "Alice nel paese delle meraviglie";
    libreria[6] = "Manuale di cucina";
    libreria[7] = "Essere o non essere";
    libreria[8] = "Manuale C";
    libreria[9] = "Manuale di Programmazione Web";

    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    int server_socket, connect_socket, retcode, nw;
    char buffer[MAXBUF];
    int libro_found = 0;
    if (argc != 3)
    {
        printf("Usage: libreria.c <indirizzo Ip> <Port>\n");
        exit(EXIT_FAILURE);
    }
    

    if ( (server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Errore apertura socketn\n");
        exit(EXIT_FAILURE);
    }
    
    mkaddr(&server_addr, SERVERNAME, SERVERPORT);

    if ((retcode = bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1))
    {
        perror("Errore bind\n");
        exit(EXIT_FAILURE);
    }

    if ((retcode = listen(server_socket, 1)) == -1)
    {
        perror("Errore listen\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Server ready (CTRL-C to quit)\n");
    
    client_addr_len = sizeof(client_addr);
    while (1)
    {
        printf("Posso accettare connessioni\n");

        if ((connect_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_addr_len)) == -1)
        {
            perror("Errore accept\n");
            close(server_socket);
            exit(EXIT_FAILURE);
        }
        
        printf("\nClient %s connesso su socket/port %d/%u.\n", inet_ntoa(client_addr.sin_addr),
                                                               connect_socket, 
                                                               (client_addr.sin_port));

        while ((retcode = read(connect_socket, buffer, MAXBUF -1)) > 0 )
        {
            buffer[retcode] = '\0';

            if ((nw = write(connect_socket, buffer, ( strlen(buffer)+1))) < 0)
            {
                printf("Errore write\n");
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < sizeof(libreria); i++)
            {
                if (strcmp(buffer, libreria[i]) == 0)
                {
                    libro_found = 1;
                    printf("Libro Trovato!\n");
                }
            }
            if (libro_found == 0)
            {
                printf("Libro non trovato!\n");
            }
        }

        if (retcode == 0 || errno == EPIPE)
        {
            printf("Il client ha chiuso la connessione sulla socket:%d\n", connect_socket);
        }
        else
        {
            printf("sto leggendo dalla connessione\n");
        }

        close(connect_socket);
        
    }
    


    
}

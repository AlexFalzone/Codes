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

#define F_PORT 3333
#define F_IP 151.97.157.78
#define MAXBUF 1024

int mkaddr(struct sockaddr_in * addr, const char * hostname_or_ip, u_int16_t port)
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


int main(int argc, char  *argv[])
{
    int client_socket, retcode;
    char buffer[MAXBUF];
    struct sockaddr_in client_addr;

    if (argc != 3)
    {
        printf("Usage: <./a.out> <ip_address> <port>\n");
        return -1;
    }

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Errore apertura socketn\n");
        printf("errno: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    mkaddr(&client_addr, argv[1], F_PORT);

    socklen_t client_addr_len = sizeof(client_addr);
    if (connect(client_socket, (struct sockaddr *)&client_addr, &client_addr_len) == -1)
    {
        perror("Errore connect\n");
        printf("errno: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        if ((retcode = write(client_socket, buffer, strlen(buffer))) < 0)
        {
            perror("Errore write\n");
            printf("errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        
        if ((retcode = read(client_socket, buffer, MAXBUF)) != 0)
        {
            if (retcode == -1)
            {
                perror("\nleggendo dalla socket\n");
                exit(EXIT_FAILURE);
            }
        }
        write(STDOUT_FILENO, buffer, retcode);
    }
    
    close(client_socket);
    exit(EXIT_SUCCESS);
}

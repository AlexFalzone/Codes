#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>

#define IPPORT_FINGER 79
#define MAXBUF 1024*8

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

int main(int argc, char *argv[])
{
    struct sockaddr_in addr;
    char buffer[MAXBUF];
    int sock, retcode;
    u_int16_t fport;

    if (argc != 3 && argc != 4)
    {
        fprintf(stderr, "Usage: %s <server> <messagge> <port>\n", argv[0]);
        fprintf(stderr, "Usage: %s <directory.mit.edu> <messagge>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Errore apertura socket\n");
        exit(EXIT_FAILURE);
    }

    if (argc == 4)
    {
        fport = atoi(argv[3]);
    }
    else
    {
        fport = IPPORT_FINGER;
    }
    
    mkaddr(&addr, argv[1], fport);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("Errore apertura connessione\n");
        exit(EXIT_FAILURE);
    }
    
    sprintf(buffer,"%s\n", argv[2]);
    while (1)
    {
        if((write(sock, buffer, strlen(buffer))) == -1)
        {
            perror("Errore scrittura sul buffer\n");
            exit(EXIT_FAILURE);
        }

        if ((retcode = read(sock, buffer, MAXBUF)) != 0)
        {
            if (retcode == -1)
            {
                perror("\nleggendo dalla socket\n");
                exit(EXIT_FAILURE);
            }
        }
        write(STDOUT_FILENO, buffer, retcode);
    }
    
    fprintf(stderr, "\n>>>Exiting: server closed connection\n");

    close(sock);
    exit(EXIT_SUCCESS); 
}

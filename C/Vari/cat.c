#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *in;
    char buffer[BUFSIZ];

    if (argc >= 2)
    {
        if ( (in = fopen(argv[1], "r")) == NULL )
        {
            perror(argv[1]);
            exit(1);
        }
    }
    else
    {
        in = stdin;
    }
    
    while (fgets(buffer, BUFSIZ, in) != NULL)
    {
        printf("%s", buffer);
    }
    fclose(in);
}

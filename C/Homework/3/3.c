/*
    Homework n.3

    Usando la possibilita' di mappare file in memoria, creare un programma che
    possa manipolare un file arbitrariamente grande costituito da una sequenza
    di record lunghi N byte.
    La manipolazione consiste nel riordinare, tramite un algoritmo di ordinamento
    a scelta, i record considerando il contenuto dello stesso come chiave:
    ovvero, supponendo N=5, il record [4a a4 91 f0 01] precede [4a ff 10 01 a3].
    La sintassi da supportare e' la seguente:
     $ homework-3 <N> <pathname del file>

    E' possibile testare il programma sul file 'esempio.txt' prodotto dal seguente
    comando, utilizzando il parametro N=33:
     $ ( for I in `seq 1000`; do echo $I | md5sum | cut -d' ' -f1 ; done ) > esempio.txt

    Su tale file, l'output atteso e' il seguente:
     $ homework-3 33 esempio.txt
     $ head -n5 esempio.txt
        000b64c5d808b7ae98718d6a191325b7
        0116a06b764c420b8464f2068f2441c8
        015b269d0f41db606bd2c724fb66545a
        01b2f7c1a89cfe5fe8c89fa0771f0fde
        01cdb6561bfb2fa34e4f870c90589125
     $ tail -n5 esempio.txt
        ff7345a22bc3605271ba122677d31cae
        ff7f2c85af133d62c53b36a83edf0fd5
        ffbee273c7bb76bb2d279aa9f36a43c5
        ffbfc1313c9c855a32f98d7c4374aabd
        ffd7e3b3836978b43da5378055843c67
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

void scambia(int a, int b){
    int aux = a;
    a = b;
    b = aux;
}

int partition(int a[], int p, int r)
{
    int pivot=a[r];
    fprintf("p = %d", pivot);
    int i=p-1;
    for (int j = p; j < r; j++)
    {
        if(a[j]<=pivot)
        {
            i++;
            scambia(a[i],a[j]);
        }
    }
    scambia(a[i+1],a[r]);
    return i+1;
}

void quicksort(int a[],int sinistra, int destra)
{
    if(sinistra<destra)
    {
        int q=partition(a,sinistra,destra);
        quicksort(a,sinistra,q-1);
        quicksort(a,q+1,destra);
    }
}


int main(int argc, char const *argv[])
{
    struct stat sb;
    int size;
    long fd;
    char* map;

    if (argc < 3)
    {
        fprintf("Usage: %s <dimensione record>, <file>\n", argv[0]);
        exit(1);
    }
    
    if ( (fd = open(argv[2], O_RDWR)) == -1 )
    {
        perror(argv[2]);
        exit(1);
    }

    if (stat(fd, &sb) == -1)
    {
        perror("stat\n");
        exit(1);
    }
    
    if (!S_ISREG(sb.st_mode))
    {
        fprintf("%s non è un file\n", argv[2]);
        exit(1);
    }

    size = atoi(argv[1]);
    if (size <= 0)
    {
        fprintf("Dimensione %d non valida", size);
    }

    if ((map = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {
        perror("map");
        exit(1);
    }
    
    if (close(fd) == -1)
    {
        perror("close\n");
        exit(1);
    }
    
    int num = sb.st_size / size;
    quicksort(map, num - 1, size);

    printf("Record del file '%s' riordinati!\n", argv[2]);

    if (munmap(map, sb.st_size) == -1)
    {
        perror("unmap");
        exit(1);
    }
}

/*
    Homework n.2

    Estendere l'esempio 'move.c' visto a lezione per supportare i 2 casi speciali:
    - spostamento cross-filesystem: individuato tale caso, il file deve essere
      spostato utilizzando la strategia "copia & cancella";
    - spostamento di un link simbolico: individuato tale caso, il link simbolico
      deve essere ricreato a destinazione con lo stesso contenuto (ovvero il percorso
      che denota l'oggetto referenziato); notate come tale spostamento potrebbe
      rendere il nuovo link simbolico non effettivamente valido.

    La sintassi da supportare e' la seguente:
     $ homework-2 <pathname sorgente> <pathname destinazione>
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
  int source_file, dest_file,size;
  struct stat stat_file_source, stat_file_dest;
  char *dest_pathname;
  char buffer[BUFSIZ];
  
  if (argc < 3)
  {
    printf("Usage: <pathname sorgente>, <pathname destinazione>\n");
    exit(EXIT_FAILURE);
  }
  
  if (lstat(argv[1], &stat_file_source) == -1)
  {
    perror("Source stat error\n");
    exit(EXIT_FAILURE);
  }


  switch (stat_file_source.st_mode & S_IFMT)
  {
  case S_IFREG: //file regolare

    strncpy(buffer, argv[2], BUFSIZ);
    dest_pathname = dirname(buffer);
    if ( (stat(dest_pathname, &stat_file_dest)) == -1 )
    {
      perror("Dest stat error");
      exit(EXIT_FAILURE);
    }
    
    if (!S_ISDIR(stat_file_dest.st_mode))
    {
      perror("Non è una directory\n");
      exit(EXIT_FAILURE);
    }
    
    if (stat_file_dest.st_dev == stat_file_source.st_dev)
    {
      printf("Stesso filesystem\n");

      if (link(argv[1], argv[2]) == -1) 
      {
        perror(argv[2]);
        exit(1);
      }
    }
    else
    {
      printf("Diverso filesystem\n");

      if ( (source_file = open(argv[1], O_RDONLY)) == -1 )
      {
        perror(argv[1]);
        exit(EXIT_FAILURE);
      }

      if ( (dest_file = open(argv[2], O_WRONLY|O_TRUNC|O_CREAT, stat_file_source.st_mode & 0777)) == -1 )
      {
        perror(argv[2]);
        exit(EXIT_FAILURE);
      }

      do
      {
        if ((size = read(source_file, buffer, BUFSIZ)) == -1)
        {
          perror("read error\n");
          exit(EXIT_FAILURE);
        }

        if (write(dest_file, buffer, size) == -1)
        {
          perror("write error\n");
          exit(EXIT_FAILURE);
        }
      } while (size == BUFSIZ);
    }
    close(source_file);
    close(dest_file);
    break;

  case S_IFLNK: //link simbolico
    

    break;

  default:
    printf("Errore, formato non supportato\n");
    break;
  }
  
  if (unlink(argv[1]) == -1)
  {
    perror("unlink error");
    exit(EXIT_FAILURE);
  }
}

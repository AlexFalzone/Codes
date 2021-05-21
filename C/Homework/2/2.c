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

int main(int argc, char const *argv[])
{
  struct stat src_buff, dst_buff;
  char buffer[BUFSIZ];
  int src_different_filesystem, dst_different_filesystem, size;
  char* dst_directory;


  if (argc != 3)
  {
    printf("utilizzo: %s <file-esistente> <nuovo-nome-e-o-posizione>\n", argv[0]);
    exit(1);
  }

  if (lstat(argv[1], &src_buff) == -1)
  {
    perror(argv[1]);
    exit(1);
  }
  
  
  switch (src_buff.st_mode & S_IFMT)
  {
  case S_IFREG:
    strncpy(buffer, argv[2], BUFSIZ);
    dst_directory = dirname(buffer);
    if ( stat(dst_directory, &dst_buff) == -1 )
    {
      perror(dst_directory);
      exit(1);
    }
    
    if (!S_ISDIR(dst_buff.st_mode))
    {
      printf("%s non è una directory\n", dst_directory);
      exit(1);
    }
    

    //nel caso il filesystem sia uguale
    if (src_buff.st_dev == dst_buff.st_dev)
    {
      printf("Stesso Filesystem\n");

      if (link(argv[1], argv[2]) == -1)
      {
        perror(argv[2]);
        exit(1);
      }
    }
    else
    {
      printf("Diverso Filesystem\n");
      if ( (src_different_filesystem = open(argv[1], O_RDONLY)) == -1 )
      {
        perror(argv[1]);
        exit(1);
      }
        
       if ( (dst_different_filesystem = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, (src_buff.st_mode & 0777))) == -1 )
      {
        perror(argv[2]);
        exit(1);
      }
        
      do
      {
        if ( (size = read(src_different_filesystem, buffer, BUFSIZ)) == -1)
        {
          perror(argv[1]);
          exit(1);
        }

        if (write(dst_different_filesystem, buffer, size) == -1)
        {
          perror(argv[2]);
          exit(1);
        }
      } while (size == BUFSIZ);
      close(src_different_filesystem);
      close(dst_different_filesystem);
    }
    break;

  case S_IFLNK:

    break;

  default:
    printf("Formato non supportato!");
    break;
  }

  if (unlink(argv[1]) == -1) {
      perror(argv[1]);
      exit(1);
  }


}

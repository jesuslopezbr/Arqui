#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

void main(int argc, char *argv[]){
  //preguntar directorios relativos ./ con que nombre lo ponemos y como hacer que el programa espere la ejecucion del prgrama hijo

  pid_t procA,procB;
  procA = fork();

  if(procA < 0)
  {
    fprintf(stderr, "Fork1 Failed");
    exit(-1);
  }
  if(procA == 0)
  {

    /*char* nombre_texto = NULL;
    printf("Introduzca el path del archivo de texto: ");
    scanf("%s\n", nombre_texto);*/
    char * args[] = {"cat", /*nombre_texto*/"/home/matthew/Documents/Arqui/Practica1/main.c", NULL};
    int ret = execv("/bin/cat", args);

    if(ret == -1)
    {
      perror("execvp");
    }

  }
  else
  {

    procB = fork();

    if(procB < 0)
    {
      fprintf(stderr, "Fork2 Failed");
      exit(-1);
    }
    if(procB == 0)
    {
      /*char* nombre_pro;
      printf("Introduzca el nombre del programa: ");
      scanf("%s\n", nombre_pro);*/

      int ret = execlp("/home/matthew/Documents/Arqui/Practica1/prog1", /*nombre_pro*/"prog1", NULL);

      if(ret == -1)
      {
        perror("execl");
      }

    }
    else
    {
      wait(NULL);
      printf("Proceso hijo completado");
      exit(0);
    }

  }
}

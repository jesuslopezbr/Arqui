#include <sys/types.h>
#include <unistd.h>

void main(int argc, char *argv[]){
  pid_t procA,procB;

  char* s = NULL;
  printf("Introduzca el nombre del programa: ");
  scanf("%s\n", &s);

  procA = fork();

  if(procA < 0)
  {
    fprintf(stderr, "Fork1 Failed");
    exit(-1);
  }
  if(procA == 0)
  {
    int ret = execvp("cat", "cat", argv[0], NULL);

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
      int ret = execl(argv[0], s, NULL);

      if(ret == -1)
      {
        perror("execvp");
      }

    }
    else
    {
      wait(NULL);
      printf("Proceso hijo completado");
      exit(0;
    }

  }
}

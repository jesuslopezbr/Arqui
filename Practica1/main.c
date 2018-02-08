#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void usage(int argc){
  if(argc != 3){
    fprintf(stderr, "Usage: <path_texto> <path_programa>\n" );
    exit(-1);
  }
}

void main(int argc, char *argv[]){

  usage(argc);

  pid_t procA,procB;


  procA = fork();

  if(procA < 0)
  {
    fprintf(stderr, "Fork1 Failed");
    exit(-1);
  }
  if(procA == 0)
  {

    char * args[] = {"cat",argv[1], NULL};
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
      sleep(1);
      int ret = execlp(argv[2], argv[2], NULL);

      if(ret == -1)
      {
        perror("execl");
      }

    }
    else
    {
      wait(NULL);
      wait(NULL);
      printf("\nProcesos hijos completados\n");
      exit(0);
    }

  }
}

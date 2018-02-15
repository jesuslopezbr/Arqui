#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){

  pid_t pid_editor;

  pid_editor = fork();

  if(pid_editor < 0)
  {
    fprintf(stderr, "Editor_Fork Failed\n");
    exit(-1);
  }

  if(pid_editor == 0)
  {
    //HIJO
    int ret;

    ret = execl("/usr/bin/gedit", "gedit", NULL);

    if (ret == -1)
    {
      perror("execl");
    }
  }
  else
  {
    //PADRE
    wait(NULL);
    printf("\nHijo Completo\n");
    exit(0);
  }

}

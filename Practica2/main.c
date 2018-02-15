#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 200

int main(int argc, char *argv[])
{
    int n, fd[2];
    char line1[MAXLINE];
    char line2[MAXLINE];
    pid_t pid_backup;

    if (pipe(fd) < 0)
    {
      fprintf(stderr, "\nError in pipe creation\n\n");
      exit(-1);
    }
    pid_backup = fork();

    if(pid_backup < 0)
    {
      fprintf(stderr, "\nEditor_Fork Failed\n\n");
      exit(-1);
    }

    if(pid_backup == 0)
    {
      //HIJO
      close(fd[1]);
      n = read(fd[0], line1, MAXLINE);
      if(n < 0)
      {
        fprintf(stderr, "\nEditor_Fork Failed\n\n");
        exit(-1);
      }

      write(STDOUT_FILENO, line1, n);

      FILE* f_bkp = fopen("users.bkp", "wt");
      fputs(line1, f_bkp);
      fclose(f_bkp);
    }
    else
    {
      //PADRE
      FILE* fb = fopen("users.data", "r");

      if(fb != NULL)
      {
          if(fgets(line2, MAXLINE, fb) != NULL)
          {
            puts(line2);
          }
          fclose(fb);
      }
      else
      {
          perror("Error opening file");
      }

      close(fd[0]);
      write(fd[1], line2, MAXLINE);
    }
    exit(0);
}

void editor()
{

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

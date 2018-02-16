#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#define MAXLINE 14

int go = 0;

void usage(int argc){
  if(argc != 2){
    fprintf(stderr, "Usage: <monitoring_time_interval>\n" );
    exit(-1);
  }
}

void menu(){
  printf("\nExtended Operating System Functions: \n");
  printf("[0] Exit - Ordered termination\n");
  printf("[1] Edit user data\n");
  printf("[2] Monitor file system activation\n");
  printf("[3] Clock activation\n");
  printf("[4] Clock stop\n");
  printf("[5] Process monitor activation\n");
  printf("[6] Automatic back up activation\n");
  printf("[7] Keep alive reporting\n");
  printf("\n ExOS> ");
}

void sigint_handler(int signo){
  go = 1;
}

void clock_activation(){
  int time_type;
  pid_t app;

  do
  {
    while(go == 0);

    app = fork();

    if(time_type == 0)
    {
      if(app == 0)
        execlp("/bin/date", "date", NULL);
      time_type = 1;
    }
    else
    {
      if(app == 0)
        execlp("/bin/date", "date", "-u", NULL);
      time_type = 0;
    }

    go = 0;

  }while (1);
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

    }
}

void backup()
{

      int n, fd[2];
      //char *line1 = NULL;
      char *line2 = NULL;
      char line1[MAXLINE];
      pid_t pid_backup;

      if (pipe(fd) < 0)
      {
        fprintf(stderr, "\nFather: Error in pipe creation\n\n");
        exit(-1);
      }
      pid_backup = fork();

      if(pid_backup < 0)
      {
        fprintf(stderr, "\nBackup_Fork Failed\n\n");
        exit(-1);
      }

      if(pid_backup == 0)
      {
        //HIJO
        close(fd[1]);
        //line1 = malloc(sizeof(688888888));

        //if(line1 != NULL)
        //{
          n = read(fd[0], line1, MAXLINE/*sizeof(688888888)*/);
          if(n < 0)
          {
            fprintf(stderr, "\nSon: Read_Pipe Failed\n\n");
            exit(-1);
          }
        //}

        //write(STDOUT_FILENO, line1, n);

        FILE* f_bkp = fopen("users.bkp", "wt");
        fputs(line1, f_bkp);
        fclose(f_bkp);
        exit(0);
        //free(line1);
      }
      else
      {
        //PADRE
        FILE* fb = fopen("users.data", "rb");

        if(fb != NULL)
        {
            /*if(fgets(line2, MAXLINE, fb) != NULL)
            {
              puts(line2);
            }*/
            fseek (fb, 0, SEEK_END);
            int length = ftell (fb);
            if(length < 0)
            {
              fprintf(stderr, "\nFather: F_Tell Failed\n\n");
              exit(-1);
            }
            fseek (fb, 0, SEEK_SET);
            line2 = malloc (length);
            if(line2 != NULL)
            {
              int fr = fread (line2, 1, length, fb);
              if(fr < 0)
              {
                fprintf(stderr, "\nFather: F_Read Failed\n\n");
                exit(-1);
              }
            }
            fclose (fb);
        }
        else
        {
            perror("\nFather: Error opening file\n\n");
        }

        close(fd[0]);
        write(fd[1], line2, MAXLINE);
        free(line2);
      }
}

int main(int argc, char *argv[]){

  usage(argc);

 if(signal(SIGINT, sigint_handler) == SIG_ERR)
    printf("\nError Catching signal\n");

  pid_t pid_date;
  int choice;
  int exit = 1;
  int result = 0;

  do
  {
    do
    {
      menu();

      result = scanf("%d", &choice);
      if(result == 0)
        while(fgetc(stdin) != '\n');

    }while(result <= 0);

    switch (choice)
    {
      case 0:
        printf("Exit\n");
        exit = 0;
        if(pid_date != 0){
          kill(pid_date, SIGKILL);
        }
        wait(NULL);
        break;
      case 1:
        printf("Editing user data\n");
        editor();
        break;
      case 2:
        printf("Monitoring file system\n");
        break;
      case 3:
        printf("Clock activated\n");
        pid_date = fork();
        if(pid_date == 0)
          clock_activation();
        break;
      case 4:
        printf("Clocks stopped\n");
        kill(pid_date, SIGKILL);
        break;
      case 5:
        printf("Process monitoring\n");
        break;
      case 6:
        printf("Backing up\n");
        backup();
        break;
      case 7:
        printf("Checking live processes\n");
        break;
      default:
        printf("Not valid\n");
        choice = 7;
        break;
    }
  }while(exit == 1);
}

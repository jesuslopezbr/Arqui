#include <stdio.h>  //Estandar input outut(printf, scanf y fprintf)
#include <stdlib.h> //Estandar library(exit y malloc)
#include <sys/types.h> //Para las funciones fork, open y wait, y el tipo pid_t
#include <sys/stat.h>  //Para open
#include <sys/wait.h>	//Para wait
#include <fcntl.h>  //Para open
#include <unistd.h> //Para fork,close, execl, dup2 y sleep
#include <string.h>  //Para la funcion strerror
#include <errno.h>  //Para la variable errno
#include <signal.h>

#define MAX_PIPE_SIZE 65536

int go = 0;

void usage(int argc){
  if(argc != 2){
    fprintf(stderr, "\nUsage: <monitoring_time_interval>\n" );
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
      fprintf(stderr, "\nEditor_Fork Failed\n");
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
      printf("\nusers.data: EDITADO\n");

    }
}

void backup()
{

      int n, fd[2];
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
        char *line1 = (char *)malloc(MAX_PIPE_SIZE);
        close(fd[1]);

        n = read(fd[0], line1, MAX_PIPE_SIZE);
        if(n < 0)
        {
          fprintf(stderr, "\nSon: Read_Pipe Failed\n\n");
          exit(-1);
        }

        FILE* f_bkp = fopen(".users.bkp", "w");
        fputs(line1, f_bkp);
        fclose(f_bkp);
        free(line1);
        exit(0);
      }
      else
      {
        //PADRE
        char *line2 = NULL;
        int length;
        FILE* fb = fopen("users.data", "r");

        if(fb != NULL)
        {
            fseek (fb, 0, SEEK_END);
            length = ftell (fb);
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

            close(fd[0]);
            write(fd[1], line2, length);
            close(fd[1]);
            free(line2);

            wait(NULL);
            printf("\nBackup Hecho\n");
        }
        else
        {
            perror("\nFather: Error opening file\n\n");
        }
      }
}

void proc_monitor(int n)
{
  int ret;
  int fd;

  while(1)
  {
    fd = open("process.log",O_WRONLY|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR);
    if(fd == -1)
    {
      printf("%s",strerror(errno));
    }
    //Hijo ejecuta ps y exec
    //Redireccionar la salida estandar al fichero abierto
	  dup2(fd,1); //Para que en vez de imprimir por pantalla, escriba en el fichero
    ret = execl("/bin/ps","ps","r",NULL);
    close(fd);  //Cerramos el fichero en el hijo


    if(ret < 0)
    {
  	  perror("execl");
    }
    sleep(n);
  }
}

int main(int argc, char *argv[]){

  usage(argc);

  if(signal(SIGINT, sigint_handler) == SIG_ERR)
  {
    printf("\nError Catching signal\n");
  }

  pid_t pid_date, pid_proc;
  int choice;
  int n;
  int exit_p = 1;
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
        printf("\nExit\n\n");
        exit_p = 0;
        if(pid_date != 0){
          kill(pid_date, SIGKILL);
        }
        wait(NULL);
        break;
      case 1:
        printf("\nEditing user data\n");
        editor();
        break;
      case 2:
        printf("\nMonitoring file system\n");
        break;
      case 3:
        printf("\nClock activated\n");
        pid_date = fork();
        if(pid_date == 0)
          clock_activation();
        break;
      case 4:
        printf("\nClocks stopped\n");
        kill(pid_date, SIGKILL);
        break;
      case 5:
        printf("\nProcess monitoring\n");
        n = atoi(argv[1]);

        if((pid_proc = fork()) < 0)
        {
          fprintf(stderr, "\nProc_Monitor_Fork Failed\n");
          exit(-1);
        }
        if(pid_proc == 0)
        {
          proc_monitor(n);
        }
        else
        {
          printf("\nprocess.log: EDITADO\n");
        }

        break;
      case 6:
        printf("\nBacking up\n");
        backup();
        break;
      case 7:
        printf("\nChecking live processes\n");
        break;
      default:
        printf("\nNot valid\n");
        choice = 7;
        break;
    }
  }while(exit_p == 1);
}

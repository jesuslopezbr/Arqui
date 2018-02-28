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
  go = 1;//Si recibe señal cambia variable para imprimir hora
}

/*Si recibe señal, crea nieto y imprime UTC o CET dependiendo
de time_type*/
void clock_activation(){
  int time_type = 0, ret = 0;
  pid_t pid_time;

    do{
      go = 0;

      while(go == 0);
    pid_time = fork();

    if(time_type == 0){
      if(pid_time == 0)
        ret = execlp("/bin/date", "date",NULL);
      if (ret == -1)
        perror("execl");
      time_type = 1;
    }else{
      if(pid_time == 0)
        ret = execlp("/bin/date", "date","-u",NULL);
      if (ret == -1)
        perror("execl");
      time_type = 0;
    }
  }while (1);
}

void editor()
{
  int ret;

  ret = execl("/usr/bin/gedit", "gedit", NULL);

  if (ret == -1)
    perror("execl");

  exit(0);
}

void child_bkp(int fd[2]){
  //HIJO
  int n;
  char line1;
  FILE* f_bkp = fopen(".users.bkp", "w");
  close(fd[1]);

    while((n = read(fd[0],&line1, sizeof(char))) != 0){

      fwrite(&line1, sizeof(char), 1, f_bkp);
      if(n < 0)
      {
        fprintf(stderr, "\nSon: Read_Pipe Failed\n\n");
        exit(-1);
      }
    }
  fclose(f_bkp);
  close(fd[0]);
  printf("Closed\n");
  exit(0);
}

void father_bkp(int fd[2]){
  //PADRE
  char *line2 = NULL;
  FILE* fb = fopen("users.data", "rb");

  if(fb != NULL)
  {
    fseek (fb, 0, SEEK_END);
    int length = ftell (fb);
    printf("This is the length %d\n", length);
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
  }
  else
    perror("\nFather: Error opening file\n\n");
}

void file_logger(){

  int log;
  int ret;
  log = open("filesys.log", O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
  if(log == -1)
    perror("\nError creating file\n");
  dup2(log,1);
  ret = execl("/bin/ls","ls","-a",NULL);
  close(log);
  if(ret < 0)
    perror("execl");

  exit(0);
}

void proc_monitor(int n)
{
  int ret;
  int fd;
  pid_t pid_ps;

  while(1)
  {
    pid_ps = fork();
    if(pid_ps == 0){
      fd = open("process.log",O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
      if(fd == -1)
      {
        printf("%s",strerror(errno));
      }
      //Hijo ejecuta ps y exec
      //Redireccionar la salida estandar al fichero abierto
  	  dup2(fd,1);//Para que en vez de imprimir por pantalla, escriba en el fichero
      close(fd);  //Cerramos el fichero en el hijo
      ret = execl("/bin/ps","ps","r",NULL);
      if(ret < 0)
      {
    	  perror("execl");
      }
    }
    else
    sleep(n);
  }
}

int main(int argc, char *argv[]){

  usage(argc);

 if(signal(SIGINT, sigint_handler) == SIG_ERR)
    printf("\nError Catching signal\n");

  pid_t pid_date[50], pid_file, pid_backup, pid_editor, pid_proc;
  int choice, ex = 1,result = 0, i = 0, j = 0, n;
  int fd[2], status;
  int monitor_stat = 0, file_stat = 0, editor_stat = 0, backup_stat = 0;
  pid_t check;

  do{
    do{
      menu();

      result = scanf("%d", &choice);
      if(result == 0)
        while(fgetc(stdin) != '\n');

    }while(result <= 0);

    switch (choice) {
      case 0:
        ex = 0;
        i--;
        for(;i>=0;i--){
          kill(pid_date[i],SIGKILL);
          printf("%d reporting: Terminating\n", pid_date[i]);
        }
        if(file_stat == 1){
          check = waitpid(pid_file, &status, WNOHANG);
          if(check == 0){
            kill(pid_file,SIGKILL);
            printf("%d reporting: Terminating\n", pid_file);
          }
        }
        if(editor_stat == 1){
          check = waitpid(pid_editor, &status, WNOHANG);
          if(check == 0){
            kill(pid_editor,SIGKILL);
            printf("%d reporting: Terminating\n", pid_editor);
          }
        }
        if(backup_stat == 1){
          check = waitpid(pid_backup, &status, WNOHANG);
          if(check == 0){
            kill(pid_backup,SIGKILL);
            printf("%d reporting: Terminating\n", pid_backup);
          }
        }
        if(monitor_stat == 1){
          check = waitpid(pid_proc, &status, WNOHANG);
          if(check == 0){
            kill(pid_proc,SIGKILL);
            printf("%d reporting: Terminating\n", pid_proc);
          }
        }
        printf("Main process reporting: Terminating\n");
        break;
      case 1:
        printf("\nEditing user data\n");
        pid_editor = fork();
        editor_stat = 1;
        if(pid_editor < 0)
        {
          fprintf(stderr, "\nEditor_Fork Failed\n");
          exit(-1);
        }

        if(pid_editor == 0)
          editor();

        break;
      case 2:
        printf("\nMonitoring file system\n");
        pid_file = fork();
        file_stat = 1;
        if(pid_file < 0)
        {
          fprintf(stderr, "\nFile_Fork Failed\n");
          exit(-1);
        }
        if(pid_file == 0)
          file_logger();

        break;
      case 3:

        if(i<0)
          i=0;
        pid_date[i] = fork();
        if(pid_date[i] < 0)
        {
          fprintf(stderr, "\nDate_Fork Failed\n");
          exit(-1);
        }
        if(pid_date[i] == 0)
          clock_activation();
        else{
          #ifdef DEBUG
            if(pid_date[i]!= 0){
              printf("%d. ", i+1);
              printf("Process %d created\n", pid_date[i]);
            }
          #endif
          printf("\nClock number %d activated\n", i+1);

          i++;
        }
        break;
      case 4:
        i--;
        j = i;
        for(;i>=0;i--){
          #ifdef DEBUG
            printf("%d. ", i+1);
            printf("Closing process: %d\n", pid_date[i]);
          #endif
          kill(pid_date[i],SIGKILL);
        }
        printf("\n%d Clocks stopped\n", j+1);
        i=-1;
        break;
      case 5:
        if(monitor_stat == 0){
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
          }else{
            monitor_stat = 1;
          }
          if(monitor_stat == 1)
            printf("\nProcess monitor already activated\n");
        }
        break;
      case 6:
        printf("\nBacking up\n");

        if (pipe(fd) < 0)
        {
          fprintf(stderr, "\nFather: Error in pipe creation\n\n");
          exit(-1);
        }
        pid_backup = fork();
        backup_stat = 1;

        if(pid_backup < 0)
        {
          fprintf(stderr, "\nBackup_Fork Failed\n\n");
          exit(-1);
        }

        if(pid_backup == 0)
          child_bkp(fd);
        else
          father_bkp(fd);
        break;
      case 7:
        printf("\nChecking live processes...\n");
        result = 0;
        j=i;

        for(; j > 0; j--){
          printf("%d reporting: Alive\n", pid_date[j-1]);
          result = 1;
        }
        if(file_stat == 1){
          check = waitpid(pid_file, &status, WNOHANG);
          if(check == 0 && pid_file != 0){
            printf("%d reporting: Alive\n", pid_file);
            result += 1;
          }
        }
        if(editor_stat == 1){
          check = waitpid(pid_editor, &status, WNOHANG);
          if(check == 0 && pid_editor != 0){
            printf("%d reporting: Alive\n", pid_editor);
            result += 1;
          }
        }
        if(backup_stat == 1){
          check = waitpid(pid_backup, &status, WNOHANG);
          if(check == 0 && pid_backup != 0){
            printf("%d reporting: Alive\n", pid_backup);
            result += 1;
          }
        }
        if(monitor_stat == 1){
          check = waitpid(pid_proc, &status, WNOHANG);
          if(check == 0 && pid_proc != 0){
            printf("%d reporting: Alive\n", pid_proc);
            result += 1;
          }
        }
        if(result == 0)
          printf("No process running\n");


        break;
      default:
        printf("Not valid\n");
        choice = 7;
        break;
    }
  }while(ex == 1);
}

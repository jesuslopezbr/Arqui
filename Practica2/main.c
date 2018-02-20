#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>

#define MAXLINE 14
#define MAX_PIPE_SIZE 65536

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
  int time_type, ret;
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

//HIJO que recive del pipe y escribe a archivo .users.bkp
void child_bkp(int fd[2])
{
  int n;
    /*Alternativa a preguntar, recibir de pipe
    caracter a caracter y escribir en .users.bkp*/
    char *line1 = (char *)malloc(MAX_PIPE_SIZE);
    close(fd[1]);

    n = read(fd[0], line1, MAX_PIPE_SIZE);
    if(n < 0)
    {
      fprintf(stderr, "\nSon: Read_Pipe Failed\n\n");
      exit(-1);
    }
    #ifdef DEBUG
      printf("Child reading from pipe: \n%s\n", line1);
    #endif
    FILE* f_bkp = fopen(".users.bkp", "w");
    fputs(line1, f_bkp);
    fclose(f_bkp);
    free(line1);
    exit(0);
}

//PADRE que lee archvo users.data y pasa a HIJO por pipe
void father_bkp(int fd[2]){
  char *line2 = NULL;
  int length;
  FILE* fb = fopen("users.data", "r");

  if(fb != NULL)
  {
      /*Alternativa a preguntar, leer y mandar a pipe
      caracter a caracter*/
      fseek (fb, 0, SEEK_END);//Buscar longitud archivo
      length = ftell (fb);
      if(length < 0)
      {
        fprintf(stderr, "\nFather: F_Tell Failed\n\n");
        exit(-1);
      }
      fseek (fb, 0, SEEK_SET);//Poner lectura desde el principio
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
      #ifdef DEBUG
        printf("Father writing to pipe: \n%s\n", line2);
      #endif
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

void file_logger(){
  //Alternativa?
  DIR *d;
  struct dirent *dir ;
  FILE *log;
  log = fopen("filesys.log", "w");

  d = opendir("./");
  if(d != NULL){
    while((dir = readdir(d)))
      fprintf(log, "%s\n", dir -> d_name);
    closedir(d);
    fclose(log);
    exit(0);
  }
}

int main(int argc, char *argv[]){

  usage(argc);

 if(signal(SIGINT, sigint_handler) == SIG_ERR)
    printf("\nError Catching signal\n");

  pid_t pid_date[50], pid_file, pid_backup, pid_editor, pid_proc;
  int choice, ex = 1,result = 0, i = 0, j = 0;
  int fd[2], status;
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
        check = waitpid(pid_file, &status, WNOHANG);
      //  if(check == -1)
      //    fprintf(stderr, "\nError checking %d status\n\n", pid_file);
        if(check == 0){
          kill(pid_file,SIGKILL);
          printf("%d reporting: Terminating\n", pid_file);
        }
        check = waitpid(pid_editor, &status, WNOHANG);
        //if(check == -1)
        //  fprintf(stderr, "\nError checking %d status\n\n", pid_editor);
        if(check == 0){
          kill(pid_editor,SIGKILL);
          printf("%d reporting: Terminating\n", pid_editor);
        }
        check = waitpid(pid_backup, &status, WNOHANG);
        //if(check == -1)
        //  fprintf(stderr, "\nError checking %d status\n\n", pid_backup);
        if(check == 0){
          kill(pid_backup,SIGKILL);
          printf("%d reporting: Terminating\n", pid_backup);
        }

        check = waitpid(pid_proc, &status, WNOHANG);
        //if(check == -1)
        //  fprintf(stderr, "\nError checking %d status\n\n", pid_proc);
        /*if(check == 0){
          kill(pid_proc,SIGKILL);
          printf("%d reporting: Terminating\n", pid_proc);
        }*/


        printf("Main process reporting: Terminating\n");
        break;
      case 1:
        printf("\nEditing user data\n");
        pid_editor = fork();

        if(pid_editor < 0)
        {
          fprintf(stderr, "\nEditor_Fork Failed\n");
          exit(-1);
        }

        if(pid_editor == 0)
          editor();
        /*else
          {
            wait(NULL);
            printf("\nusers.data: EDITADO\n");
          }*/
        break;
      case 2:
        printf("\nMonitoring file system\n");
        pid_file = fork();
        if(pid_file < 0)
        {
          fprintf(stderr, "\nFile_Fork Failed\n");
          exit(-1);
        }
        if(pid_file == 0)
          file_logger();
        /*else{
          wait(NULL);
          printf("\nFile logged\n");
        }*/
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
        for(;i>=0;i--){
          #ifdef DEBUG
            printf("%d. ", i);
            printf("Closing process: %d\n", pid_date[i]);
          #endif
          kill(pid_date[i],SIGKILL);
        }
        printf("\nClocks stopped\n");
        i=-1;
        break;
      case 5:
        printf("\nProcess monitoring\n");
        break;
      case 6:
        printf("\nBacking up\n");

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

        check = waitpid(pid_file, &status, WNOHANG);
        if(check == 0 && pid_file != 0){
          printf("%d reporting: Alive\n", pid_file);
          result += 1;
        }
        check = waitpid(pid_editor, &status, WNOHANG);
        if(check == 0 && pid_editor != 0){
          printf("%d reporting: Alive\n", pid_editor);
          result += 1;
        }
        check = waitpid(pid_backup, &status, WNOHANG);
        if(check == 0 && pid_backup != 0){
          printf("%d reporting: Alive\n", pid_backup);
          result += 1;
        }
      /*  check = waitpid(pid_proc, &status, WNOHANG);
        if(check == 0 && pid_proc != 0){
          printf("%d reporting: Alive\n", pid_proc);
          result += 1;
        }*/
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

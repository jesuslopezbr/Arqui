#include <stdio.h>  //Estandar input outut(printf, scanf y fprintf)
#include <stdlib.h> //Estandar library(exit y malloc)
#include <sys/types.h> //Para las funciones fork, open y wait, y el tipo pid_t
#include <sys/stat.h>  //Para open()
#include <sys/wait.h>	//Para wait()
#include <fcntl.h>  //Para open
#include <unistd.h> //Para fork,close, execl, dup2 y sleep
#include <string.h>  //Para la funcion strerror
#include <errno.h>  //Para la variable errno
#include <signal.h> //Para manejar señales


int go = 0; //Variable global para controlar la señal CTRL-C

//Uso para la ejecución
void usage(int argc){
  if(argc != 2){
    fprintf(stderr, "\nUsage: <monitoring_time_interval>\n" );
    exit(-1);
  }
}

//Opciones
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

//Manejador de señales
void sigint_handler(int signo){
  go = 1; //Si recibe señal cambia variable para imprimir hora
}

//Si recibe señal, crea nieto e imprime UTC o CET dependiendo de time_type
void clock_activation(){
  int time_type = 0, ret = 0;
  pid_t pid_time;

  do{
      go = 0;

      while(go == 0);
    pid_time = fork(); //Creación del nieto

    if(time_type == 0){
      if(pid_time == 0)
        ret = execlp("/bin/date", "date", NULL); //Imprime la fecha CET
      if (ret == -1)
        perror("execl");
      time_type = 1;
    }else{
      if(pid_time == 0)
        ret = execlp("/bin/date", "date", "-u", NULL); //Imprime la fecha UTC
      if (ret == -1)
        perror("execl");
      time_type = 0;
    }
  }while (1);
}

//Editor -> Creamos el archivo "users.data"
void editor()
{
  int ret;

  ret = execl("/usr/bin/gedit", "gedit", NULL); //Abre el editor gedit

  if (ret == -1)
    perror("execl");

  exit(0);
}

//Backup
void child_bkp(int fd[2]){ //Hijo

  int n;
  char line1;
  FILE* f_bkp = fopen(".users.bkp", "w"); //Creamos el archivo oculto para escribir
  close(fd[1]); //Cerramos el descriptor de fichero de escritura

    while((n = read(fd[0], &line1, sizeof(char))) != 0){ //Leemos caracter a caracter

      fwrite(&line1, sizeof(char), 1, f_bkp); //Escribimos en .users.bkp caracter a caracter
      if(n < 0)
      {
        fprintf(stderr, "\nSon: Read_Pipe Failed\n\n");
        exit(-1);
      }
    }
  fclose(f_bkp); //Cerramos el fichero
  close(fd[0]); //Cerramos el descriptor de fichero de lectura
  exit(0);
}

void father_bkp(int fd[2]){ //Padre

  char *line2 = NULL;
  FILE* fb = fopen("users.data", "rb"); //Abrimos el archivo para leer

  if(fb != NULL)
  {
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
      int fr = fread (line2, 1, length, fb); //Copiamos de principio a fin el archivo users.data en line2
      if(fr < 0)
      {
        fprintf(stderr, "\nFather: F_Read Failed\n\n");
        exit(-1);
      }
    }
    fclose (fb); //Cerramos el fichero

    close(fd[0]); //Cerramos el descriptor de fichero de lectura
    write(fd[1], line2, length); //Escribimos en el pipe -> line2
    close(fd[1]); //Cerramos el descriptor de fichero de escritura
    free(line2); //Liberamos memoria dinámica
  }
  else
    perror("\nFather: Error opening file\n\n");
}

//Monitor sistema de ficheros
void file_logger(){

  int log;
  int ret;
  log = open("filesys.log", O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR); //Creamos el archivo
  if(log == -1)
    perror("\nError creating file\n");
  dup2(log,1); //Redirigimos la salida del comando "ls" al archivo "filesys.log"
  ret = execl("/bin/ls","ls","-a",NULL); //"-a" para mostrar todos los archivos, ocultos incluidos
  close(log); //Cerramos el fichero
  if(ret < 0)
    perror("execl");

  exit(0);
}

//Monitor procesos
void proc_monitor(int n)
{
  int ret;
  int fd;
  pid_t pid_ps;

  while(1)
  {
    pid_ps = fork(); //Creación del proceso hijo
    if(pid_ps == 0){ //Hijo
      fd = open("process.log",O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR); //Creamos el archivo
      if(fd == -1)
      {
        printf("%s",strerror(errno));
      }
  	  dup2(fd,1); //Redirigimos la salida del comando "ps" al archivo "process.log"
      close(fd); //Cerramos el fichero
      ret = execl("/bin/ps","ps","r",NULL); //"-r" para mostrar los procesos activos
      if(ret < 0)
      {
    	  perror("execl");
      }
    }
    else
    sleep(n); //Esperar n segundos para volver a hacer el backup
  }
}

//MAIN
int main(int argc, char *argv[]){

  usage(argc);

 if(signal(SIGINT, sigint_handler) == SIG_ERR) //Error en CTRL-C
    printf("\nError Catching signal\n");


  pid_t pid_date[50], pid_file, pid_backup, pid_editor, pid_proc;
  int choice, ex = 1,result = 0, i = 0, j = 0, n;
  int fd[2], status;
  int monitor_stat = 0, file_stat = 0, editor_stat = 0, backup_stat = 0;
  pid_t check;

  do
  {
    do
    {
      menu();

      result = scanf("%d", &choice); //Esperar a opción que elija el usuario
      if(result == 0)
        while(fgetc(stdin) != '\n');

    }while(result <= 0);

    switch (choice) {
      case 0: //EXIT
        ex = 0;
        i--;
        //Mandamos una señal SIGKILL a todos los procesos para matarlos al cerrar el programa
        for(;i>=0;i--){
          kill(pid_date[i],SIGKILL);
          printf("%d reporting: Terminating\n", pid_date[i]);
        }
        if(file_stat == 1){ //Para saber si se ha activado el proceso
          check = waitpid(pid_file, &status, WNOHANG); //waitpid() -> Para saber si el proceso está vivo
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
      case 1: //EDITOR
        printf("\nEditing user data\n");
        pid_editor = fork(); //Creación del hijo
        editor_stat = 1; //Proceso editor activado o creado
        if(pid_editor < 0)
        {
          fprintf(stderr, "\nEditor_Fork Failed\n");
          exit(-1);
        }

        if(pid_editor == 0) //Hijo
          editor();

        break;
      case 2: //MONITOR FILE SYSTEM
        printf("\nMonitoring file system\n");
        pid_file = fork(); //Creación del hijo
        file_stat = 1; //Proceso file system activado o creado
        if(pid_file < 0)
        {
          fprintf(stderr, "\nFile_Fork Failed\n");
          exit(-1);
        }
        if(pid_file == 0) //Hijo
          file_logger();

        break;
      case 3: //CLOCK ACTIVATION

        if(i<0)
          i=0;
        pid_date[i] = fork(); //Creación de array de procesos hijos
        if(pid_date[i] < 0)
        {
          fprintf(stderr, "\nDate_Fork Failed\n");
          exit(-1);
        }
        if(pid_date[i] == 0) //Hijo
          clock_activation();
        else{ //Padre
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
      case 4: //CLOCK STOP
        i--;
        j = i;
        //Matar todos los procesos activados de reloj
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
      case 5: //PROCESS MONITOR ACTIVATION
        if(monitor_stat == 0){
          printf("\nProcess monitoring\n");
          n = atoi(argv[1]); //Argumento de ejecución "n"

          if((pid_proc = fork()) < 0)
          {
            fprintf(stderr, "\nProc_Monitor_Fork Failed\n");
            exit(-1);
          }
          if(pid_proc == 0) //Hijo
          {
            proc_monitor(n);
          }else{ //Padre
            monitor_stat = 1;
          }
          if(monitor_stat == 1)
            printf("\nProcess monitor already activated\n");
        }
        break;
      case 6: //AUTOMATIC BACK UP ACTIVATION
        printf("\nBacking up\n");

        if (pipe(fd) < 0)
        {
          fprintf(stderr, "\nFather: Error in pipe creation\n\n");
          exit(-1);
        }
        pid_backup = fork(); //Creación del hijo
        backup_stat = 1; //Proceso backup activado o creado

        if(pid_backup < 0)
        {
          fprintf(stderr, "\nBackup_Fork Failed\n\n");
          exit(-1);
        }

        if(pid_backup == 0) //Hijo
          child_bkp(fd);
        else //Padre
          father_bkp(fd);
        break;
      case 7:
        printf("\nChecking live processes...\n");
        result = 0;
        j=i;

        //Comprobar y listar los procesos activos sólo si estan creados o activados
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
      default: //DEFAULT
        printf("Not valid\n");
        choice = 7;
        break;
    }
  }while(ex == 1); //Repetir hasta que se haya pulsado 0 "EXIT"
}

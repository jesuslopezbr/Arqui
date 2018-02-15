#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

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
    do{
      while(go == 0);
    app = fork();

    if(time_type == 0){
      if(app == 0)
        execlp("/bin/date", "date",NULL);
      time_type = 1;
    }else{
      if(app == 0)
        execlp("/bin/date", "date","-u",NULL);
      time_type = 0;
    }
    go = 0;
  }while (1);


}

int main(int argc, char *argv[]){

  usage(argc);

 if(signal(SIGINT, sigint_handler) == SIG_ERR)
    printf("\nError Catching signal\n");

  pid_t pid_date[100];
  int choice;
  int exit = 1;
  int result = 0;
  int i = 0;

  do{
    do{
      menu();

      result = scanf("%d", &choice);
      if(result == 0)
        while(fgetc(stdin) != '\n');

    }while(result <= 0);

    switch (choice) {
      case 0:
        printf("Exit\n");
        exit = 0;
        while(pid_date[i] == 0){
          if(pid_date != 0){
            kill(pid_date, SIGKILL);
          i++;
        }
        }
        wait(NULL);
        break;
      case 1:
        printf("Editing user data\n");
        break;
      case 2:
        printf("Monitoring file system\n");
        break;
      case 3:
        pid_date[i] = fork();
        printf("Clock activated\n");
        if(pid_date[i] == 0)
          clock_activation();
        i++;
        break;
      case 4:
        printf("Clocks stopped\n");
        i = 0;
        while(pid_date[i] == 0){
          if(pid_date[i] != 0){
            kill(pid_date[i], SIGKILL);
          i++;
        }
        break;
      case 5:
        printf("Process monitoring\n");
        break;
      case 6:
        printf("Backing up\n");
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

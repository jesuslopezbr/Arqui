#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void usage(int argc){
  if(argc != 2){
    fprintf(stderr, "Usage: <monitoring_time_interval>\n" );
    exit(-1);
  }
}

int main(int argc, char *argv[]){

  usage(argc);

  int choice;
  int exit = 1;
  int result = 0;

  do{
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

    do{
      result = scanf("%d", &choice);
      printf("%d\n", result);
    }while(result <= 0);

    switch (choice) {
      case 0:
        printf("Exit\n");
        exit = 0;
        break;
      case 1:
        printf("Editing user data\n");
        break;
      case 2:
        printf("Monitoring file system\n");
        break;
      case 3:
        printf("Clock activated\n");
        break;
      case 4:
        printf("Clocks stopped\n");
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

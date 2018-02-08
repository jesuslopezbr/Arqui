#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
  pid_t pid1,pid2;
  pid1 = fork();

 if(pid1 < 0){
  perror("fork() error");
  exit(-1);
 }
 if(pid1 == 0){
   while(1){
  for(char c = 'A'; c <= 'C'; ++c)
    printf("%c\n", c);
    sleep(1);
  }
 }
 else{
   pid2 = fork();
   if(pid2 < 0){
    perror("fork() error");
    exit(-1);
   }
   if(pid2 == 0){
     while(1){
     for(char c = 'a'; c <= 'c'; ++c)
       printf("%c\n", c);
     sleep(1);
     }
   }else{
     while(1){
       printf("El padre ejecutando...\n");
       sleep(1);
     }
     wait(NULL);
   }
  }
}

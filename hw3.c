#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>


int main(){
  char line[500];
  char argsarray[20][100];

  //User prompt
  printf("CS361 > ");
  fgets(line, 500, stdin);
  int fd;
  int ret;
  int pid = fork();

  fd = open("filename.txt" , O_CREAT | O_APPEND |O_WRONLY );

while(1){
  //if (pid == 0) {
   // printf("I am the child!  I have pid %d.\n", getpid());
    //exit(6);
  //} else {
    printf("pid: %d status:%d\n", getpid(), pid);
   waitpid();
    int status;
   // wait(&status);
    exit(status);
     printf("CS361 > ");
   //printf("My child has died with status %d. :(\n", WEXITSTATUS(status));
   //printf("My child has died with status %d. :(\n", WEXITSTATUS(status));
  }

                return 0;
}

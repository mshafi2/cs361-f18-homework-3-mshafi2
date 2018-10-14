#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>


int main(void){
    pid_t child;
    int status;
    char line[500];
    char argsarray[20][100];

    printf("CS361 > ");
    fgets(line, 500, stdin);

//break the string up into words
  char *word = strtok(line, " ");
  int i = 0;
  while (word) {
    printf("word: %s\n", word);
    //copy a word to the arg array
    strcpy(argsarray[i], word);
    //get next word
    word = strtok(NULL, " ");
    i = i + 1;
  }

  //print out our array
  int j=0;
  for (;j<i;j++){
    printf("argsarray[%d]: %s\n", j, argsarray[j]);
}
//---------------------------------------------------
   pid_t pid = fork();

  if (pid < 0) {
    printf("Fork failed \n");
  }
  if (pid == 0) {
    printf("pid:%d status:%d\n" , (int)getpid(),(int)pid);
                                                        
    int status;
    wait(&status);
   }
   if (pid > 0){
     printf("pid:%d status:%d\n" , (int)getpid() , (int)pid);
    }
    printf("CS361 > ");
    fgets(line, 500, stdin);

   while (word) {
    printf("word: %s\n", word);
    //copy a word to the arg array
    strcpy(argsarray[i], word);
    //get next word
    word = strtok(NULL, " ");
    i = i + 1;

    //print out our array
  for (;j<i;j++){
    printf("argsarray[%d]: %s\n", j, argsarray[j]);

}
//---------------------------------------------------
        int fd;
        int ret;

        fd = open("filename.txt", O_CREAT | O_APPEND | O_WRONLY);

        if(fd < 0)
        {
          perror("open");
           exit(1);
         }

        ret = dup2(fd, 1);

        if(ret < 0)
        {
           perror("dup2");
           exit(1);
        }
 system("ls /tmp");
        close(fd);

}
        return 0;

}

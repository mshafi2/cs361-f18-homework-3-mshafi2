#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>


int main(){
  char line[500];
  char argsarray[20][100];

  char **malArray = (char **) malloc(1000 * sizeof(char));
  
 
while(1){
 printf("CS361 > ");
 
 fgets(line, 500, stdin);
 
 	line[strlen(line) - 1] = '\0';
 	
 if(strcmp(line, "exit") ==0){
 	exit(0);
 }
 

  char *word = strtok(line, " ");
  int i = 0;
   
  
  while (word) 
  {
  	
    printf("word: %s\n", word);
    
    //copy a word to the arg array
    strcpy(argsarray[i], word);
   
	
    //get next word
    word = strtok(NULL, " ");
    
    
    malArray[i] = argsarray[i];
    i = i + 1;
    
    //printf("pid:%d status:%d\n", getpid(), pid);
  }
    int pid = fork();
  if (pid == 0) 
  {
    printf("pid:%d status:%d\n", getpid());
    execv(malArray[0], malArray);
   // printf("Hello adding print statement\n");
  } 
  else 
  {
   // printf("I am the parent.  I am waiting for my child %d to die.\n", pid);
    int status;
    wait(&status);
   // printf("My child has died with status %d. :(\n", WEXITSTATUS(status));
  }
   
   
  }

		return 0;
}

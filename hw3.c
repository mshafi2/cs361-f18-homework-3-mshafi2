#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>


int main(){
  char line[500];
  char argsarray[20][100];

 
while(1){
 printf("CS361 > ");
 fgets(line, 500, stdin);
 
 if(strcmp(line, "exit\n") ==0){
 	exit(0);
 }
 	
  int fd;
  int ret;
  //int pid = fork();
  
  //fd = open("filename.txt" , O_CREAT | O_APPEND |O_WRONLY );
  
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
   
  }

		return 0;
}

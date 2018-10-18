#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#define ARGUMENTS 20
#define COMMAND 500

//================================================================
// Check for signal SIGTSTP
void sigtstp_handler(int sig){
  char msg[] = "SIGTSTP handled\n";
  write(1, msg, sizeof(msg));
  return;
}

// Check for signal SIGINT
void sigint_handler(int sig){
  char msg[] = "SIGINT handled\n";
  write(1, msg, sizeof(msg));
  return;
}

// Check for input 'exit'
int stringCheck(char**args){
  if(!strcmp(args[0], "exit"))
    exit(0);
  return 0;
}
// Parse line
int getLine(char *token, char**args){
  char* temp;
  int count = 0;
  int parsedValue;

  token[strlen(token)-1] = ' ';
  while(*token && (*token == ' ')){
    token++;
  }
  while((temp = strchr(token, ' '))){
    args[count++] = token;
    *temp = '\0';
    token = temp + 1;
    while(*token && (*token == ' ')){
      token++;
    }
  }
  args[count] = NULL;

  if(count == 0){
    return 1;
  }

  if((parsedValue = (*args[count-1] == '&')) != 0){
    args[--count] = NULL;
  }

  return parsedValue;
}
// Fork() and execute user command
void forkAndEval(char *line)
{
  // Declare variables
  char *args[ARGUMENTS];
  char token[COMMAND];
  int parsedValue;
  pid_t pid;

  strcpy(token, line);
  parsedValue = getLine(token, args);


  if(!stringCheck(args)){
    // Fork child
    pid = fork();
    if(pid == 0){

      // Print PID value
      printf("PID: %d\n", getpid());

      // I/O Redirection
      int fd0,fd1,fd2;
      int value_in=0;
      int value_out=0;
      int value_out_2 =0;
      char array_input[200];
      char array_output[200];
      char* array_output_2 = malloc(200);
      int i = 0;
      for(i=0;args[i]!='\0';i++)
      {
        // Check for '<'
        if(strcmp(args[i], "<") == 0)
        {
          args[i] = NULL;
          strcpy(array_input, args[i+1]);
          value_in = 2;
        }
        // Check for '>'
        if(strcmp(args[i], ">") == 0)
        {
          args[i]=NULL;
          strcpy(array_output, args[i+1]);
          value_out = 2;
        }
        // Check for '>>'
        if(strcmp(args[i], ">>") == 0)
        {
          args[i] = NULL;
          strcpy(array_output_2, args[i+1]);
          value_out_2 = 2;
        }
      }
      // Command reads input from filename
      if (value_in)
      {
        if ((fd0 = open(array_input, O_RDONLY, 0)) < 0) {
            exit(0);
        }
        dup2(fd0, 0);
        close(fd0);
      }
      // Redirect the output of command to filename
      if (value_out)
      {
        if ((fd1 = creat(array_output , 0644)) < 0) {
            exit(0);
        }
        dup2(fd1, STDOUT_FILENO);
        close(fd1);
      }
      // Redirect the output of command to filename
      if (value_out_2)
      {
        fd2 = open(array_output_2, O_APPEND);
        int nw = write(fd2, array_output_2, 200);
        dup2(fd2, nw);
        close(fd2);
      }
      // Execute
      execvp(args[0], args);
    }
    else {
      int status;
      // Wait for child process
      while (!(wait(&status) == pid));
      // Print exit status
      printf("Exit: %d\n", WEXITSTATUS(status));
    }
  }
  return;
}




//=========================================================================
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
 

  char *word = strtok(line, ";");
  int i = 0;
   
  
  while (word) 
  {
  	
    printf("word: %s\n", word);
    
    //copy a word to the arg array
    strcpy(argsarray[i], word);
   
	
    //get next word
    word = strtok(NULL, ";");
    
    
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
//---------------------------------------
void sigint_handler(int sig){
  char msg[] = "Signal handled.  Deal with it.\n";
  write(1, msg, sizeof(msg));
  exit(0);
}

//----------------------------------------

int main(){
  char line[500];
  char argsarray[20][100];
  char argsarray1[20][100];

  char **malArray = (char **) malloc(30 * sizeof(char));
  char **malArray1 = (char **) malloc(30 * sizeof(char));
 	
 
	while(1)
	{
 		printf("CS361 > ");
 
 		fgets(line, 500, stdin);
 
 		line[strlen(line) - 1] = '\0';
 	
 		if(strcmp(line, "exit") ==0)
 		  {
 				exit(0);
 		  }
 
 	   	char *word = strtok(line, " ");
  	   	int i = 0;
  	   	int u = 0;
  
		while (word) 
		{
		   // printf("word1: %s\n", word);
		    int ret;
		    ret = strcmp(word, ";");
		  	if(ret == 0)
		  	{
		  		word =strtok(NULL, " ");
		  		
	  		
		   			while(word)
		    	 	{
			   			//printf("word2: %s\n", word);
			   			strcpy(argsarray1[u], word);
			   		 		//get next word
			    		word = strtok(NULL, " ");
			    		malArray1[u] = argsarray1[u];
			   				 u = u + 1;
			   			malArray1 [u] = NULL;
					}
				break;	
			}
//------------------------------------------------------------
   		 //copy a word to the arg array
    	 strcpy(argsarray[i], word);
    	 //get next word
    	 word = strtok(NULL, " ");
     	 malArray[i] = argsarray[i];
      	 	i = i + 1;
      	 	malArray [i] = NULL;
  		}
  		
  		
  		  //print out our array
 		 int j=0;
   
//  for (;j<i;j++){
//    printf("argsarray[%d]: %s\n", j, argsarray[j]);
//  }  
  
    //print out our array
  
//  for (j=0; j<u;j++){
//    printf("argsarray1[%d]: %s\n", j, argsarray1[j]);
//  }  
  		
  		
  		 int pid = fork();
  if (pid == 0) 
  {
   
    execv(malArray[0], malArray);
   // printf("Hello adding print statement\n");
  } 
  else 
  {
   // printf("I am the parent.  I am waiting for my child %d to die.\n", pid);
    int status;
    wait(&status);
    printf("pid:%d status:%d\n", getpid()+1 ,  WEXITSTATUS(status));
   // printf("My child has died with status %d. :(\n", WEXITSTATUS(status));
  }
  
  int pid1 = fork();
  if (pid1 == 0) 
  {
  
    execv(malArray1[0], malArray1);
   // printf("Hello adding print statement\n");
  } 
  else 
  {
  	
   // printf("I am the parent.  I am waiting for my child %d to die.\n", pid);
    int status1;
    wait(&status1);
    printf("pid:%d status:%d\n", getpid()+1, WEXITSTATUS(status1));
   // printf("My child has died with status %d. :(\n", WEXITSTATUS(status));
  }
}
//===========================IOREDIRECT======================================
char buf1[20];
  char buf2[20];
  char buf3[20];
  char buf4[20];
  
  int fd1 = open("sampletext1.txt", O_RDONLY);
  int fd2 = open("sampletext2.txt", O_RDONLY);

int fd = open("output.txt", O_RDWR);
dup2(fd,2);
fprintf(stderr,"Hello world\n");

  read(fd1, buf1, 19);
  buf1[19] = '\0';
  printf("%s\n", buf1);

  read(fd2, buf2, 19);
  buf2[19] = '\0';
  printf("%s\n", buf2);

  dup2(fd1, fd2);

  read(fd1, buf3, 19);
  buf3[19] = '\0';
  printf("%s\n", buf3);

  read(fd2, buf4, 19);
  buf4[19] = '\0';
  printf("%s\n", buf4);
  
//============================SIGNAL HANDLER=====================================
  signal(SIGINT, sigint_handler);

  int i = 99;
  while(1){
    printf("%d bottles of beer on the wall\n", i);
    printf("%d bottles of beer\n", i);
    printf("Take one down, pass it around\n");
    i = i - 1;
    printf("%d bottles of beer on the wall\n", i);
  } 
  
  
//======================================================================

		return 0;
}

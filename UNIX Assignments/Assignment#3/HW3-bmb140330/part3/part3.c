#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sysexits.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
    char line[256];
    char prompt[] = "Write PIPE command or to end program press (Ctrl + D) \n";
    int MAX_ARGS = 10000;
    int status;
    
    /* spit out the prompt */
    printf("%s", prompt );
    /* Try getting input. If error or EOF, exit */
    while( fgets(line, sizeof line, stdin) != NULL ){
		/* fgets leaves '\n' in input buffer. ditch it */
		line[strlen(line)-1] = '\0';

		//first tokenize on pipe
		char* string = line;
		char** args = (char**)malloc(MAX_ARGS*sizeof(char*));
		memset(args, 0, sizeof(char*)*MAX_ARGS);

		char** commands1 = (char**)malloc(MAX_ARGS*sizeof(char*));
		memset(commands1, 0, sizeof(char*)*MAX_ARGS);

		char** commands2 = (char**)malloc(MAX_ARGS*sizeof(char*));
		memset(commands2, 0, sizeof(char*)*MAX_ARGS);

		char* curToken = strtok(string, "|");
		int i = 0, numOfArgs=0;
	    for(i = 0; curToken != NULL; ++i){
	        args[i] = strdup(curToken);
	  		curToken = strtok(NULL, "|");
	  	}
	  	numOfArgs=i;
	  	
	  	int pipefd[2];
  		int pid;

  		char *first_args[] = {NULL,NULL,NULL,NULL,NULL};
  		char *second_args[] = {NULL,NULL,NULL,NULL,NULL};
		
		if(numOfArgs==2){
			if(!fork()){
				curToken = strtok(args[0], " \t");
				for(i = 0; curToken != NULL; ++i){
			        commands1[i] = strdup(curToken);
			  		curToken = strtok(NULL, " \t");
			  	}

			  	int k;
			  	for(k=0; k<i; k++){
			  		first_args[k]=commands1[k];
			  	}

				
				curToken = strtok(args[1], " \t");
				for(i = 0; curToken != NULL; ++i){
			        commands2[i] = strdup(curToken);
			  		curToken = strtok(NULL, " \t");
			  	}

			  	for(k=0; k<i; k++){
			  		second_args[k]=commands2[k];
			  	}
			  	
			  	pipe(pipefd);

		  		pid = fork();

				if (pid == 0)
			    {

					
						dup2(pipefd[0], 0);

						close(pipefd[1]);

						execvp(commands2[0], second_args);
	  			}
			  	else
			    {
			    	
				    	dup2(pipefd[1], 1);

				    	close(pipefd[0]);

				    	execvp(commands1[0], first_args);
			  		
			    }	
			}
			wait(&status);
			wait(&status);
		}else{
			if(!fork()){
				curToken = strtok(args[0], " \t");
				for(i = 0; curToken != NULL; ++i){
			        commands1[i] = strdup(curToken);
			  		curToken = strtok(NULL, " \t");
			  	}
			  	
			  	int k;
			  	for(k=0; k<i; k++){
			  		first_args[k]=commands1[k];
			  	}
			  	
			  	execvp(commands1[0], first_args);
		  	}
		  	wait(&status);
		}
		
		close(pipefd[0]);
		close(pipefd[1]);


	     printf("\n\n%s", prompt );
    }

    printf("\n ** PIPE Program Closed ** \n");

    return 0;
}
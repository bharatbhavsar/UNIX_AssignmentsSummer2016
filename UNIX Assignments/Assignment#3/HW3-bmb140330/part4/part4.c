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

		
		char *first_args[] = {NULL,NULL,NULL,NULL,NULL};

		char* curToken = strtok(string, "|");
		int i = 0, numOfArgs=0;
	    for(i = 0; curToken != NULL; ++i){
	        args[i] = strdup(curToken);
	  		curToken = strtok(NULL, "|");
	  	}
	  	numOfArgs=i;
	  	if(strcmp(args[0],"exit")==0 || strcmp(args[0],"Exit")==0 || strcmp(args[0],"Exit")==0){
	  		printf("\nProgram ended with EXIT\n");
	  		exit(0);
	  	}
	  	if(!fork()){
		  	for( i=0; i<numOfArgs-1; i++){
		        int pd[2],k;
		        pipe(pd);

		        if (!fork()) {
			        curToken = strtok(args[i], " \t");
					for(i = 0; curToken != NULL; ++i){
				        commands1[i] = strdup(curToken);
				  		curToken = strtok(NULL, " \t");
				  	}

				  	//int k;
				  	for(k=0; k<i; k++){
				  		first_args[k]=commands1[k];
				  	}
		            dup2(pd[1], 1); // remap output back to parent
		            //execlp(args[i], args[i], NULL);
		            execvp(first_args[0], first_args);
		            perror("exec");


		            //abort();
		        }

		        // remap output from previous child to input
		        dup2(pd[0], 0);
		        close(pd[1]);

		       	for(k=0; k<5; k++){
					first_args[k]=NULL;
				}
	    	}

		  	curToken = strtok(args[i], " \t");
			for(i = 0; curToken != NULL; ++i){
		        commands1[i] = strdup(curToken);
		  		curToken = strtok(NULL, " \t");
		  	}

		  	int k;
		  	for(k=0; k<i; k++){
		  		first_args[k]=commands1[k];
		  	}

		  	
			//execlp(args[i], args[i], NULL);
	    	execvp(first_args[0], first_args);
	    	perror("exec");
	    }
	    int k;
	    for(k=0; k<numOfArgs;k++){
	    	wait(&status);
	    }
	    printf("\n\n%s", prompt );
    }

    printf("\n ** PIPE Program Closed ** \n");

    return 0;
}
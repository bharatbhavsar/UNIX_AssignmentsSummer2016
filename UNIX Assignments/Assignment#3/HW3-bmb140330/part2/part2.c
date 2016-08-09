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


int
main(int argc, char **argv) {
	char line[256];
	pid_t pid;
	int status;
	char* curToken ;
	int in,out;
	int MAX_ARGS = 10000;
	char prompt[] = "Write Fileredirection command or to end program press (Ctrl + D) \n";

	printf("\n%s", prompt );

	while (fgets(line, sizeof line, stdin) != NULL) {
		line[strlen(line)-1] = '\0';

		char* string = line;

		if((pid=fork()) == -1) {  
			fprintf(stderr, "shell: can't fork: %s\n",
					strerror(errno));
			continue;
		} else if (pid == 0){   
			/* child to run the command */

			/* your code to parse the command & set any file redirection as needed */

			char** args = (char**)malloc(MAX_ARGS*sizeof(char*));
			memset(args, 0, sizeof(char*)*MAX_ARGS);

			char** command = (char**)malloc(MAX_ARGS*sizeof(char*));
			memset(command, 0, sizeof(char*)*MAX_ARGS);

			char** option = (char**)malloc(MAX_ARGS*sizeof(char*));
			memset(option, 0, sizeof(char*)*MAX_ARGS);

			char** fileIn = (char**)malloc(MAX_ARGS*sizeof(char*));
			memset(fileIn, 0, sizeof(char*)*MAX_ARGS);

			char** fileOut = (char**)malloc(MAX_ARGS*sizeof(char*));
			memset(fileOut, 0, sizeof(char*)*MAX_ARGS);

			char *fileDoubleDirect = ">>";

			int i=0, numOfArgs;

			int inFile=0, outDFile=0, outFile=0, isExecuted=0;

			//Parse on <
			curToken = strtok(string, "<");
	  		for(i = 0; curToken != NULL; ++i){
	        	args[i] = strdup(curToken);
	  			curToken = strtok(NULL, "<");
	  		}
	  		numOfArgs=i;
	  		if(numOfArgs>1){
	  			//if more than 1 part parse part 0 on space and store in command and option
	  			inFile=1;
	  			curToken = strtok(args[0], " \t");
	  			int k;
	  			for( k=0; curToken != NULL; ++k){
	  				command[k]=strdup(curToken);
	  				curToken = strtok(NULL, " \t");
	  			}
	  			if(k==2){
	  				option[0]=command[1];
	  			}else{
	  				option[0]=NULL;
	  			}
	  			if(strstr(args[1],fileDoubleDirect)!=NULL){
	  				//then parse second part on >>
	  				outDFile=1;
	  				curToken = strtok(args[1], ">>");
			  		for(i = 0; curToken != NULL; i++){
			        	fileIn[i] = strdup(curToken);
			  			curToken = strtok(NULL, ">>");
			  		}
			  		//if more than one part, save part one as input and part 2 as o/p
			  		curToken = strtok(fileIn[0], " \t");
		  			for( k=0; curToken != NULL; k++){
		  				fileIn[k]=strdup(curToken);
		  				curToken = strtok(NULL, " \t");
		  			}

		  			curToken = strtok(fileIn[1], " \t");
		  			for( k=0; curToken != NULL; k++){
		  				fileOut[k]=strdup(curToken);
		  				curToken = strtok(NULL, " \t");
		  			}


		  			in=open(fileIn[0],O_RDONLY);
		  			out=open(fileOut[0], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

		  			dup2(in, 0);
		  			dup2(out,1);

		  			char *execvpArgs[] = {command[0],option[0],NULL};

		  			execvp(command[0],execvpArgs);
		  			isExecuted=1;
	  			}else{
	  				//else parse part 2 on >
					outFile=1;
					curToken = strtok(args[1], ">");
			  		for(i = 0; curToken != NULL; i++){
			        	fileIn[i] = strdup(curToken);
			  			curToken = strtok(NULL, ">");
			  		}
			  		// if more than 1 part save part one as input and part 2 as o/p
			  		if(i>1){
				  		curToken = strtok(fileIn[0], " \t");
			  			for( k=0; curToken != NULL; k++){
			  				fileIn[k]=strdup(curToken);
			  				curToken = strtok(NULL, " \t");
			  			}

			  			curToken = strtok(fileIn[1], " \t");
			  			for( k=0; curToken != NULL; k++){
			  				fileOut[k]=strdup(curToken);
			  				curToken = strtok(NULL, " \t");
			  			}


			  			in=open(fileIn[0],O_RDONLY);
			  			out=open(fileOut[0], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

			  			dup2(in, 0);
			  			dup2(out,1);

			  			char *execvpArgs[] = {command[0],option[0],NULL};

			  			execvp(command[0],execvpArgs);  				
			  			isExecuted=1;
			  		}
	  			}
	  			if(isExecuted==0){
	  				//Else you have only input with standard O/P
	  				curToken = strtok(args[1], " \t");
		  			for( k=0; curToken != NULL; k++){
		  				fileIn[k]=strdup(curToken);
		  				curToken = strtok(NULL, " \t");
		  			}

		  			in=open(fileIn[0],O_RDONLY);
		  			dup2(in, 0);
		  			char *execvpArgs[] = {command[0],option[0],NULL};
		  			execvp(command[0],execvpArgs);  				
		  			isExecuted=1;
	  			}
	  			inFile=0;
	  			outDFile=0;
	  			outFile=0;
	  			isExecuted=0;
				
			}else{
				//else parse on >>

				if(strstr(string,fileDoubleDirect)!=NULL){
	  				curToken = strtok(string, ">>");
			  		for(i = 0; curToken != NULL; i++){
			        	args[i] = strdup(curToken);
			  			curToken = strtok(NULL, ">>");
			  		}
			  		numOfArgs=i;
			  		if(numOfArgs>1){
			  			//if more than 1 part parse part 0 on space and store in command and option if 2 parts else store as command only and part 1 as O/P
			  			curToken = strtok(args[0], " \t");
			  			int k;
			  			for( k=0; curToken != NULL; k++){
			  				command[k]=strdup(curToken);
			  				curToken = strtok(NULL, " \t");
			  			}


			  			if(k==2){
			  				option[0]=command[1];
			  			}else{
			  				option[0]=NULL;
			  			}
			  			
			  			
			  			curToken = strtok(args[1], " \t");
			  			for( k=0; curToken != NULL; k++){
			  				fileOut[k]=strdup(curToken);
			  				curToken = strtok(NULL, " \t");
			  			}
			  			out=open(fileOut[0], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
			  			dup2(out,1);
			  			char *execvpArgs[] = {command[0],option[0],NULL};

			  			execvp(command[0],execvpArgs);  				
		  				isExecuted=1;
			  		}	
					
				}else{
				//else parse on >
					curToken = strtok(string, ">");
			  		for(i = 0; curToken != NULL; i++){
			        	args[i] = strdup(curToken);
			  			curToken = strtok(NULL, ">");
			  		}
			  		numOfArgs=i;
			  		if(numOfArgs>1){
			  			//if more than 1 part parse part 0 on space and store in command and option if 2 parts else store as command only and part 1 as O/P
			  			curToken = strtok(args[0], " \t");
			  			int k;
			  			for( k=0; curToken != NULL; k++){
			  				command[k]=strdup(curToken);
			  				curToken = strtok(NULL, " \t");
			  			}


			  			if(k==2){
			  				option[0]=command[1];
			  			}else{
			  				option[0]=NULL;
			  			}
			  			
			  			
			  			curToken = strtok(args[1], " \t");
			  			for( k=0; curToken != NULL; k++){
			  				fileOut[k]=strdup(curToken);
			  				curToken = strtok(NULL, " \t");
			  			}
			  			out=open(fileOut[0], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
			  			dup2(out,1);
			  			char *execvpArgs[] = {command[0],option[0],NULL};

			  			execvp(command[0],execvpArgs);  				
		  				isExecuted=1;
			  		}	
					//if more than 1 part parse part 0 on space and store in command and option if 2 parts else store as command only and part 1 as O/P
				}

			if ((pid=waitpid(pid, &status, 0)) < 0)
			fprintf(stderr, "shell: waitpid error: %s\n",
					strerror(errno));
			}
		}

        printf("\n\n%s", prompt );	
	}

	printf("\n ** FileRedirection Program Closed ** \n");
	exit(EX_OK);
}

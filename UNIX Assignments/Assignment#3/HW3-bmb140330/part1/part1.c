#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    char line[256];
    char prompt[] = "Write command to parse or to end program press (Ctrl + D) \n";
    int MAX_ARGS = 10000;
    int pipe = 0, fileIO = 0;
    /* spit out the prompt */
    printf("%s", prompt );
    char *fileDoubleDirect = ">>";
    /* Try getting input. If error or EOF, exit */
    while( fgets(line, sizeof line, stdin) != NULL ){
		/* fgets leaves '\n' in input buffer. ditch it */
		line[strlen(line)-1] = '\0';

		//first tokenize on pipe
		char* string = line;
		char** args = (char**)malloc(MAX_ARGS*sizeof(char*));
		memset(args, 0, sizeof(char*)*MAX_ARGS);

		char** commands = (char**)malloc(MAX_ARGS*sizeof(char*));
		memset(commands, 0, sizeof(char*)*MAX_ARGS);

		char** myFiles = (char**)malloc(MAX_ARGS*sizeof(char*));
		memset(myFiles, 0, sizeof(char*)*MAX_ARGS);
	    
	    char* curToken = strtok(string, "|");
		int i = 0, numOfArgs=0;
	    for(i = 0; curToken != NULL; ++i){
	        args[i] = strdup(curToken);
	  		curToken = strtok(NULL, "|");
	  	}


	  	numOfArgs=i;
	  	if(numOfArgs>1){
	  		for(i=0; i<numOfArgs;i++){
	  			if(i<numOfArgs-1){
	  				curToken = strtok(args[i], " \t");
	  				int k;
		  			for(k=0; curToken != NULL; ++k){
		  				commands[k]=strdup(curToken);
		  				curToken = strtok(NULL, " \t");
		  			}
		  			printf("\n Command: ");
		  			int l;
		  			for(l = 0; l<k; l++){
		  				printf("%s ", commands[l]);
		  			}
		  			printf("\n PIPE");
		  		}else{
		  			curToken = strtok(args[i], " \t");
		  			int k;
		  			for(k=0; curToken != NULL; ++k){
		  				commands[k]=strdup(curToken);
		  				curToken = strtok(NULL, " \t");
		  			}
		  			printf("\n Command: ");
		  			int l;
		  			for(l = 0; l<k; l++){
		  				printf("%s ", commands[l]);
		  			}
		  		}
	  		}
	  	}else{
	  		curToken = strtok(string, "<");
	  		for(i = 0; curToken != NULL; ++i){
	        	args[i] = strdup(curToken);
	  			curToken = strtok(NULL, "<");
	  		}
	  		numOfArgs=i;
	  		if(numOfArgs>1){
	  			curToken = strtok(args[0], " \t");
	  			int k;
	  			for( k=0; curToken != NULL; ++k){
	  				commands[k]=strdup(curToken);
	  				curToken = strtok(NULL, " \t");
	  			}
	  			printf("\n Command: ");
	  			for(i=0; i<k; i++){
	  				printf("%s", commands[i]);
	  			}
	  			printf("\n FileRedirection: <");
	  			if(strstr(args[1],fileDoubleDirect)!=NULL){
	  				curToken = strtok(args[1], ">>");
			  		for(i = 0; curToken != NULL; i++){
			        	commands[i] = strdup(curToken);
			  			curToken = strtok(NULL, ">>");
			  		}

			  		curToken = strtok(commands[0], " \t");
		  			for( k=0; curToken != NULL; k++){
		  				myFiles[k]=strdup(curToken);
		  				curToken = strtok(NULL, " \t");
		  			}
		  			printf("\n Files: ");
		  			for(i=0; i<k; i++){
		  				printf("%s", myFiles[i]);
		  			}
		  			printf("\n FileRedirection: >>");
		  			curToken = strtok(commands[1], " \t");
		  			for( k=0; curToken != NULL; k++){
		  				myFiles[k]=strdup(curToken);
		  				curToken = strtok(NULL, " \t");
		  			}
		  			printf("\n Files: ");
		  			for(i=0; i<k; i++){
		  				printf("%s", myFiles[i]);
		  			}
	  			}else{
		  			curToken = strtok(args[1], ">");
			  		for(i = 0; curToken != NULL; i++){
			        	commands[i] = strdup(curToken);
			  			curToken = strtok(NULL, ">");
			  		}
			  		int remaining = i;
			  		if(remaining>1){
			  			curToken = strtok(commands[0], " \t");
			  			int k;
			  			for( k=0; curToken != NULL; k++){
			  				myFiles[k]=strdup(curToken);
			  				curToken = strtok(NULL, " \t");
			  			}
			  			printf("\n File: ");
			  			for(i=0; i<k; i++){
			  				printf("%s", myFiles[i]);
			  			}
			  			printf("\n FileRedirection: >");
			  			curToken = strtok(commands[1], " \t");
			  			for( k=0; curToken != NULL; k++){
			  				myFiles[k]=strdup(curToken);
			  				curToken = strtok(NULL, " \t");
			  			}
			  			printf("\n Files: ");
			  			for(i=0; i<k; i++){
			  				printf("%s", myFiles[i]);
			  			}

			  		}else{
			  			curToken = strtok(args[1], " \t");
				  		for(i = 0; curToken != NULL; i++){
				        	commands[i] = strdup(curToken);
				  			curToken = strtok(NULL, " \t");
				  		}
				  		int remaining = i;
				  		printf("\n Files: ");
				  		for(i=0;i<remaining;i++){
				  			printf("%s", commands[i]);
				  		}
			  		}
		  		}
	  		}else{
	  			if(strstr(string,fileDoubleDirect)!=NULL){
	  				curToken = strtok(string, ">>");
			  		for(i = 0; curToken != NULL; i++){
			        	args[i] = strdup(curToken);
			  			curToken = strtok(NULL, ">>");
			  		}
			  		numOfArgs=i;
			  		if(numOfArgs>1){
			  			//parsing for >
			  			curToken = strtok(args[0], " \t");
			  			int k;
			  			for( k=0; curToken != NULL; k++){
			  				commands[k]=strdup(curToken);
			  				curToken = strtok(NULL, " \t");
			  			}
			  			printf("\n Command: ");
			  			for(i=0; i<k; i++){
			  				printf("%s", commands[i]);
			  			}
			  			printf("\n FileRedirection: >>");
			  			curToken = strtok(args[1], " \t");
			  			for( k=0; curToken != NULL; k++){
			  				commands[k]=strdup(curToken);
			  				curToken = strtok(NULL, " \t");
			  			}
			  			printf("\n Files: ");
			  			for(i=0; i<k; i++){
			  				printf("%s", commands[i]);
			  			}
			  		}	
	  			}else{
		  			curToken = strtok(string, ">");
			  		for(i = 0; curToken != NULL; i++){
			        	args[i] = strdup(curToken);
			  			curToken = strtok(NULL, ">");
			  		}
			  		numOfArgs=i;
			  		if(numOfArgs>1){
			  			//parsing for >>
			  			curToken = strtok(args[0], " \t");
			  			int k;
			  			for( k=0; curToken != NULL; k++){
			  				commands[k]=strdup(curToken);
			  				curToken = strtok(NULL, " \t");
			  			}
			  			printf("\n Command: ");
			  			for(i=0; i<k; i++){
			  				printf("%s", commands[i]);
			  			}
			  			printf("\n FileRedirection: >");
			  			curToken = strtok(args[1], " \t");
			  			for( k=0; curToken != NULL; k++){
			  				commands[k]=strdup(curToken);
			  				curToken = strtok(NULL, " \t");
			  			}
			  			printf("\n Files: ");
			  			for(i=0; i<k; i++){
			  				printf("%s", commands[i]);
			  			}

			  		}else{
			  			curToken = strtok(string, " \t");
				  		for(i = 0; curToken != NULL; i++){
				        	args[i] = strdup(curToken);
				  			curToken = strtok(NULL, " \t");
				  		}
				  		numOfArgs = i;
				  		if(numOfArgs==1){
				  			printf("\n Command: %s", args[0]);
				  		}else if(numOfArgs==2){
				    		printf("\n Command: %s", args[0]);
				    		printf("\n Argument: %s", args[1]);
				    	}else{
				    		printf("\n Command: %s", args[0]);
				    		printf("\n Options: %s", args[1]);
				    		int j=2;
					    	if(j<numOfArgs){
					    		printf("\n Arguments: " );
					    		while(j<numOfArgs){
					    			printf("%s ", args[j]);
					    			j++;
					    		}
					    	}	
				    	}
			  		}
		  		}	
	  		}
	  	}
		printf("\n\n%s", prompt );
    }

    printf("\n ** Parsing Program Closed ** \n");

    return 0;
}
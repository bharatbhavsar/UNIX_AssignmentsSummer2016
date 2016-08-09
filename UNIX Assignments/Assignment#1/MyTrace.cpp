// trace0.c program   
// gcc trace0.cpp -o trace
// run: ./trace0 www.utdallas.edu
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// function to find max time
float max_time(float a[], int num_elements)
{
   int i;
   float max=-32000;
   for (i=0; i<num_elements; i++)
   {
	 if (a[i]>max)
	 {
	    max=a[i];
	 }
   }
   return(max);
}

//function to find min time
float min_time(float a[], int num_elements)
{
   int i;
   float min=32000;
   for (i=0; i<num_elements; i++)
   {
	 if (a[i]<min)
	 {
	    min=a[i];
	 }
   }
   return(min);
}

//function to find average time
float avg_time(float a[], int num_elements)
{
   int i;
   float addition = 0, avg=0;
   
   for (i=0; i<num_elements; i++)
   {
	   addition = addition + a[i];
   }
   avg = addition / num_elements;
   return(avg);
}


int main(int argc, char **argv){
     if(argc<2){
        printf("Usage: ./trace domain \n for example: ./trace www.utdallas.edu\n");
        exit(0);
     }
	char command[200];
	strcpy(command, "traceroute ");
	strcat(command, argv[1]);
	strcat(command, " > output.txt");

       system(command);
       
       FILE * fp;
       char * line = NULL;
       size_t len = 0;
       ssize_t read;
       char *token;
       char delimiter[5] = " (),";
       char* strArray[12];
       
       fp = fopen("output.txt", "r"); // open file
       if (fp == NULL)
           exit(EXIT_FAILURE);
       int line_number = 0;
       int currentLine = 0;
       int tokenNumber = 0;
       float time[3];
       float min, max, avg;

       while ((read = getline(&line, &len, fp)) != -1) { //while line present do following

            printf("%s", line);
            tokenNumber = 0;
            token = strtok(line, delimiter); // token separated
            if(currentLine == 0)
            {
              //code for fist line
              while(token != NULL)
              {
                strArray[tokenNumber] = (char*)malloc(strlen(token) + 1);
                strcpy(strArray[tokenNumber], token); //token copy
                
                tokenNumber++;
                token = strtok(NULL, delimiter);
              }
              printf("DNS = %s\nIP = %s\n\n",strArray[2],strArray[3]);
              currentLine++;
            }
            else
            {
              //code for other lines
              while(token != NULL)
              {
                strArray[tokenNumber] = (char*)malloc(strlen(token) + 1);
                strcpy(strArray[tokenNumber], token);
                
                if(tokenNumber == 3)
                {
                  time[0] = atof(strArray[tokenNumber]); //time token saved by converting it to float
                }
                if(tokenNumber == 5)
                {
                  time[1] = strtod(strArray[tokenNumber],NULL); //time token saved by converting it to float
                }
                if(tokenNumber == 7)
                {
                  time[2] = strtod(strArray[tokenNumber],NULL); //time token saved by converting it to float
                }
                tokenNumber++;
                token = strtok(NULL, delimiter);
              }
               min = min_time(time, 3); //find min
               max = max_time(time, 3); // find max
               avg = avg_time(time, 3);  // find avg
               printf("DNS = %s\nIP = %s\n",strArray[1],strArray[2]);
               printf( "time 1 = %f,  time 2 = %f,  time 3 = %f\n",time[0], time[1], time[2]);
               printf( "min time = %f\nmax time = %f\navg time = %f\n\n",min, max, avg);
            }
            
       }

       fclose(fp); //close file

       printf(" ** end of mytrace program ** \n");          
}

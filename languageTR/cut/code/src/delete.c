#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#define MAX 100
#define BUFFER_SIZE_1 256
#define BUFFER_SIZE_4 1024

int find_lno(char *fname)
{
	FILE*fptr1;
	fptr1=fopen(fname,"r");
	int lno=0;
	if (fptr1 == NULL)
		return 0;
	char w[BUFFER_SIZE_1];
	printf("\n\tEnter your word : ");
	fgets(w,BUFFER_SIZE_1,stdin);
	w[strlen(w)-1]='\0';

	char str[BUFFER_SIZE_1];
	while(1)
	{
	if(fgets(str,BUFFER_SIZE_1,fptr1)==NULL) // feof returns non zero value if it points to end of file
		return 0;	
	str[strlen(str)-1]='\0';

		char *token=strtok(str,":");
		if(strcmp(token,w)==0)
		{
			return lno;
		}
		lno++;	
	}
	
}
  int delete() 
  {
        int lno, ctr = 0;
        char ch;
        FILE *fptr1, *fptr2;
		char fname[BUFFER_SIZE_1]="../src/";
        char str[BUFFER_SIZE_1], temp[] = "temp.txt";
		
		printf("\n\n\tDelete a specific line :\n");
		printf("\n\t-------------------------------\n"); 
		printf("\n\tInput the file name : ");
		fgets(fname,BUFFER_SIZE_1,stdin);
		fname[strlen(fname)-1]='\0';	
		
        fptr1 = fopen(fname, "r");
        if (!fptr1) 
		{
                printf("\n\tFile not found or unable to open the input file!!\n");
                return 0;
        }
		
        fptr2 = fopen(temp, "w"); // open the temporary file in write mode 
        if (!fptr2) 
		{
                printf("\n\tUnable to open a temporary file to write!!\n");
                fclose(fptr1);
                return 0;
        }
		
        //printf(" Input the line you want to remove  ");
      	lno=find_lno(fname);
		lno++;
	    printf("\n\t%d",lno);	
        // copy all contents to the temporary file except the specific line
        while (!feof(fptr1)) 
        {
            strcpy(str,"\0");
            fgets(str, BUFFER_SIZE_1, fptr1);
            if (!feof(fptr1)) 
            {
                ctr++;
                /* skip the line at given line number */
                if (ctr != lno) 
                {
                    fprintf(fptr2, "%s", str);
                }
            }
        }
        fclose(fptr1);
        fclose(fptr2);
        remove(fname);  		// remove the original file 
        rename(temp, fname); 	// rename the temporary file to original name
/*------ Read the file ----------------*/
   fptr1=fopen(fname,"r"); 
            ch=fgetc(fptr1); 
          printf("\n\tNow the content of the file %s is : \n",fname); 
          while(ch!=EOF) 
            { 
                printf("%c",ch); 
                ch=fgetc(fptr1); 
            }
        fclose(fptr1);
/*------- End of reading ---------------*/
        return 0;

  }

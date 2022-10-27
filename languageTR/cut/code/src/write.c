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

void writefile()
{
	FILE *fw;
	char filename[MAX] = "../src/";
	char sl[BUFFER_SIZE_1];
	char tl[BUFFER_SIZE_1];
	
	printf("\n\tplease enter your source language: ");
	fgets(sl,BUFFER_SIZE_1,stdin);
	sl[strlen(sl)-1]='\0';        //To remove \n from end of string
	
	printf("\n\tplease enter your target language: ");
	fgets(tl,BUFFER_SIZE_1,stdin);
	tl[strlen(tl)-1]='\0';

	strcat(filename,sl);         
	strcat(filename,"_");
	strcat(filename,tl);
	strcat(filename,".txt");
	printf("\t");
	printf("%s",filename);
	
	fw = fopen(filename, "a"); //opening file in append mode
	
	if (fw == NULL)
        	return;

	int flag=1,ct=1;
	char w[BUFFER_SIZE_1];
	
   	while(flag)
   	{	
		switch(ct)
		{
		case 1:	printf("\n\tEnter your source word\n");
				printf("\t");
				fgets(w,BUFFER_SIZE_1,stdin);
				w[strlen(w)-1]='\0';	
				fputs(w, fw); 
				fputs(":", fw);
				break;

		case 2:	printf("\n\tEnter your meaning\n");
				printf("\t");
				fgets(w,BUFFER_SIZE_1,stdin);
				w[strlen(w)-1]='\0';	
				fputs(w, fw); 
				break;
		
		case 3: fputs("\n",fw);
				break;
   	        }
		ct++;
		
		if(ct==4)
			{
			int i;
			printf("\n\t Press 0 to continue or Press 1 for exit");
			fgets(w,BUFFER_SIZE_1,stdin);
			w[strlen(w)-1]='\0';
				if(strcmp(w,"1")==0)
				{
					flag=0;
					break;
				}
				else
				{
					ct=1;
				}
			}

	}
		fclose(fw);
		return;
}

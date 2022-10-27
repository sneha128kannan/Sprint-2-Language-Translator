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
#include "function.h"

char *find(char*word,char *sl,char *tl)
{
	char str[BUFFER_SIZE_4];
    char filename[MAX]="../src/";
	
    strcpy(filename,sl);
	sl[strlen(sl)-1]='\0';
	strcat(filename,"_");
	tl[strlen(tl)-1]='\0';
	strcat(filename,tl);
    strcat(filename,".txt");
	FILE *fw = fopen(filename, "r");

	while(1)
	{
		char *fword,*meaning;
	
		if(fgets(str,BUFFER_SIZE_4,fw)==NULL)
		{
			break;
		}
		else							//to allocate fword and meaning line by line
		{	
			str[strlen(str)-1]='\0';           
			fword=strtok(str,":");
			meaning=strtok(NULL,":");
		}
		
		if(strcmp(word,fword)==0)     //compare word and fword until found
		{
			strcpy(word,meaning);
			return word;
		}
	}
	strcpy(word,"\n\t Source word not found !!");  //word is not present in file
	return word;
}

char *strsave(char *str)
{	
	char*word=strtok(str,":");
	char*sl=strtok(NULL,":");
	char*tl=strtok(NULL,":");	
	
	find(word,sl,tl);
        return word;
}

int main()
{	char ct[MAX];
	printf("\n\t 1) Admin Login \n\t 2) Start Sever \n\t 3) EXIT");
	printf("\n\t Enter your choice : ");
	fgets(ct,MAX,stdin);
	ct[strlen(ct)-1]='\0';
	
	if(strcmp(ct,"1")==0)
	{
		char LoginId[MAX];
        char Password[MAX];  
		
		printf("\n\t ----- Login Successful -----");		
        printf("\n\t Welcome to admin system");
        
		printf("\n\n\t Please Enter your LoginID : ");
        fgets(LoginId,MAX,stdin);
		LoginId[strlen(LoginId)-1]='\0';
		
        printf("\n\t Please Enter your Password : ");
        fgets(Password,MAX,stdin);
		Password[strlen(Password)-1]='\0';
		
        if((strcmp(LoginId,"Admin")==0)&&(strcmp(Password,"admin")==0))
		{        
			while(1)
			{
                printf("\n\t 1) Add new language and words \n\t 2) Append new word and meaning \n\t 3) Edit words \n\t 4) Delete words \n\t 5) EXIT");
				char *choice;
				printf("\n\t Enter your choice : ");
				gets(choice);
				int n=atoi(choice);
				switch(n)
				{
					case 1:	writefile();
							break;
					case 2:	writefile();
							break;
					case 3: modify();
							break;
					case 4: delete();
							break;	
					case 5: return EXIT_SUCCESS;	
				}
			}
		}
		else
			printf("\n\t Invalid Credentials");
		
	}
	

	int fd = 0;
	char buff[BUFFER_SIZE_4];
	char nbuff[BUFFER_SIZE_4];
	
	//Setup Buffer Array
	memset(buff, '0',sizeof(buff));	

	//Create Socket
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if(fd<0)
	{
		perror("Client Error: Socket not created succesfully");
		return 0;
	}

	//Structure to store details
	struct sockaddr_in server; 
	memset(&server, '0', sizeof(server)); 

	//Initialize	
	server.sin_family = AF_INET;    
	server.sin_port = htons(8080); 
    server.sin_addr.s_addr = htonl(INADDR_ANY);
   

	bind(fd, (struct sockaddr*)&server, sizeof(server)); //bound socket to an addr. with bind

	int in;
	
	listen(fd, 10);   //it accepts connection and allocates queue
	
	while(in = accept(fd, (struct sockaddr*)NULL, NULL))  //accept connection req from client
	{		
		int childpid,n;
		if ( (childpid = fork ()) == 0 ) 
		{		
			//close listening socket
			close (fd);
		
			//Clear Zeroes
			bzero(buff,256);
			bzero(nbuff,256);
							
			while ( (n = recv(in, buff, 256,0)) > 0)  
			{
				
				printf("Server Received: %s",buff);
				char *nbuff = strsave(buff);
				
				send(in, nbuff, strlen(nbuff), 0);
		
				bzero(buff,256);
										
			}
			close(in);
			exit(0);
		}

		
	}
}

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

void writefile();
void modify();
void delete();
char*find(char*word,char *sl,char *tl);

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

void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[BUFFER_SIZE_4];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);

    // Fix: If oldWord and newWord are same it goes to infinite loop
    if (!strcmp(oldWord, newWord)) {
        return;
    }


    /*
     * Repeat till all occurrences are replaced. 
     */
    while ((pos = strstr(str, oldWord)) != NULL) //str - hello:word   oldword: hello
    {
        // Backup current line
        strcpy(temp, str); //temp - hello:word

        // Index of current found word
        index = pos - str; //Index - NUll
		
        // Terminate str after word found index
        str[index] = '\0';   //str[0] = NULL

        // Concatenate str with new word 
        strcat(str, newWord);  //str - hi   
         
        // Concatenate str with remaining words after 
        // oldword found index.
        strcat(str, temp+index+owlen);  //str: hi temp+index+owlen: hi:word
		
    }
}


void modify()
{
    /* File pointer to hold reference of input file */
    FILE * fPtr;
    FILE * fTemp;
    char path[MAX] = "../src/";
    
    char buffer[BUFFER_SIZE_4];
    char oldWord[MAX], newWord[MAX];


    printf("\n\tEnter path of source file: "); //english_hindi.txt
    scanf("%s", path);

    printf("\n\tEnter word to replace: "); //hello
    scanf("%s", oldWord);

    printf("\n\tEnter the New word: "); //hola
    scanf("%s", newWord);


    /*  Open all required files */
    fPtr  = fopen(path, "r");
    fTemp = fopen("replace.tmp", "w"); 

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\n\tUnable to open file.\n");
        printf("\n\tPlease check whether file exists and you have read/write privilege.\n");
        return;
    }


    /*
     * Read line from source file and write to destination 
     * file after replacing given word.
     */
    while ((fgets(buffer, BUFFER_SIZE_4, fPtr)) != NULL)
    {
        // Replace all occurrence of word from current line
        replaceAll(buffer, oldWord, newWord);

        // After replacing write it to temp file.
        fputs(buffer, fTemp);
    }


    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);


    /* Delete original source file */
    remove(path);

    /* Rename temp file as original file */
    rename("replace.tmp", path);

    printf("\n\tSuccessfully replaced all occurrences of '%s' with '%s'.", oldWord, newWord);

    return;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dynamicString.h"


char* dynamicString(FILE* stream) {
	char *str,c; 
int i=0,j=1;
str = (char*)malloc(sizeof(char));
while(c!='\n')
{
    c = getc(stream);     //read the input from keyboard standard input
    //re-allocate (resize) memory for character read to be stored
    str = (char*)realloc(str,j*sizeof(char));
    if (c == '\n')
	    break;
    else
    str[i] = c;  //store read character by making pointer point to c
    i++;
    j++;
}
str[i]='\0';   //at the end append null character to mark end of string
printf("The entered string is : %s",str);
return str;
}






#ifndef COMMANDS_H
#define COMMANDS_H


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>   
#include <fcntl.h>


/*---------------Macros----------------------*/
#define STDIN      0
#define STDOUT     1
#define STDERR     2
 
/*-----------Variables Declarations-------------*/

extern  char *token[6];
extern  int token_counter;


/* ----------Functions Declarations------------*/
void  myexit(void);

int pwd(void);

int echo(void);

void help(void);

int cp(void);

int move(void);

#endif







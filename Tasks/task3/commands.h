#ifndef COMMANDS_H
#define COMMANDS_H


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>   
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>


       
/*---------------Macros----------------------*/
#define STDIN      0
#define STDOUT     1
#define STDERR     2
#define PATH_LENGTH     256
 
/*-----------Variables Declarations-------------*/

extern  char *token[6];
extern  int token_counter;
extern char **environ;


/* ----------Functions Declarations------------*/
void  myexit(void);

int pwd(void);

int echo(void);

void myhelp(void);

int mycp(void);

int mymove(void);

int mycd(void);

void envir(void);

int externalCommands(void);

#endif







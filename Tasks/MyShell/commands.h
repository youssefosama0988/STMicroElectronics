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
#define LINE            128
#define COMMAND_LENGTH  512
#define BUILTINCOMMANDS  11
#define TOKENS_NO        15
#define MEMINFO_PATH      "/proc/meminfo"
#define UPTIME_PATH      "/proc/uptime"
 
/*-----------Variables Declarations-------------*/

extern  int token_counter;
extern char **environ;


/* ----------Functions Declarations------------*/
void  myexit(void);

int pwd(void);

int echo(char *token[]);

void myhelp(void);

int mycp(char *token[]);

int mymove(char *token[]);

int mycd(char *token[]);

void envir(char *token[]);

int type(char *token[]);

int myfree(void);

int myUpTime(void);

int redirection(int oldFd , int newFd); 

int handleRedirection(char *token[]);

int externalCommands(char *token[]);

int execute(char *token[]);

#endif







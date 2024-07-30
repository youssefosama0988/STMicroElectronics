#include "commands.h"


int main(){
	int status =0;
	const char *shellmsg = "enter your command :) $ ";
	ssize_t inputsize =0;
	char input[512];
	
	while(1){
		token_counter = 0;
		
                /* read the command after writing the sell message*/
                write( STDOUT , shellmsg , strlen(shellmsg));
                inputsize = read(STDIN , input , 512);
                
                if( input[0] == '\n' )         //check if enter is pressed so skip & keep asking for command
                	continue;
                
               
                /* get the tokens of the command and save it in array , command = token[0]*/
                token[token_counter] = strtok( input , " \n"); 
                while(token[token_counter] != NULL){
                	token_counter++;
                	token[token_counter] = strtok( NULL , " \n");	
                
                }
                
		/* ---------------------check which command is entered by the user------------*/
                /* check if the user enter the exit command, the program will terminates */
                if ( !strcmp(token[0] , "myexit")){
                        myexit();
                        break;
                }
		
		/* check if the user enter the pwd command, the program will print on the terminal the current working directory */
                else if( !strcmp(token[0] , "pwd")){
			status = pwd();
                }
		
		/* check if the user enter the echo command, the program will print the user input command */
		else if(!strcmp(token[0] , "echo")){
			status = echo();	
		}
		
		/* check if the user enter the help command, the program will display the supported commands */
		else if(!strcmp(token[0] , "myhelp")){
			myhelp();	
		}
		
		/* check if the user enter the copy command, call cp function */
		else if(!strcmp(token[0] , "mycp")){
			status = mycp();	
		}
		
		/* check if the user enter the mv command, call move function */
		else if(!strcmp(token[0] , "mymv")){
			status = mymove();	
		}
		
		/* check if the user enter the cd command, call mycd function */
		else if(!strcmp(token[0] , "cd")){
			status = mycd();	
		}
		
		/* in case of Unsupported Command */
		else{
			externalCommands();
		}
		
		memset(input , '\0' , 512);
		
		
		
	}

	return 0 ;
}

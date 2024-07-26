#include "commands.h"


int main(){
	
	while(1){
		token_counter = 0;
		
                /* read the command after writing the sell message*/
                write( STDOUT , shellmsg , strlen(shellmsg));
                inputsize = read(STDIN , input , 100);
                
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
                if ( !strcmp(token[0] , "exit")){
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
		else if(!strcmp(token[0] , "help")){
			help();	
		}
		
		/* check if the user enter the copy command, call cp function */
		else if(!strcmp(token[0] , "cp")){
			status = cp();	
		}
		
		/* check if the user enter the mv command, call move function */
		else if(!strcmp(token[0] , "mv")){
			status = move();	
		}
		/* in case of Unsupported Command */
		else{
			write(STDOUT , " Command Not Found, Please Check 'help' Command\n" , strlen(" Command Not Found, Please Check 'help' Command\n") );
		}
		
		
		

	}

	return 0 ;
}

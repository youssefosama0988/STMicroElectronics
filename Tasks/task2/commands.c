#include "commands.h"

char input[100];
int status =0;
char *token[6];
int token_counter=0;
const char *shellmsg = "enter your command :) $ ";
ssize_t inputsize =0;


void myexit(void){
	write(STDOUT , " Goodbye! :)\n" , strlen(" Goodbye! :)\n") );
}


int pwd(void){

	char cwd[256];
	if( getcwd( cwd , sizeof(cwd) ) != NULL){
		printf("Current Working Directory : %s \n" , cwd);
		return 0 ;
	}	
	else{
	       	perror("Failed! ");
		return -1;
	}	
}


int  echo(void){
	token_counter = 1;
	
	if(NULL == token)
		return -1;
	else{
		
		while(token[token_counter] != NULL){
			printf("%s ",token[token_counter]);
			token_counter++;
		}
		printf("\n");
		memset(input , '\0' , 100);
		return 0;
	}
}



void help(void){
	write(STDOUT , " Supported Commands \n" , strlen(" Supported Commands \n"));
	write(STDOUT , "   1) pwd: print working directory \n" , strlen(" 1) pwd: print working directory \n"));
	write(STDOUT , "   2) echo: print a user input string on stdout \n" , strlen("   2) echo: print a user input string on stdout \n"));
	write(STDOUT , "   3) cp: copy a file to another file (cp sourcePath targetPath)\n" , strlen("   3) cp: copy a file to another file (cp sourcePath targetPath)\n"));
	write(STDOUT , "   4) mv: move a file to another place (mv sourcePath targetPath)\n" , strlen("   4) mv: move a file to another place (mv sourcePath targetPath)\n"));
	write(STDOUT , "   5) exit: print 'Goodbye!' and terminate the shell\n" , strlen("   5) exit: print 'Goodbye!' and terminate the shell\n"));
	write(STDOUT , "   6) help: print all the supported commands \n" , strlen("   6) help: print all the supported commands \n"));				

}

char targetPath[100] , sourcePath[100];   /* GLOBAL to use in MOVE function*/
int cp(void){
	
	int fd_source , fd_target;
	char buffer[200];
	int size = 0;
	char *fileName_target , *fileName_source;
	char *temp;
	
	
	strcpy( targetPath , token[2]);
	strcpy( sourcePath , token[1]);
	
		
	/* get the source file name */
	temp = strtok(token[1] , "/");
	while( temp != NULL){
		fileName_source = temp;
		temp = strtok(NULL , "/"); 
	}
	
	
	/* check if the user enter file name or just the directory -------'case'-------> Dir. so create new file with same name of the source file */
	if( token[2][strlen( token[2] ) - 1] == '/'){
		fileName_target = fileName_source;
		strcat(targetPath , fileName_target );
	}

	/*------------------------------------------------ Start Opening the files ----------------------------------------------------*/
	
	fd_source = open( sourcePath , O_RDONLY);
	
	if(fd_source == -1){
		perror("Failed to open Source ");
		return -1;
	}
	
	/* when the source file opened successfully*/
	else {
		fd_target = open(targetPath , O_CREAT | O_WRONLY | O_TRUNC | O_EXCL , S_IRWXU);
		if(fd_target == -1){
			perror("Failed! ");
			return -1;
		}
		
		/* Start Copying if all is done and the file created or opened*/
		do{
		size = read(fd_source  , buffer , 200);
		write(fd_target , buffer , size);	
		
			if( size == -1){
				perror("Operation is Failed! ");
				return -1;
			}
		}while(size);
			
	}
		
	close(fd_source);
	close(fd_target);
	
	return 0 ;
	
}


int move(void){
	int done = 0;
	/* Call cp Function to copy the content of the file to target*/
	done = cp();
	if(-1 == done){
		write(STDOUT , " Failed to copy" , strlen(" Failed to copy") );
		return  -1;
	}
	
	/* Remove the Source File */
	done = unlink(sourcePath);
	if( -1 == done){
		perror("Deleting Failed ");
		return -1 ;
	}
	return 0 ;
}





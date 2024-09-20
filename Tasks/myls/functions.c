
#include "main.h"

static int CountDigits(long long num);

/*=========================================================================================================================================================*/



/*=========================================================================================================================================================*/

void NormalPrint(MaxSizes_t* max_sizes , CombinedStat_t* Entries , Options_t* options){
	struct winsize window;
	char colored_name[268];
	short row=0 , col=0;
	int mode;
	int i = 0;
	
	ioctl( 0, TIOCGWINSZ, &window );
	
	while( strcmp(Entries->name , "DONE") != 0 ){
		mode = Entries->Files.st_mode;
		
		if( (!options->all_opt) && ( strcmp(Entries->name , ".") == 0 || strcmp(Entries->name , "..") == 0 ) ){						
			Entries++;
			continue;
		}
		
		ColoredFileName(mode , colored_name , Entries->name);
		
		/* check on inode_opt flag to print inode number */
		if(options->inode_opt){
			col = window.ws_col / (max_sizes->file_inode + max_sizes->file_name) ;
			col =  (window.ws_col - col) / (max_sizes->file_inode + max_sizes->file_name);
			
			if(i == 0){
				printf("%*li %s ", max_sizes->file_inode , Entries->Files.st_ino  ,  colored_name);
				i++;
		
			}
			else if(i == col){
				printf("\n");
				i=0;
			}
			else{
				printf("%*li %s ", (int)(max_sizes->file_inode + (max_sizes->file_name - strlen((Entries -1 )->name) )) , Entries->Files.st_ino ,  colored_name);
				i++;
			
			}

		}
		else{
			col = window.ws_col / max_sizes->file_name ;
			col =  (window.ws_col - col) / max_sizes->file_name;
			
			if(i == 0){
				printf("%s " ,  colored_name);
				i++;
			}
			else if(i == col){
				printf("\n");
				i=0;
			}
			else{
				printf("%*s%s ", (int)(max_sizes->file_name - strlen((Entries -1 )->name) ) , "" ,  colored_name);
				i++;
			}
		}
		
		Entries++;
	}
	printf("\n");

}

/*=========================================================================================================================================================*/

void PrintLongFormat(char *dir_path , MaxSizes_t* max_sizes , CombinedStat_t* Entries , Options_t* options){
	char str[11];
	int mode;
	struct group* grp;
	struct passwd* pwd;
	long time;
	char c_time[128];
	char inode[16];
	char colored_name[268];
	char *symlink_buf;			//to save the file name in case of symlink.
        ssize_t nbytes, bufsiz;
        char *path;         
	
	if(Entries == NULL ){
		printf("NULL pointer is passed to Print Long Format\n");
		exit(-1);
	}
	
	while(strcmp(Entries->name , "DONE") != 0){
		
		strcpy(str, "----------");
		mode = Entries->Files.st_mode;
		grp = getgrgid(Entries->Files.st_gid);
		pwd = getpwuid(Entries->Files.st_uid);
		if(options->c_opt){
			time = Entries->Files.st_ctime;
		}
		else if(options->u_opt){
			time = Entries->Files.st_atime;
		}
		else if(options->t_opt){
			time = Entries->Files.st_mtime;
		}
		else{
			time = Entries->Files.st_ctime;
		}
		
		strcpy(c_time , ctime(&time));
		strcpy(c_time , strtok(c_time ,"\n")) ;
		
		strcpy(inode ,"");
		
		
		
		//File Type
		if(S_ISREG(mode)){
		 	str[0] = '-';
		 	strcpy(colored_name , Entries->name);		//default.
		 	
		 	//check if file is Executable so make it green.
			if( ((mode & S_IXUSR) == S_IXUSR) && ((mode & S_IXOTH) == S_IXOTH) && ((mode & S_IXGRP) == S_IXGRP) ){
				strcpy(colored_name , "\033[1;32m");		//green color
				strcat(colored_name , Entries->name);
				strcat(colored_name , "\033[0m");
			}
		 }	
		else if(S_ISDIR(mode)){
		  	str[0] = 'd';
			strcpy(colored_name , "\033[1;34m");		//blue color	
			strcat(colored_name , Entries->name);
			strcat(colored_name , "\033[0m");		
		}
		else if(S_ISCHR(mode)){
			str[0] = 'c';
			strcpy(colored_name , "\033[1;40;33m");		//orange color
			strcat(colored_name , Entries->name);
			strcat(colored_name , "\033[0m");
			
		}	
		else if(S_ISBLK(mode)){
		 	str[0] = 'b';
			strcpy(colored_name , "\033[1;40;33m");		//orange color
			strcat(colored_name , Entries->name);
			strcat(colored_name , "\033[0m");
				
		}
		else if(S_ISFIFO(mode)){
			str[0] = 'p';
			strcpy(colored_name , "\033[1;40;33m");		//orange color
			strcat(colored_name , Entries->name);
			strcat(colored_name , "\033[0m");
			
		}
		else if(S_ISLNK(mode)){
			str[0] = 'l';
			strcpy(colored_name , "\033[1;36m");		//cyan color
			strcat(colored_name , Entries->name);
			strcat(colored_name , "\033[0m");
		}	
		else if(S_ISSOCK(mode)){
			str[0] = 's';
			strcpy(colored_name , "\033[1;35m");		//purple color
			strcat(colored_name , Entries->name);
			strcat(colored_name , "\033[0m");
		}
		else{
			strcpy(colored_name , Entries->name);		//default.
		}
		
		
		//owner permissions
           	if((mode & S_IRUSR) == S_IRUSR) str[1] = 'r';
		if((mode & S_IWUSR) == S_IWUSR) str[2] = 'w';
		if((mode & S_IXUSR) == S_IXUSR) str[3] = 'x';
		//group permissions
		if((mode & S_IRGRP) == S_IRGRP) str[4] = 'r';
		if((mode & S_IWGRP) == S_IWGRP) str[5] = 'w';
		if((mode & S_IXGRP) == S_IXGRP) str[6] = 'x';
		//others  permissions
		if((mode & S_IROTH) == S_IROTH) str[7] = 'r';
		if((mode & S_IWOTH) == S_IWOTH) str[8] = 'w';
		if((mode & S_IXOTH) == S_IXOTH) str[9] = 'x';
		//special  permissions
		if((mode & S_ISUID) == S_ISUID) str[3] = 's';	//set-user-ID bit
		if((mode & S_ISGID) == S_ISGID) str[6] = 's';	//set-group-ID bit	
		if((mode & S_ISVTX) == S_ISVTX) str[9] = 't'; 	//sticky bit
		
		if( (!options->all_opt) && ( strcmp(Entries->name , ".") == 0 || strcmp(Entries->name , "..") == 0 ) ){						
			Entries++;
			continue;
		}
			
		if(options->inode_opt)
			sprintf(inode , "%ld" , Entries->Files.st_ino);
		
			
		printf("%*s %s %3li %-*s %-*s %*li %-*s %s" ,
			options->inode_opt ? max_sizes->file_inode : 0 ,      
			inode,
			str,   			//permissions
			Entries->Files.st_nlink ,
			max_sizes->file_owner ,
			pwd->pw_name ,		
			max_sizes->file_gr ,
			grp->gr_name ,	
			max_sizes->file_size ,
			Entries->Files.st_size ,
			(int)strlen(c_time) ,
			c_time ,
			colored_name 
		);
		
		if(S_ISLNK(mode)){
			/* Add one to the link size, so that we can determine whether
	   		   the symlink_buffer returned by readlink() was truncated. */
	  		 bufsiz = Entries->Files.st_size + 1;
			
			/* Some magic symlinks under (for example) /proc and /sys
              		report 'st_size' as zero. In that case, take PATH_MAX as a "good enough" estimate. */

			if (Entries->Files.st_size == 0)
				bufsiz = PATH_MAX;
				
			symlink_buf = (char *)malloc(bufsiz);
			
			if (symlink_buf == NULL) {
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			/*get the path of the file */
			path = (char *)malloc(strlen(dir_path) + 1 + strlen(Entries->name) + 1);     // one more for "/" -->  "dir + / + Name + Null termination"
			
			if(NULL == path){
				printf("Allocation failed\n");
				exit(-1);
			}
			
			sprintf(path , "%s%s%s" , dir_path , "/" , Entries->name);
			nbytes = readlink(path , symlink_buf, bufsiz);
			free(path);
			
			if (nbytes == -1) {
				perror("readlink");
				exit(EXIT_FAILURE);
			}
			else{
				printf("\033[1;37m→\033[0m %s\n" , symlink_buf);
				
				free(symlink_buf);
			}

		}
		else
			printf("\n");
			
		Entries++;
		
	}
	
}

/*=========================================================================================================================================================*/

void PrintOneLine(MaxSizes_t* max_sizes , CombinedStat_t* Entries , Options_t* options){
	char colored_name[268];
	int mode;
	
	while( strcmp(Entries->name , "DONE") != 0 ){
		mode = Entries->Files.st_mode;
		
		if( (!options->all_opt) && ( strcmp(Entries->name , ".") == 0 || strcmp(Entries->name , "..") == 0 ) ){						
			Entries++;
			continue;
		}
		
		ColoredFileName(mode , colored_name , Entries->name);
		
		/* check on inode_opt flag to print inode number */
		if(options->inode_opt){
			printf("%*li %s\n", max_sizes->file_inode , Entries->Files.st_ino , colored_name);
		}
		else{
			printf("%s\n", colored_name);
		}
		
		Entries++;
	}
}

/*=========================================================================================================================================================*/

MaxSizes_t* GetLstat(char *dir_path , CombinedStat_t Entries[]){
	int i = 0;
	int rv;
	char *path;
	struct group* grp;
	struct passwd* pwd;
	MaxSizes_t* max_sizes;
	
	
	max_sizes = (MaxSizes_t *)malloc(sizeof(MaxSizes_t));
	
	if(max_sizes != NULL){
		max_sizes->file_size=0  ;
		max_sizes->file_name=0  ;
		max_sizes->file_gr=0    ; 
		max_sizes->file_owner=0 ;
		max_sizes->file_inode=0 ;
		max_sizes->file_time=0  ;
	}
	else{
		printf("Allocation failed for struct\n");
		exit(-1);
	}
	
		
	while(strcmp(Entries[i].name , "DONE") != 0){
		/*get the path of the file */
		path = (char *)malloc(strlen(dir_path) + 1 + strlen(Entries[i].name) + 1);     // one more for "/" -->  "dir + / + Name + Null termination"
		
		if(NULL == path){
			printf("Allocation failed\n");
			exit(-1);
		}
		else{
			
			sprintf(path , "%s%s%s" , dir_path , "/" , Entries[i].name);
			rv = lstat(path , &(Entries[i].Files));
			if(-1 == rv){
				perror("lstat");
				
			}
			else{	
			
			/* extract the max width of the fields */
				grp = getgrgid(Entries[i].Files.st_gid);
				pwd = getpwuid(Entries[i].Files.st_uid);

				if(max_sizes->file_size < CountDigits(Entries[i].Files.st_size) ){
					max_sizes->file_size = CountDigits(Entries[i].Files.st_size);
				}
				if(max_sizes->file_name < strlen(Entries[i].name)){
					max_sizes->file_name = strlen(Entries[i].name);
				}
				if(max_sizes->file_gr < strlen(grp->gr_name)){
					max_sizes->file_gr = strlen(grp->gr_name);
				}
				if(max_sizes->file_owner < strlen(pwd->pw_name)){
					max_sizes->file_owner = strlen(pwd->pw_name);
				}
				if(max_sizes->file_inode < CountDigits(Entries[i].Files.st_ino) ){
					max_sizes->file_inode = CountDigits(Entries[i].Files.st_ino) + 1;      // 1 for allignment 
				}
				if(max_sizes->file_time < CountDigits(Entries[i].Files.st_ctime) ){
					max_sizes->file_time = CountDigits(Entries[i].Files.st_ctime);
				}	
			}
			free(path);
		}
			
		i++;
	}
	
	return max_sizes;
}

/*=========================================================================================================================================================*/

int GetEntries(char *dirName,CombinedStat_t Entries[]){
	DIR *directory;
	struct dirent* entry;
	int i = 0;
	
	errno = 0;
	
	directory = opendir(dirName);
	if(NULL == directory){
		printf("Failed to open %s directory\n", dirName);
		perror("open");
		return 0;
	}
	else{	
		/* get the entries of the directory */
		while( (entry = readdir(directory)) != NULL ){
			strcpy(Entries[i].name , entry->d_name);
			i++;
		}
		strcpy(Entries[i].name , "DONE");
		
		if(errno != 0){
			perror("Read Dir");
		}
	
		if(closedir(directory) == -1)
			perror("close");	
	}	
	return i;	//return no. of entries 
}

/*=========================================================================================================================================================*/

void ColoredFileName(int mode , char *colored_name , char *file_name){

	/*-----------File Type---------*/
		if(S_ISREG(mode)){
		 	strcpy(colored_name , file_name);		//default.
		 	
		 	//check if file is Executable so make it green.
			if( ((mode & S_IXUSR) == S_IXUSR) && ((mode & S_IXOTH) == S_IXOTH) && ((mode & S_IXGRP) == S_IXGRP) ){
				strcpy(colored_name , "\033[1;32m");		//green color
				strcat(colored_name , file_name);
				strcat(colored_name , "\033[0m");
			}
		 }	
		else if(S_ISDIR(mode)){
			strcpy(colored_name , "\033[1;34m");		//blue color	
			strcat(colored_name , file_name);
			strcat(colored_name , "\033[0m");		
		}
		else if(S_ISCHR(mode)){
			strcpy(colored_name , "\033[1;40;33m");		//orange color
			strcat(colored_name , file_name);
			strcat(colored_name , "\033[0m");
			
		}	
		else if(S_ISBLK(mode)){
			strcpy(colored_name , "\033[1;40;33m");		//orange color
			strcat(colored_name , file_name);
			strcat(colored_name , "\033[0m");
				
		}
		else if(S_ISFIFO(mode)){
			strcpy(colored_name , "\033[1;40;33m");		//orange color
			strcat(colored_name , file_name);
			strcat(colored_name , "\033[0m");
			
		}
		else if(S_ISLNK(mode)){
			strcpy(colored_name , "\033[1;36m");		//cyan color
			strcat(colored_name , file_name);
			strcat(colored_name , "\033[0m");
		}	
		else if(S_ISSOCK(mode)){
			strcpy(colored_name , "\033[1;35m");		//purple color
			strcat(colored_name , file_name);
			strcat(colored_name , "\033[0m");
		}
		else{
			strcpy(colored_name , file_name);		//default.
		}

}

/*=========================================================================================================================================================*/

int Cmp_Ctime(const void *p1, const void *p2){

	return -( ((CombinedStat_t *)p1)->Files.st_mtime - ((CombinedStat_t *)p2)->Files.st_mtime );
}

/*=========================================================================================================================================================*/

int Cmp_Mtime(const void *p1, const void *p2){

	return -( ((CombinedStat_t *)p1)->Files.st_mtime - ((CombinedStat_t *)p2)->Files.st_mtime );
}

/*=========================================================================================================================================================*/


int Cmp_Atime(const void *p1, const void *p2){

	return -( ((CombinedStat_t *)p1)->Files.st_atime - ((CombinedStat_t *)p2)->Files.st_atime );
}

/*=========================================================================================================================================================*/

int cmpstringp(const void *p1, const void *p2){
	char str1[strlen(((CombinedStat_t *)p1)->name)] ;
	char str2[strlen(((CombinedStat_t *)p2)->name)];
	
	strcpy(str1 , ((CombinedStat_t *)p1)->name );
	strcpy(str2 , ((CombinedStat_t *)p2)->name );
	
	for (int i = 0; str1[i] != '\0'; i++) {
		str1[i] = tolower(str1[i]);
	}
	for (int i = 0; str2[i] != '\0'; i++) {
		str2[i] = tolower(str2[i]);
	}

	return strcoll( str1 ,  str2);
}

/*=========================================================================================================================================================*/

static int CountDigits(long long num){
    int count = 0;
    if (num == 0) return 1; //Special case for 0
    
    //Handle negative numbers
    if (num < 0) num = -num;

    while (num > 0){
        num /= 10;
        count++;
    }
    
    return count;
}







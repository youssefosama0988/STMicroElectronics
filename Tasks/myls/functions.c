
#include "main.h"

static int CountDigits(int num);
/*=========================================================================================================================================================*/

void PrintOneLine(MaxSizes_t* max_sizes , struct dirent Entries[] , Options_t* options){
	int i = 0;
	while( strcmp(Entries[i].d_name , "DONE") != 0 ){
		
		if(options->inode_opt){
			printf("%*li %s\n",max_sizes->file_inode , Entries[i].d_ino , Entries[i].d_name);
		}
		else{
			printf("%s\n",Entries[i].d_name);
		}
		i++;
	}
}

/*=========================================================================================================================================================*/

MaxSizes_t* GetLstat(char *dir_path , struct dirent Entries[] , struct stat Files[]){
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
	}
	else{
		printf("Allocation failed for struct\n");
		exit(-1);
	}
	
		
	while(strcmp(Entries[i].d_name , "DONE") != 0){
		/*get the path of the file */
		path = (char *)malloc(strlen(dir_path) + 1 + strlen(Entries[i].d_name) + 1);     // one more for "/" -->  "dir + / + Name + Null termination"
		
		if(NULL == path){
			printf("Allocation failed\n");
			exit(-1);
		}
		else{
			//printf("in Lstat %p\n" , Entries[i]);
			sprintf(path , "%s%s%s" , dir_path , "/" , Entries[i].d_name);
			//printf("path %s\n" , path);
			//printf("after %s\n" , Entries[i].d_name);
			rv = lstat(path , &Files[i]);
			if(-1 == rv){
				perror("lstat");
				
			}
			else{	
			
			/* extract the max width of the fields */
				grp = getgrgid(Files[i].st_gid);
				pwd = getpwuid(Files[i].st_uid);

				if(max_sizes->file_size < CountDigits(Files[i].st_size) ){
					max_sizes->file_size = CountDigits(Files[i].st_size);
				}
				if(max_sizes->file_name < strlen(Entries[i].d_name)){
					max_sizes->file_name = strlen(Entries[i].d_name);
				}
				if(max_sizes->file_gr < strlen(grp->gr_name)){
					max_sizes->file_gr = strlen(grp->gr_name);
				}
				if(max_sizes->file_owner < strlen(pwd->pw_name)){
					max_sizes->file_owner = strlen(pwd->pw_name);
				}
				if(max_sizes->file_inode < CountDigits(Files[i].st_ino) ){
					max_sizes->file_inode = CountDigits(Files[i].st_ino) + 1;      // 1 for allignment 
				}	
			}
			free(path);
		}
			
		i++;
	}
	
	return max_sizes;
}

/*=========================================================================================================================================================*/

int GetEntries(char *dirName,struct dirent Entries[]){
	DIR *directory;
	struct dirent* entry;
	int i = 0;
	
	errno = 0;
	
	directory = opendir(dirName);
	if(NULL == directory){
		printf("Failed to open %s directory\n", dirName);
		perror("open");
	}
	else{	
		/* get the entries of the directory */
		while( (entry = readdir(directory)) != NULL ){
			Entries[i] = *entry;
			//printf("in ENTRY %p\n" , Entries[i]);
			i++;
		}
		strcpy(Entries[i].d_name , "DONE");
		
		if(errno != 0){
			perror("Read Dir");
		}
	
		if(closedir(directory) == -1)
			perror("close");	
	}	
	return i;	//return no. of entries 
}

/*=========================================================================================================================================================*/

static int CountDigits(int num){
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







#include "main.h"


int main(int argc , char** argv){
	int opt;
	int rv;
	struct dirent Entries[2048];
	MaxSizes_t* max_sizes;
	struct stat Files[2048];
	int entries_number = 0;
	int i = 0;
	Options_t options = {
	 	.all_opt 	= false ,
		.long_format_opt= false ,
		.c_opt 		= false ,
		.t_opt 		= false ,
		.u_opt 	     	= false ,
		.inode_opt    	= false ,
		.f_opt 	    	= false ,
		.oneLine_opt	= false ,
	};
		
	/* Parsing the Options */
	while( (opt = getopt(argc, argv, "latucifd1")) != -1){
	
		switch (opt){
			case 'a': options.all_opt         = true;       break;
			case 'l': options.long_format_opt = true;       break;
			case 't': options.t_opt 	  = true;       break;
			case 'u': options.u_opt		  = true;  	break;
			case 'c': options.c_opt 	  = true;       break;
			case 'i': options.inode_opt       = true;       break;
			case 'f': options.f_opt 	  = true;       break;
			case '1': options.oneLine_opt 	  = true;       break;
			
			case ':': printf("Missing Argument for %c option\n" , optopt);		break;
			case '?': printf("'%c' option is Unsupported \n" , optopt);		break;
			default:  printf("Unexpected case in switch()\n"); return -1;
		}
	}
	
	/* check if the first non-option argument is NULL --> print CWD "."*/
	if(argv[optind] == NULL ){
		printf("Listing Current working Directory\n");
		
		/* get the entry of the directory and save it in the array and return no. of entries */
		entries_number = GetEntries(".",Entries);
		
		qsort(Entries, entries_number, sizeof(struct dirent), cmpstringp);
		max_sizes = GetLstat("." , Entries , Files);
		
		if(options.oneLine_opt){
			PrintOneLine(max_sizes , Entries , Files , &options);
		}
		else if(options.long_format_opt){
			PrintLongFormat("." , max_sizes , Entries , Files , &options);
		}
		
	}
	
	while(argv[optind] != NULL){
	
		printf("\nListing '%s' Directory\n", argv[optind]);
		
		/* get the entry of the directory and save it in the array and return no. of entries */
		entries_number = GetEntries( argv[optind] , Entries);
		
		if(entries_number){
			if(options.f_opt){
				//don't sort except with -c option
			}
			else if(options.t_opt){
				//sorting by time with 
				
				
			}
			else{
				qsort(Entries, entries_number, sizeof(struct dirent), cmpstringp);	//sorting by name.
			}
			
			/* get lstat structures and return struct contains the maximum width of each field */
			max_sizes = GetLstat(argv[optind] , Entries , Files);
			
			if(options.oneLine_opt){
				PrintOneLine(max_sizes , Entries , Files , &options);
			}
			else if(options.long_format_opt){
				PrintLongFormat(argv[optind] , max_sizes , Entries , Files , &options);
			}
			else{
				NormalPrint(max_sizes , Entries , Files , &options);
			
			}
			
			
		}
		else{
			printf("No entries!\n");
		
		}
		
		/* get the next directory if exist*/
		optind++;
		free(max_sizes);
	}
	return 0;		
}






#include <stdio.h>
#include <elf.h>

#define FILE_PATH "/home/youssef/Desktop/STMicroElectronics/Tasks/task1/Program1/programexe"

int main(){
	char *type[] = {"An Unknown type","A reloctable file","An executable file","A shared object","A core file"};

	FILE *myelf = fopen( FILE_PATH , "r" );
	Elf64_Ehdr myheader;
	fread( &myheader , sizeof(Elf64_Ehdr) , 1 , myelf);
	
	printf("ELF Header : \n");
	printf(" Magic :   %2x %2x %2x %2x %2x %2x %2x %2x %2x 00 00 00 00 00 00 00 \n" , ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3,myheader.e_ident[EI_CLASS], myheader.e_ident[EI_DATA], myheader.e_ident[EI_VERSION], myheader.e_ident[EI_OSABI] , myheader.e_ident[EI_ABIVERSION] );
	                /*---------------Class------------------- */
	if( ELFCLASSNONE == myheader.e_ident[EI_CLASS])
		printf(" Class :                              This class is invalid.\n");
	else if( ELFCLASS32== myheader.e_ident[EI_CLASS])
                printf(" Class :                              ELF32\n");
	else if( ELFCLASS64== myheader.e_ident[EI_CLASS])
                printf(" Class :                              ELF64\n");
	else printf("  \n ");

                       /*---------------Data------------------------*/
	if( ELFDATA2LSB  ==myheader.e_ident[EI_DATA])
		printf(" Data :                               2's complement, little endian \n");
	else if( ELFDATA2LSB  ==myheader.e_ident[EI_DATA])
                printf(" Data :                               2's complement, big  endian \n");	
	else printf(" Data :                                  Unknown Data Format \n");
	             
       			/*---------------Version------------------- */
	if( EV_CURRENT == myheader.e_ident[EI_VERSION])
		printf(" Version :                            1 (current) \n");
	else printf(" Version :                               Invalid version \n");

			/*-------------OS/ABI-----------------------*/
	if( ELFOSABI_LINUX  == myheader.e_ident[EI_OSABI] )
		printf(" OS/ABI :                             UNIX - GNU \n");
	else if( ELFOSABI_ARM  == myheader.e_ident[EI_OSABI] )
                printf(" OS/ABI :                             ARM Architecture ABI \n");
	else printf(" OS/ABI :                                Unsupported \n");

			/*------------ABI Version-------------------*/
	printf(" ABI Version :                        %d \n" , myheader.e_ident[EI_ABIVERSION]);
      
         	/*---------------------------------------------------------------------------*/

	printf(" Type:                                %s \n",type[myheader.e_type]);

	if(myheader.e_machine == EM_X86_64)
		printf(" Machine : 			      AMD x86-64 \n");
	else if(myheader.e_machine == EM_ARM)
		printf(" Machine : 			      Advanced RISC Machines \n");
	else printf("Unsupported Machine \n");

	printf(" Version :			      0x%x \n",myheader.e_version);
	printf(" Entry point address :     	      0x%lx \n" ,myheader.e_entry);
        printf(" Start Program Headers :   	      %ld (bytes into file) \n" ,myheader.e_phoff);
        printf(" Start of Section Headers : 	      %ld (bytes into file) \n" ,myheader.e_shoff);
        printf(" Flags :                    	      0x%x \n" ,myheader.e_flags);
        printf(" Size of this Headers :     	      %d (bytes) \n" ,myheader.e_ehsize);
	printf(" Size of program Headers :  	      %d (bytes) \n" ,myheader.e_phentsize);
	printf(" Number of program Headers :	      %d  \n" ,myheader.e_phnum);
	printf(" Size of section Headers : 	      %d (bytes) \n" ,myheader.e_shentsize);
	printf(" Number of section Headers :	      %d  \n" ,myheader.e_shnum);
	printf(" Section header string table index :  %d  \n" ,myheader.e_shstrndx);

	
		
	fclose(myelf);
	return 0 ;
}	

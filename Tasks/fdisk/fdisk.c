#include "fdisk.h"


int main(int argc , char**argv){
	
	char buff[BLOCK_SIZE];
	char buff2[BLOCK_SIZE];
	int fd;
	ssize_t read_size;
	PartitionEntry *partition_entry_ptr;
	PartitionEntry *extended_partition_ptr = NULL;
	GPTPartitionEntry *gpt_ptr;
	uint64_t absolute_lba;
	int i = 0;
	uint64_t offset;
	
	if(2 != argc){
		printf("Arguments Invalid\n");
		return -1;
	}

	fd = open(argv[1] , O_RDONLY);
	
	if(-1 == fd){
		perror("open ");
		return -1;
	}
	
	read_size = read(fd , buff , BLOCK_SIZE);
	
	if(read_size <= 0){
		perror("read ");
		return -1;
	}
	
	partition_entry_ptr = (PartitionEntry *)&buff[446];
	
	/*Handle MBR */	
	if(partition_entry_ptr[i].type != 0xee){
		printf("\033[1m%-10s %-10s %-10s %-10s %-10s %-10s %-10s %s\033[0m\n","Device","Boot","Start","End","Sectors","Size","Id","Type");
		
		for(i=0 ;i<4; i++){
			if(partition_entry_ptr[i].type == 0x00 || partition_entry_ptr[i].type == 0xee ){
				break;
			}
			
			printf("%s%i %-11c %-10u %-10u %-10u %u%s %10x",
			argv[1],i+1,
			partition_entry_ptr[i].status == 0x80? '*':' ',
			partition_entry_ptr[i].lba,
			partition_entry_ptr[i].lba + partition_entry_ptr[i].sector_count - 1,
			partition_entry_ptr[i].sector_count,
			(uint32_t)(((uint64_t)partition_entry_ptr[i].sector_count * 512)/(1024 * 1024 * 1024)),
			"G",
			partition_entry_ptr[i].type
			);
			
			if( partition_entry_ptr[i].type == 0x83){
				printf("%14s","Linux\n");
			}
			else if( partition_entry_ptr[i].type == 0x05){
				printf("%14s","Extended\n");
				extended_partition_ptr = (partition_entry_ptr+i);
			}
			else
				printf("\n");
			
		}
	}	
	/*Support GPT*/
	if(partition_entry_ptr[i].type == 0xee){
		i=0;
		printf("\033[1m%-10s %-10s %-10s %-10s %-10s %s\033[0m\n","Device","Start","End","Sectors","Size","Type");
		offset = (uint64_t) 2 * 512;             //skip first 2 blocks
		offset = lseek(fd , offset , SEEK_SET);
		
		if(-1 == offset){
			perror("lseek ");
			return -1;
		}
		
		read_size = read(fd , buff2 , 128);
	
		if(read_size <= 0){
			perror("read ");
			return -1;
		}
		
		gpt_ptr = (GPTPartitionEntry *)&buff2[0];
		while(gpt_ptr->first_lba != 0x0){
			
			printf("%s%i  %-10lu %-10lu %-10lu %lu\n",
				argv[1],i+1,
				gpt_ptr->first_lba,
				gpt_ptr->last_lba,
				gpt_ptr->last_lba - gpt_ptr->first_lba + 1,
				(uint64_t)((gpt_ptr->last_lba - gpt_ptr->first_lba + 1)*512)/(1024*1024*1024)
			);
			read_size = read(fd , buff2 , 128);
	
			if(read_size <= 0){
				perror("read ");
				return -1;
			}
			gpt_ptr = (GPTPartitionEntry *)&buff2[0];	
			i++;
		}	
	}
	
	
	if(NULL != extended_partition_ptr){
		
		i = 4;
		offset = (uint64_t)extended_partition_ptr->lba * 512 ;
		offset = lseek(fd , offset , SEEK_SET);
		
		if(-1 == offset){
			perror("lseek ");
			return -1;
		}
		
		read_size = read(fd , buff2 , BLOCK_SIZE);
	
		if(read_size <= 0){
			perror("read ");
			return -1;
		}
		
		partition_entry_ptr = (PartitionEntry *)&buff2[446];
		
		printf("%s%i %-11c %-10u %-10u %-10u %u%s %10x",
			argv[1],i+1,
			partition_entry_ptr->status == 0x80? '*':' ',
			(partition_entry_ptr->lba + extended_partition_ptr->lba),
			partition_entry_ptr->lba + extended_partition_ptr->lba + partition_entry_ptr->sector_count - 1,
			partition_entry_ptr->sector_count,
			(uint32_t)(((uint64_t)partition_entry_ptr->sector_count * 512)/(1024 * 1024 * 1024)),
			"G",
			partition_entry_ptr->type
		);
		
		if( partition_entry_ptr->type == 0x83){
			printf("%14s","Linux\n");
		}
		else if( partition_entry_ptr->type == 0x05){
			printf("%14s","Extended\n");
		}
		else
			printf("\n");
			
		absolute_lba = extended_partition_ptr->lba;	
		while((partition_entry_ptr+1)->type != 0x00){
			absolute_lba += (partition_entry_ptr+1)->lba;
			i++;
			offset = (uint64_t)absolute_lba * 512 ;
			offset = lseek(fd , offset , SEEK_SET);
			
			if(-1 == offset){
				perror("lseek ");
				return -1;
			}
			
			read_size = read(fd , buff2 , BLOCK_SIZE);
		
			if(read_size <= 0){
				perror("read ");
				return -1;
			}
			
			partition_entry_ptr = (PartitionEntry *)&buff2[446];
			
			printf("%s%i %-11c %-10lu %-10lu %-10u %u%s %10x",
				argv[1],i+1,
				partition_entry_ptr->status == 0x80? '*':' ',
				(partition_entry_ptr->lba + absolute_lba),
				partition_entry_ptr->lba + absolute_lba + partition_entry_ptr->sector_count - 1,
				partition_entry_ptr->sector_count,
				(uint32_t)(((uint64_t)partition_entry_ptr->sector_count * 512)/(1024 * 1024 * 1024)),
				"G",
				partition_entry_ptr->type
			);
			if( partition_entry_ptr->type == 0x83){
				printf("%14s","Linux\n");
			}
			else if( partition_entry_ptr->type == 0x05){
				printf("%14s","Extended\n");
			}
			else
				printf("\n");
				
			absolute_lba = 	extended_partition_ptr->lba;

		}			
	}
	
	close(fd);
	return 0;	
}	

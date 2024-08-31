#include "fdisk.h"


int main(int argc , char**argv){
	
	char buff[BLOCK_SIZE];
	char buff2[BLOCK_SIZE];
	int fd;
	ssize_t read_size;
	PartitionEntry *partition_entry_ptr;
	PartitionEntry *extended_partition_ptr = NULL;
	int i = 0;
	off_t lseek_offset;
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
	printf("\033[1m%-10s %-10s %-10s %-10s %-10s %-10s %-10s %s\033[0m\n","Device","Boot","Start","End","Sectors","Size","Id","Type");
	
	for(i=0 ;i<4; i++){
		if(partition_entry_ptr[i].type == 0x00){
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
	}
	
	close(fd);
	return 0;	
}	

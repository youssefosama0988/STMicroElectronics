#ifndef FDISK_H
#define FDISK_H 

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>


#define BLOCK_SIZE   	512
#define GBYTE      	(1024*1024*1024)
#define MBYTE 		(1024*1024)


typedef struct{

	uint8_t status;
	uint8_t first_chs_address[3];
	uint8_t type;
	uint8_t last_chs_address[3];
	uint32_t lba;
	uint32_t sector_count; 

}PartitionEntry;

typedef struct {
    uint8_t  partition_type_guid[16];
    uint8_t  unique_partition_guid[16];
    uint64_t first_lba;
    uint64_t last_lba;
    uint64_t attributes;
    uint16_t partition_name[36];
}GPTPartitionEntry;



#endif

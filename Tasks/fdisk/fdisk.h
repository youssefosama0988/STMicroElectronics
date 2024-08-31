#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>


#define BLOCK_SIZE   512



typedef struct{

	uint8_t status;
	uint8_t first_chs_address[3];
	uint8_t type;
	uint8_t last_chs_address[3];
	uint32_t lba;
	uint32_t sector_count; 

}PartitionEntry;

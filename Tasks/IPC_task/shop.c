#include "system.h"

void initialize_inventory(Item_t * inventory, char *file_name);

int main()
{

	int fd;
	Item_t *inventory;

	// Create the inventory file
	fd = open(INVENTORY, O_RDWR | O_CREAT , 0644);
	if (fd == -1) {
		perror("Opening the Shop failed :( ");
		return -1;
	}

	if (ftruncate(fd, SHOP_SIZE) != 0) {	//set the inventory file to that size 
		perror("ftruncate ");
		return -1;
	}

	//Map the file into memory
	inventory =
	    mmap(NULL, SHOP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if (inventory == MAP_FAILED) {
		perror("Error mapping file");
		close(fd);
		return -1;
	}

	/*Initialize the Inventory */
	write_lock(fd);
	initialize_inventory(inventory, INIT_STOCK);
	unlock(fd);
	
	/*periodic printing of inventory*/
	while (1) {

	/***********************lock the file***************************/
		read_lock(fd);

	/************************** Show the stock *********************/
		for (int i = 0; i < NO_OF_ITEMS; i++) {
			printf("Bar Code: %d, Name: %s, Price: %.2f, Count: %d\n",
			       inventory[i].bar_code, inventory[i].name,
			       inventory[i].price, inventory[i].count);
		}
		printf("===============================================\n");

	/*************************unlock the file***********************/
		unlock(fd);

		sleep(3);
	}

	//Unmap the memory
	if (munmap(inventory, SHOP_SIZE) == -1) {
		perror("Error unmapping file");
		return -1;
	}

	close(fd);

	return 0;
}



void initialize_inventory(Item_t * inventory, char *file_name)
{
	FILE *initial_file = fopen(file_name, "r");
	if (initial_file == NULL) {
		perror("Error opening initial inventory file");
		exit(1);
	}

	for (int i = 0; i < NO_OF_ITEMS; i++) {
		fscanf(initial_file, "%d %s %f %d",
		       &inventory[i].bar_code,
		       inventory[i].name,
		       &inventory[i].price, &inventory[i].count);
	}

	fclose(initial_file);
}

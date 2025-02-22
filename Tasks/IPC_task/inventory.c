#include "system.h"

void update_inventory(Item_t *inventory, int fd);

int main() {

	int fd;
	Item_t *inventory;

	//Open the inventory file
	fd = open(INVENTORY, O_RDWR);			
	if (fd == -1) {
		perror("Error opening inventory file");
		exit(1);
	}
	
	//Map the file into memory
	inventory =
	    mmap(NULL, SHOP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if (inventory == MAP_FAILED) {
		perror("Error mapping file");
		close(fd);
		exit(1);
	}

    //inventory updates
    while (1) {
    
        update_inventory(inventory, fd);
    }

    //unmap the memory before exiting
    if (munmap(inventory, SHOP_SIZE) == -1) {
        perror("Error unmapping file");
        exit(1);
    }
    
    close(fd);

    return 0;
}



void update_inventory(Item_t *inventory, int fd) {
    	int quantity , price;
	char item_name[30] = { };
	int len;

	// Ask for item Name and quantity
	do {
		printf("Enter item NAME to UPDATE: ");
		fgets(item_name, sizeof(item_name), stdin);

	} while (strcmp("\n", item_name) == 0);

	len = strlen(item_name);
	if (len > 0 && item_name[len - 1] == '\n') {
		item_name[len - 1] = '\0';
	}
	
	// search for the item in the inventory
	for (int i = 0; i < NO_OF_ITEMS; i++) {
		
		if (strcmp(inventory[i].name, item_name) == 0) {	//item exist
			printf("Enter quantity: '0 for unchange'");
			scanf("%d", &quantity);
			printf("Enter Price: '-1 for unchange'");
			scanf("%d", &price);
			
			//lock the file
			write_lock(fd);
			
			if (quantity > -1) {
				inventory[i].count += quantity;
			} 
			if(price > -1){
				inventory[i].price = price;
			}
			
			//unlock the file
			unlock(fd);
			
			break;
			
		} else if (i == NO_OF_ITEMS - 1)			//last item 
			printf("Invalid ITEM : %s\n", item_name);
	}
	
	close(fd);
	
}

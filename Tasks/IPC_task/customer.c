
#include "system.h"

void order_handler(Item_t * inventory, int fd);

int main()
{
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

	/****make the orders******/
	while (1) {

		order_handler(inventory, fd);	// Place an order and update inventory , locking the inventory while updating.

	}

	//Unmap the memory before exiting
	if (munmap(inventory, SHOP_SIZE) == -1) {
		perror("Error unmapping file");
		exit(1);
	}

	close(fd);

	return 0;
}

/***************************************************************** END OF MAIN **************************************************************************/

// Function to place an order
void order_handler(Item_t * inventory, int fd)
{
	int quantity;
	char item_name[30] = { };
	int len;

	// Ask for item Name and quantity
	do {
		printf("Enter item NAME: ");
		fgets(item_name, sizeof(item_name), stdin);

	} while (strcmp("\n", item_name) == 0);

	len = strlen(item_name);
	if (len > 0 && item_name[len - 1] == '\n') {
		item_name[len - 1] = '\0';
	}

	printf("Enter quantity: ");
	scanf("%d", &quantity);

	//lock the file
	write_lock(fd);

	// search for the item in the inventory
	for (int i = 0; i < NO_OF_ITEMS; i++) {
		if (strcmp(inventory[i].name, item_name) == 0) {	//item exist

			if (inventory[i].count >= quantity) {
				inventory[i].count -= quantity;
				printf("Order: %d piece(s) of %s\n", quantity,
				       inventory[i].name);
			} else {
				printf
				    ("Not enough stock for %s ,we will get a new stock soon :)\n",
				     inventory[i].name);
			}
			break;

		} else if (i == NO_OF_ITEMS - 1)	//last item 
			printf("Invalid ITEM : %s\n", item_name);
	}

	//unlock the file
	unlock(fd);
}

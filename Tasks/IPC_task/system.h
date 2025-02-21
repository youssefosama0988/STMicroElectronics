#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define INVENTORY 	"inventory.txt"
#define INIT_STOCK	"initial_stock.txt"
#define NO_OF_ITEMS 	4
#define SHOP_SIZE 	1024		//size of inventory file.



typedef struct{
    int id;
    char name[30];
    float price;
    int count;
}Item_t;


void read_lock(int fd);
void write_lock(int fd);
void unlock(int fd);

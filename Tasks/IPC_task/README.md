# Clothing Shop Simulation

##  Project Overview  
This project simulates a **multi-process Clothing Shop system** using **Inter-Process Communication (IPC)** mechanisms. The system consists of **three processes** that interact to manage inventory, handle customer orders, and update stock dynamically.  

## Features  
- **Shop Process**:   
  - Periodically prints the current stock.  
  - Reads the initial stock from a file.  
    
- **Customer Process**:  
  - Allows customers to place orders interactively.  
  - Supports multiple items with different quantities.  
  - Communicates with the Inventory to check stock availability.  
    
- **Inventory Manager Process**:  
  - Allows restocking of items when stock is low.  
  - Enables price updates interactively.    

## **Inter-Process Communication (IPC) Mechanisms Used**  
To ensure **efficient communication and synchronization**, the project utilizes:  
- **File-Based Memory Mapping (mmap)**: For shared access to inventory data.  
- **File Locking (fcntl)**: To prevent race conditions and ensure consistency.  
- **Processes directly edit the inventory file after acquiring the lock and release it after changes.**  


##  **How to Run the Project**  

### **1️⃣ Compile the Code**  
```bash
gcc shop.c sys.c -o shop 
gcc customer.c sys.c -o customer 
gcc inventory.c sys.c -o inventory_manager 
```

### **2️⃣ Run the Processes**  
- Start the shop process:  
  ```bash
  ./shop
  ```
- Start the inventory manager:  
  ```bash
  ./inventory_manager
  ```
- Start the customer process:  
  ```bash
  ./customer
  ```


##  **Future Improvements**  
- Add **multi-threading** for better concurrency.  
- Implement **database support** instead of file-based storage.  
- Improve **user interface** for better interaction.  

---

## for better Visualization

![Image](https://github.com/user-attachments/assets/ae2b1b17-a3f1-4a98-9d6b-92dd17304b53)

---
<br>

![Image](https://github.com/user-attachments/assets/c9d76890-820f-4c97-9723-30126226740b)

<br>

---
![Image](https://github.com/user-attachments/assets/1954c0c0-a9d7-43da-af4e-dd671d4dc98e) 

---
## Video 



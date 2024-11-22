# HTTP Server in C

This project is a basic HTTP server implemented in C. The server can handle requests from web browsers, process different types of resources, and respond appropriately.

## Features
**1-Connection Handling:**

  - Accepts and processes HTTP requests from web browsers.
        
**2-Request Processing:**

- Parses HTTP requests to determine the requested resource.
        
**3-Resource Handling:**

- Directories: Lists the contents of the directory.
- Regular Files: Returns the file's contents to the client.
- CGI Scripts: Executes the script and returns the output.
        
**4-Error Handling:** 

- Sends appropriate HTTP error messages for invalid requests or missing resources.
<br>

## Setup Instructions

  **Clone the Repository:**
```
  git clone <repository-url>
```

```
  /*get into this task dir.*/
```

**Compile the Server:**

      gcc server.c functions.c -o http

**Run the Server:**

      ./http <port>

***Example:***

      ./http 8888

<br>

## Usage

1-**Accessing the Server:**
    
- Open a web browser and navigate to:

      http://serverip:port 

- Example:
  
      http://localhost:8888  

2-**Testing Different Scenarios:**

  - ***List Directory Contents:*** Navigate to a directory (e.g., /public/docs/).
  - ***Access Regular Files:*** Access a file URL (e.g., /public/index.html).
- ***Run CGI Script:*** Access a CGI script (e.g., /example.cgi).
- ***Error Handling:*** Access a non-existent resource (e.g., /nonexistent).

<br>

## Example of CGI Script

 - An example Bash script (example.cgi) that outputs HTML:
```
#!/bin/bash
echo "Content-Type: text/html"
echo
echo "<html><body><h1>Hello from CGI!</h1></body></html>"
```
<br>

# Testing

- Use curl to test server responses:

      curl http://localhost:8888/index.html           // make sure that index.html is exist.

- Use a web browser to test the server visually.


<br>

## Video 
[Watch the Video](https://drive.google.com/file/d/1maUsrLE7vpFGDQwzWnXdhZAaUZ-CyDFS/view?usp=sharing)

<br>

------------

Feel free to contribute or report issues to improve the project! 😊





      

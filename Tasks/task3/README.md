  # My Shell

  simple shell support built in commands (myhelp , echo , pwd , mycp , mymv , myexit , type , cd , envir)

  Also,Any command in the PATH environment variable (ps,ls,man,cat,less ....etc)

  you can see the **output** below:
     

  ### Compilation Commands :
  ==========================
```
    git clone RepoURL
  
    gcc myshell.c commands.c -o shell
    ./shell
    
```
  
## Supported Commands : 
==========================

### *Built In Commands* :


1- **pwd**: print working directory.

2- **echo**: print a user input string on stdout 
 
 ex:


```

    echo Hello!
    Output : Hello!
    
```
  

3- **mycp**: copy a file to another file

   - Print error if the target file exists

  - if the user provide the target file name then use it, if the user provide the target path without file name use the  same source file name
  
  - -a option, to append the source content to the end of the target file.

    ex:

```

    mycp sourcePath targetPath -a
    
```

4- **mymv**: move a file to another place (mv sourcePath targetPath)

        
  - Print error if the target file exist
    
  - if the user provide the target file name then use it, if the user provide the target path without file name use the same source file name
        
  - -f option, to force overwriting the target file if exist    

    ex:

```

     mymv sourcePath targetPath -f
    
```
        
5- **myexit** : print "good bye" and terminate the shell

6- **myhelp**: print all the supported command with a brief info about each one.

7- **cd** path : change the current directory

8- **type** command: return the type of the command (built in, external or unsupported command)

9- **envir** : print all the environment variables.
      
**Also, Support pressing Enter to be similar to pressing Enter on Bash shell.**

### *External commands:*

**Any command in the PATH environment variable (ps,ls,cat....etc)**
 
   Support executing the programs using their names directly without the need to enter the full patch

## My Shell Output :
====================

![MyShellOutput(1)](https://github.com/user-attachments/assets/c010e08a-031f-4787-bbb7-c68cdab1eae9)

![MyShellOutput(2)](https://github.com/user-attachments/assets/590fa775-6c8b-4d10-bb2a-688abd894440)







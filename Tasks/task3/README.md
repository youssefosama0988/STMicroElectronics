  # My Shell

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

**Any command in the PATH environment variable (ps,ls,vim....etc)**
 
 Support executing the programs using their names directly without the need to enter the full patch

## My Shell Output :
====================

<img src ="https://github.com/user-attachments/assets/6044e646-9834-4542-af7b-3552a53780ea">

<img src ="https://github.com/user-attachments/assets/d45e3f13-96c8-48ba-b6d2-5519e64b0540">


***envir Command with an argument :***

![envirTest](https://github.com/user-attachments/assets/5c6e93cc-dd64-4c77-8384-cdfdf2d9d861)







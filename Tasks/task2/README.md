  ## My Shell

  ### Compilation Commands :
  ==========================
```

    gcc myshell.c commands.c -o shell
    ./shell
    
```
  
### Supported Commands :
========================

1- **pwd**: print working directory.

2- **echo**: print a user input string on stdout 

3- **cp**: copy a file to another file

   - Print error if the target file exists

  - if the user provide the target file name then use it, if the user provide the target path without file name use the  same source file name
  
  - -a option, to append the source content to the end of the target file.

    ex:

```

    cp sourcePath targetPath -a
    
```

4- **mv**: move a file to another place (mv sourcePath targetPath)

        
  - Print error if the target file exist
    
  - if the user provide the target file name then use it, if the user provide the target path without file name use the same source file name
        
  - -f option, to force overwriting the target file if exist    

    ex:

```

     mv sourcePath targetPath -f
    
```
        
5- **exit** : print "good bye" and terminate the shell

6- **help**: print all the supported command with a brief info about each one.
      
Also, Support pressing Enter to be similar to pressing Enter on Bash shell.

### My Shell Output :
=====================

<img src ="https://github.com/user-attachments/assets/6044e646-9834-4542-af7b-3552a53780ea">








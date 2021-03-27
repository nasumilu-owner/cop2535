# COP2535 - Project 4

## Description
Program builds upon an example found the the classes text by 
adding a cousin as a node to a `Person` class. Demonstrates a 
tree and how to traverse the tree to get list of cousins. 

## Usage
```bash
$ cd <project dir>
$ g++ project5.cpp -o bin/project5
$ ./bin/project5
```
Expected output
```bash
Kacey's Cousins:
        Emily
        Kyle
        Ann
        Elizabeth
        Kenny
        ... Omitted for brevity
```
## Note
- The program required the use of an OS dependent system command "cls". 
If compiled and used on a system which does not support the "cls" command
the program will output the following:
``` bash
sh: cls: command not found
```
- The project required the use of an OS dependent system command "pause".
If compiled and used on a system which does not support the "pause" command
the program will output the following:
```bash
sh: PAUSE: command not found
```
- Professor preferred that the project was a single file so no header files 
are include.
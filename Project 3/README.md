# COP2535 - Project 3

## Description
Demonstrate a linked list data structure which displays its contents 
forwards and in reverse.

## Usage
```bash
$ cd <project dir>
$ g++ project3.cpp -o bin/project3
$ ./bin/project3
```
Expected output
```bash
--- Project 3 ---
FORWARD:  Thisismylinkedtextfile.
BACKWARD: .eliftxetdeknilymsisihT
Thank you, have a nice day! :-)
```
## Note
- The program required the use of an OS dependent system command "cls". 
If compiled and used on a system which does not support the "cls" command
the program will output the following:
``` bash
sh: cls: command not found
```
- Professor preferred that the project was a single file so no header files 
are include.
- Text is read from a file named 'linedText.txt' and must be found in the current
directory.
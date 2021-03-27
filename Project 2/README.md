# COP2535 - Project 2

## Description
Reads a string from user input, then an integer, and finally outputs 
the character found at that offset. The range starts with 0 as the first
character.

## Usage
```bash
$ cd <project dir>
$ g++ project2.cpp -o bin/project2
$ ./bin/project2
```
Expected output
```bash
This program demonstrates bounds checking on a string object.
Enter a string: This is my string input

Legitimate string positions are: 0 - 22

Enter an positive integer describing a position inside or outside the string or \q to quit: 8

The character a position 8 is m

Enter an positive integer describing a position inside or outside the string or \q to quit: \q
Thank you! Have a great day :-)
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
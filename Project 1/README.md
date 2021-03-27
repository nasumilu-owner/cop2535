# COP2535 - Project 1

## Description
Bubble & selection sort & linear & binary search comparison

## Usage
```bash
$ cd <project dir>
$ g++ project1.cpp -o bin/project1
$ ./bin/project1
```
Expected output
```bash
Bubble sort used 10309 exchanges to sort the integer values found in ./random.txt.
Selecton sort used 197 exchanges to sort the integer values found in ./random.txt.
Linear search took 170 comparisons to find the value 869 at subscript 169
Binary search took 7 comparisons to find the value 869 at subscript 169
```
## Note
- The project required the use of an OS dependent system command "pause".
If compiled and used on a system which does not support the "pause" command
the program will output the following:
```bash
sh: PAUSE: command not found
```
- Reads a file of random numbers named 'random.txt' found in the current working
directory. 
## Pipe Operator

This goal of this lab is to implement a pipe operator for chaining multiple commands, allowing output of one command to serve as input to the next, similar to the Unix pipe mechanism.

## Building

Go to directory containing source code and Makefile. 
Run 'make'. (this compiles the source code and generates an executable named 'pipe')

## Running

To run the program, use the syntax `./pipe [command1] [command2...]`
For example, `./pipe` ls cat wc' is equivalent to `ls|cat|wc|`, so both will output the word count of the directory. 

The final output will display three numbers: the number of lines, the number of words, and the total number of characters from the `ls` command output.

## Cleaning up

To clean up and remove binary files, run `make clean`. This command removes the pipe executable and any object files generated during the build process.

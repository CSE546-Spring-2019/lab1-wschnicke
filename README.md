# Will Schnicke
# CSE 5462
# Ogle 9:35
# Lab 1

### Description
count.c will count the number of occurrences of a query string within a given
input file. The results and size of the input will be printed to the terminal
as well to a specified output file.

## Running count
Input must be of the following form:
    `./count <input-filename> <query-string> <output-filename>`

If the arguments are specified incorrectly, an error is written to the screen,
and the program exits

## Compiling
A simple makefile is also included. To compile count.c, simply use the `make`
command. The makefile relies on access to the gcc compiler. If you cannot use
gcc, the makefile can be edited to change the `CC` to a compiler of your choice.

## Testing
count was tested by using the example files and the example tests in output.htm
as well as others selected and verified independently.

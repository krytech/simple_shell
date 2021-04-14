#simple_shell

A simple shell

## Synopsis

Our homemade command line interpreter provides the user with a way to interact
with their system.  It is designed to function similarly to the bash unix shell.
By taking in input either directly or from a file, it will attempt to search
builts and the path to execute the given commands.  If found it will use the
systemcalled fork (), execve(), and wait () to execute the input. The results
will be returned to the user including possible errors. For a more detailed
featureset see the manual page: man_1_simple_shell.

## Installation

After cloning the repository, compile all the files by using:
`$ gcc -Wall -Werror -Wextra -pedantic *.c -o hsh`

Then run the shell program with:
`$ ./hsh`

This will give you a new prompt and the shell will wait for input.

## File Descriptions

**basic_shell.c** - Main simple_shell functions.

**built-ins.c** - Builtin functions for cd and exit.

**PATH_search.c** - Function to dynamically search the $PATH.

**error_handle.c** - Handles potential errors.

**linkedlist.c** - Various functions to help with linked lists.

**string.c** - Helper functions related to strings.

**globals.c** - Helper functions for environmental variables and line count.

**_strtok.c** - Hommemade strtok function (WIP).

**shell.h** - Header file containing all function prototypes, structs and libraries.

**README.md** - Description of the simple_shell program.

**man_1_simple_shell** - Manual page for simple_shell.

**AUTHORS** - Authors.

## Authors
Carson Stearn <cstearn@gmail.com> @krytech

Justin Masayda <justin.masayda@gmail.com> @keysmusician

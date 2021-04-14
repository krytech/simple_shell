# simple_shell

A simple shell

## Synopsis

Our homemade command line interpreter provides the user with a way to interact with their system. It is designed to function similarly to the [dash](https://wiki.archlinux.org/index.php/Dash) unix shell. By taking input either interactively or piped in via standard input (see **usage** below), simple_shell will attempt to execute commands by searching for built-ins and in the path. If a command is found, it will use the system calls `fork()`, `execve()`, and `wait()` to execute the input. The results will be displayed to the user including possible errors. For a more detailed featureset see the manual page: man_1_simple_shell.

## Installation
Clone this repository:
`git clone https://github.com/krytech/simple_shell.git`

Then, compile all the files:
`$ gcc *.c -o hsh`

## Usage

Run the shell program with:
`$ ./hsh`

This will launch the shell in **interactive mode** which will display a command prompt (`$ `) and the shell will wait for input.
Type the name of any command to execute it:

`$ echo Hello World!`

### Command separator

Simple_shell also supports the use of the command separator `;`. Use it to execute multiple commands in a single line:

`$ which ls ; echo "Here it is!"`

### Built-in commands
Simple_shell offers the following **built-ins**:

`cd [directory]` - (WIP) Changes the present working directory to _directory_. If no directory is entered, `cd` will change to the $HOME directory (run `env` to view the path of $HOME).

`env` - Displays all of the shell environment variables.

`exit [status]` - Exits the shell with exit code _status_. If no status is entered, the shell exits with the stauts of the last executed command.

## File Descriptions

**simple_shell.c** - Main simple_shell functions.

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
Carson Stearn <cstearn@gmail.com> [@krytech](https://github.com/krytech)

Justin Masayda <justin.masayda@gmail.com> [@keysmusician](https://github.com/keysmusician)

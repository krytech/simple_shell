#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h> /* malloc, free */
#include <string.h>
#include <sys/types.h> /* open */
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>


/* helper functions */
int _strlen(char *s);


/* our functions */


/* error functions */
int write_error(char c);
void error_main(char **av, char *command, int count);

#endif

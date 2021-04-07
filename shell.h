#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h> /* malloc, free */
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h> /* open */
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

/**
 * struct list_s - singly linked list
 * @str: (malloc'd) string
 * @len: length of the string
 * @next: pointer to the next node
 *
 * Description: singly linked list containing string data
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;
typedef list_t str_list_t;

/* helper functions */
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
void *_calloc(unsigned int nmemb, unsigned int size);

/* our functions */
str_list_t *split_str(char *const string, const char *dlmtr);
char **str_list_t_to_array(str_list_t *head);
void free_list(list_t *head);

/* error functions */
int write_error(char c);
void error_main(char **av, char *command, int count);

#endif	/* SHELL_H */

#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
/* #include <errno.h> maybe don't need */

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
int _strlen(const char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strncmp(const char *s1, const char *s2, unsigned int n);


/* Lists */
str_list_t *split_str(char *const string, const char *dlmtr);
char **str_list_t_to_array(str_list_t *head);
void free_list(list_t *head);

/* Error functions */
int write_error(char c);
void error_main(char **av, char *command, int count);

/* PATH */
list_t *add_node(list_t **head, const char *str);

/* execute */


#endif	/* SHELL_H */

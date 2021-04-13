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

/* linkedlist.c */
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

str_list_t *split_str(char *const string, const char *dlmtr);
char **str_list_t_to_array(str_list_t *head);
void free_list(list_t *head);
list_t *add_node(list_t **head, const char *str);

/* string.c */
unsigned int _strlen(const char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strncmp(const char *s1, const char *s2, unsigned int n);
char *_strdup(char *str);

/* env.c */
void env_builtin(void);
char **get_env(char ***env_address);
char *get_env_var(const char *get_var);

/* Error functions */
int write_error(char c);
void error_main(char **av, char *command, int count);

/* PATH */
list_t *PATH_search(list_t *input_ll);

/* our functions */
char *_strtok(char *str_in, char *delimit);

#endif	/* SHELL_H */

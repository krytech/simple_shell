#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
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

/* built-ins.c */
int cd(str_list_t *input_ll);
int env(list_t *input_ll);
int exit_built_in(list_t *input_ll, list_t *queue, int exit_code);

/* string.c */
unsigned int _strlen(const char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
int _strncmp(const char *s1, const char *s2, unsigned int n);
char *_strdup(const char *str);

/* globals.c */
char **get_argv(char ***argv_address);
int get_count(int *count_address);
char **get_env(char ***env_address);
char *get_env_var(const char *get_var);

/* error_handle.c */
void print_error(char *command);

char *_strmerge(size_t n_str, ...);

/* PATH_search.c */
int PATH_search(list_t **input_ll);

/**
 * struct built_in - named built-in functions
 * @name: name of the built-in
 * @function: pointer to the built-in function
 * Description: Used to pair built-in functions with their names
 */
typedef struct built_in
{
	char *name;
	int (*function)(list_t *input_ll);
} built_in_t;

/* _strtok.c */
char *_strtok(char *str_in, char *delimit);

#endif	/* SHELL_H */

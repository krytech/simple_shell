#include "shell.h"

/**
 * append_node - Inserts a new tail node
 * @head: Pointer to current head
 * @str: String to store in the new tail node
 * Return: Pointer to new tail; NULL on failure
 */
list_t *append_node(list_t **head, const char *str)
{
	list_t *new, *tail;
	size_t len = 0;

	if (!head)
		return (NULL);

	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);

	new->str = strdup(str);
	if (!new->str)
	{
		free(new);
		return (NULL);
	}

	while (new->str[len])
		len++;
	new->len = len;

	new->next = NULL;

	if (!*head)
	{
		*head = new;
		return (new);
	}
	tail = *head;
	while (tail->next)
		tail = tail->next;
	tail->next = new;

	return (new);
}

/**
 * free_list - Frees all nodes in a list_t linked list
 * @head: List head
 * Return: Void
 */
void free_list(list_t *head)
{
	list_t *node = head;

	while (node)
	{
		free(node->str);
		node = head->next;
		free(head);
		head = node;
	}
}


/**
 * split_str - splits a string into a str_list_t linked list
 * !NOTE! The caller must free() the returned linked list
 * @string: null terminated string to split
 * @dlmtr: delimiter(s)
 * Return: str_list_t linked list on success;
 * NULL if string or dlmtr is NULL;
 */
str_list_t *split_str(char *const string, const char *dlmtr)
{
	char *tok_ptr;
	str_list_t *head = NULL;

	if (!string || !dlmtr)
		return (NULL);

	/* Create nodes for each token */
	tok_ptr = strtok(string, dlmtr);
	while (tok_ptr)
	{
		if (!append_node(&head, tok_ptr))
		{
			free(head);
			return (NULL);
		}
		tok_ptr = strtok(NULL, dlmtr);
	}

	return (head);
}

/**
 * str_list_t_to_array - lists each string in a str_list_t in an array
 * !NOTE! The caller must free() the returned array
 * @head: head of the linked list
 * Return: malloc'd array of pointers to strings
 */
char **str_list_t_to_array(str_list_t *head)
{
	str_list_t *node;
	char **argv;
	size_t n_nodes, i = 0; /* argv itterator */

	/* Count nodes */
	node = head;
	for (n_nodes = 0; node; n_nodes++)
		node = node->next;

	/* Create array */
	argv = malloc(sizeof(char *) * (n_nodes + 1));
	if (!argv)
	{
		free(head);
		return (NULL);
	}

	/* Add elements to the array */
	for (node = head; node; node = node->next)
		argv[i++] = node->str;
	argv[i] = NULL; /* NULL terminate the array */

	return (argv);
}

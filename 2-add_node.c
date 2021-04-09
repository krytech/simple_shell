#include "shell.h"
/**
 * add_node - adds a new node at the begining of list_t
 * @head: double pointer to the start of list_t
 * @str: string to add
 * Return: pointer to the new element in the list, otherwise NULL if failed
 */

list_t *add_node(list_t **head, const char *str)
{
	list_t *new_node;

	if (str == NULL)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);

	new_node->str = strdup(str);
	new_node->len = _strlen(str);

	new_node->next = *head;

	*head = new_node;
	return (new_node);
}

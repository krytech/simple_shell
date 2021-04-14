#include "shell.h"

/**
 * PATH_search - searches the path for the input command
 * @input_ll: input command linked list
 * Return: pointer to the new first input node, otherwise NULL
 */

list_t *PATH_search(list_t **input_ll_p)
{
	unsigned int size;
	char *buff, *error_message;
	list_t *new_node, *path_ll, *path_ll_head, *input_ll = *input_ll_p;
	struct stat sb;

	if (!input_ll)
		return (NULL);
	/* check if input is a valid path which can be directly executed */
	if (stat(input_ll->str, &sb) == 0)
		return (input_ll);

	/* creates a dymanic path linked list */
	path_ll_head = split_str(get_env_var("PATH="), ":=");
	path_ll = path_ll_head;

	while (path_ll)
	{
		/* malloc buffer with slash and null */
		size = _strlen(path_ll->str) + _strlen(input_ll->str) + 2;
		buff = malloc(sizeof(char) * size);

		/* adds search criteria */
		_strcpy(buff, path_ll->str);
		_strcat(buff, "/");
		_strcat(buff, input_ll->str);

		/* using stat to run a search */
		if (stat(buff, &sb) == 0)
		{
			/* replaces first input_ll with buffer */
			new_node = input_ll->next;

			free(input_ll->str);
			free(input_ll);

			*input_ll_p = add_node(&new_node, buff);
			free(buff);

			free_list(path_ll_head);
			return (new_node); /* return pointer */
		}
		free(buff);
		path_ll = path_ll->next;
	}
	free_list(path_ll_head);

	error_message = _strmerge(2, input_ll->str, ": not found\n");
	print_error(error_message);
	free(error_message);

	return (NULL); /* return no match */
}

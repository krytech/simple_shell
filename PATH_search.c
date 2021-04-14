#include "shell.h"

/**
 * PATH_search - searches the path for the input command
 * @input_ll_p: address of linked list containing input command
 * Return: 0 on sucess, 127 if nothing found
 */

int PATH_search(list_t **input_ll_p)
{
	int NOTFOUND = 127, SUCCESS = 0;
	char *buff, *error_message;
	list_t *new_node, *path_ll, *path_ll_head, *input_ll = *input_ll_p;
	struct stat sb;

	if (!input_ll)
		return (NOTFOUND);
	/* check if input is a valid path which can be directly executed */
	if (stat(input_ll->str, &sb) == 0)
		return (SUCCESS);

	/* creates a dymanic path linked list */
	path_ll_head = split_str(get_env_var("PATH="), ":=");

	for (path_ll = path_ll_head; path_ll; path_ll = path_ll->next)
	{	/* Merge path and command */
		buff = _strmerge(3, path_ll->str, "/", input_ll->str);

		/* using stat to run a search */
		if (stat(buff, &sb) == 0)
		{	/* replaces first input_ll with buffer */
			new_node = input_ll->next;
			free(input_ll->str);
			free(input_ll);
			*input_ll_p = add_node(&new_node, buff);
			free(buff);
			free_list(path_ll_head);
			return (SUCCESS);
		}
		free(buff);
	}
	free_list(path_ll_head);

	error_message = _strmerge(2, input_ll->str, ": not found\n");
	print_error(error_message);
	free(error_message);

	return (NOTFOUND);
}

#include "shell.h"


/**
 * can_execute - checks if a string represents an executable path
 * @command: string containing the command to check
 * Return: 0 on sucess, 127 if file does not exist
 * 126 if file exists but cannot be executed
 */

int can_execute(char *command)
{
	char *error_message;
	int DENIED = 126, NOTFOUND = 127, SUCCESS = 0;

	if (access(command, X_OK) == 0)
		return (SUCCESS);
	else if (access(command, F_OK) == 0)
	{ /* File exists but cannot be executed */
		error_message = _strmerge(2, command, ": Permission denied\n");
		print_error(error_message);
		free(error_message);
		return (DENIED);
	}
	else
		return (NOTFOUND);

}

/**
 * PATH_search - searches the path for the input command
 * @input_ll_p: address of linked list containing input command
 * Return: 0 on sucess, 127 if nothing found
 */

int PATH_search(list_t **input_ll_p)
{
	int NOTFOUND = 127, DENIED = 126, SUCCESS = 0, access_code;
	char *buff, *error_message;
	list_t *new_node, *path_ll, *path_ll_head, *input_ll = *input_ll_p;

	if (!input_ll)
		return (NOTFOUND);
	/* check if input is a valid path which can be directly executed */
	access_code = can_execute(input_ll->str);
	if (access_code == SUCCESS)
		return (SUCCESS);
	else if (access_code == DENIED)
		return (DENIED);

	/* creates a dymanic path linked list */
	path_ll_head = split_str(get_env_var("PATH="), ":=");

	for (path_ll = path_ll_head; path_ll; path_ll = path_ll->next)
	{	/* Merge path and command */
		buff = _strmerge(3, path_ll->str, "/", input_ll->str);

		/* using stat to run a search */
		if (access(buff, F_OK) == 0)
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

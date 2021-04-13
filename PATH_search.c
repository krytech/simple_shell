#include "shell.h"

/**
 * PATH_search - searches the path for the input command
 * @cmd: pointer to string with command
 * @pptr: pointer to path string
 * Return: pointer to the new first input node, otherwise NULL
 */

list_t *PATH_search(list_t **input_ll_p)
{
	unsigned int size;
	char *buff;
	list_t *new_node, *path_ll, *path_ll_head, *input_ll = *input_ll_p;
	struct stat sb;

	path_ll_head = split_str(get_env_var("PATH="), ":=");
	path_ll = path_ll_head;
	while (path_ll)
	{
		/* malloc buffer */
		size = _strlen(path_ll->str) + _strlen(input_ll->str) + 2; /* null and slash */
		buff = malloc(sizeof(char) * size);

		_strcpy(buff, path_ll->str);
		_strcat(buff, "/");
		_strcat(buff, input_ll->str);

 		if (stat(buff, &sb) == 0)
		{
			new_node = input_ll->next;

			free(input_ll->str);
			free(input_ll);

			*input_ll_p = add_node(&new_node, buff);
			free(buff);
			free_list(path_ll_head);
			return (new_node);
		}
		free(buff);
		path_ll = path_ll->next;
	}
	free_list(path_ll_head);
	return (NULL); /* no match */
}

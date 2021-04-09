#include "shell.h"

/**
 * PATH_search - searches the path for the input command
 * @cmd: pointer to string with command
 * @pptr: pointer to path string
 * Return: pointer to the new first input node, otherwise NULL
 */

list_t *PATH_search(list_t *input_ll, list_t *path_ll)
{
	unsigned int size;
	char *buff;
	list_t *new_node;
	struct stat sb;

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

			input_ll = add_node(&new_node, buff);
			free(buff);
			return (input_ll);
		}
		free(buff);
		path_ll = path_ll->next;
	}
	return (NULL); /* no match */
}
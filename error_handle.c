#include "shell.h"

/**
 * write_error - simple print error func for count
 */

int write_error(char c)
{
	return (write(STDERR_FILENO, &c, 1));
}

/**
 * error_main - function to print the error command as per the example
 * @message: error message from the command that error'd
 */

void print_error(char *message)
{
	int mul = 1, numlen = 1, count = get_count(NULL);
	int copy = count;
	char *shell = get_argv(NULL)[0];

	/* writes error path */
	write(STDERR_FILENO, shell, _strlen(shell));
	write(STDERR_FILENO, ": ", 2);

	/* error count */
	while (copy >= 10)
	{
		copy /= 10;
		mul *= 10;
		++numlen;
	}
	while (numlen > 1)
	{
		if ((count / mul) < 10)
			write_error((count / mul) + '0');
		else
			write_error((count / mul) % 10 + '0');
		--numlen;
		mul /= 10;
	}
	/* write command error */
	write_error(count % 10 + '0');
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, message, _strlen(message));
}

/**
 * _strmerge - merges any number of strings into a single array
 * @n_str: number of strings being merged. Returns NULL of n = 0.
 * Return: a single merged string (caller must free)
 */
char *_strmerge(size_t n_str, ...)
{
	char *va_string, *merge = NULL, **string_ptrs = NULL;
	va_list strings;
	size_t array_size = 0, i;

	if (!n_str)
		return (NULL);

	va_start(strings, n_str);

	string_ptrs = malloc(sizeof(char *) * n_str);
	if (!string_ptrs)
		return (NULL);

	for (i = 0; i < n_str; i++)
	{
		va_string = va_arg(strings, char *);
		string_ptrs[i] = va_string;
		array_size += _strlen(va_string);
	}

	merge = malloc(array_size + 1); /* +1 for null byte */
	if (!merge)
		return (NULL);
	merge[0] = '\0';
	for (i = 0; i < n_str; i++)
		_strcat(merge, string_ptrs[i]);

	free(string_ptrs);
	va_end(strings);
	return (merge);
}

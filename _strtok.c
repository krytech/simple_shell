#include "shell.h"

/**
 * _finddel - finds the delimiter where it matches in the string
 * @str: string input to check
 * @delimit: delimiters to check for
 * Return: matched delimiter
 */

char _finddel(char *str, const char *delimit)
{
	int i = 0;
	int j;

	while (str[i])
	{
		j = 0;
		while (delimit[j])
		{
			if (str[i] == delimit[j])
				return (delimit[j]);
			j++;
		}
		i++;
	}
	return (delimit[0]);
}

/**
 * _strchr - located the delimiter in the string
 * @str: string to check
 * @c: delimiter to look for
 * Return: returns the string after the delimiter, otherwise NULL
 */

char *_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	if (c == 0)
		return (str);

	return (NULL);
}

/**
 * _strtok2 - homemade strtok function, breaks up a input string into tokens
 * @str_in: input string to tokenize
 * @delimit: delimiters used to make tokens from string
 * Return: pointer to the current delimited token
 */

char *_strtok2(char *str_in, const char *delimit)
{
	static char *string;
	char *token = NULL;
	char *next = NULL;
	int i = 0;
	char deli = '\0';

	if (str_in)
		string = str_in;

	token = string;
	if (token == NULL)
		return (NULL);

	deli = _finddel(string, delimit);
	next = _strchr(string, deli);

	if (next)
	{
		i = _strlen(string);
		i -= _strlen(next);
		token = string;
		next++;
		string = next;
		token[i] = '\0';
	}
	if (next == NULL)
	{
		token = string;
		string = NULL;
	}
	return (token);
}

/**
 * _strtok - main strtok function
 * @str: string to tokenize
 * @delim: delimiters
 * Return: tokens from string
 */

char *_strtok(char *str, const char *delim)
{
	char *token;

	token = _strtok2(str, delim);

	while (token)
	{
		if (token[0] == '\0')
			token = _strtok2(NULL, delim);
		else
			return (token);
	}
}

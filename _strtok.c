#include "shell.h"

/**
 * _strtok - homemade strtok function, breaks up a input string into tokens
 * @str_in: input string to tokenize
 * @delimit: delimiters used to make tokens from string
 * Return: pointer to the current delimited token
 */

char *_strtok(char *str_in, char *delimit)
{
	static char *string;
	int i, j;
	char *tmp;

	if (str_in)
		string = str_in;
	/*
	 * go over the string to check for the delimiter
	 * and replace it with a null byte using tmp to store
	 * the current token to return
	 */
	if (string)
	{
		for (i = 0; string[i]; i++)
		{
			for (j = 0; delimit[j]; j++)
			{
				if (string[i] == delimit[j])
				{
					string[i] = '\0';
					tmp = string;
					string = string + i + 1;
					return (tmp);
				}
			}
		}
		return (string);
	}
	return (NULL);
}

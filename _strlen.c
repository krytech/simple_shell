#include "shell.h"

/**
 * _strlen - prints the length of a string
 * @s: string
 * Return: string length value
 */

int _strlen(char *s)
{
	int length;

	while (*s != '\0')
	{
		length++;
		s++;
	}
	return (length);
}

#include "shell.h"

/**
 * _strlen - prints the length of a string
 * @s: string
 * Return: string length value
 */
unsigned int _strlen(const char *s)
{
	int length = 0;

	if (!s)
		return (length);

	while (s[length] != '\0')
		length++;

	return (length);
}

/**
 * _strcpy - copies the string pointed to by src,
 * including the terminating null byte (\0), to the buffer pointed to by dest
 * @dest : destination buffer
 * @src : source string
 * Return: pointer to dest. If src is NULL, dest remains unchanged.
 */
char *_strcpy(char *dest, char *src)
{
        char *end = src;
        int i, len;

        if (!src)
                return (dest);

        while (*end != '\0')
                end++;

        len = end - src;

        for (i = 0; i <= len; i++)
                dest[i] = src[i];

        return (dest);
}

/**
 * _strcat - concatenates two strings
 * @dest : string to be appended to
 * @src : string to append
 * Return: concatenation of strings. If src is NULL, dest remains unchanged
 */
char *_strcat(char *dest, char *src)
{
	int dest_end = 0;
	int i = 0;

	if (!src)
		return (dest);

	while (dest[dest_end] != '\0')
		dest_end++;

	while (src[i] != '\0')
	{
		dest[dest_end + i] = src[i];
		i++;
	}

	dest[dest_end + i] = '\0';

	return (dest);
}

/**
 * _strncmp - compares the first n bytes of two strings
 * @s1: first string
 * @s2: second string
 * @n: number of bytes to compare; if n = 0, the full lengths of the strings
 * are compared until one terminates (with a null byte).
 * Return: difference between first unequal ASCII char values
 */
int _strncmp(const char *s1, const char *s2, unsigned int n)
{
	int i = 0;
	int comp_all_flag = !n;

	while (s1[i] != '\0' && s2[i] != '\0' && (--n || comp_all_flag))
	{
		if (s1[i] != s2[i])
			break;
		i++;
	}

	return (s1[i] - s2[i]);
}

/**
 * _strdup - allocates memory and copies a string from input
 * @str: string to copy
 * Return: pointer to copied string, otherwise NULL
 */

char *_strdup(const char *str)
{
	char *s;
	unsigned int i;
	unsigned int length = 0;

	if (!str)
		return (NULL);

	while (str[length])
		length++;

	s = malloc(sizeof(char) * length + 1);

	if (!s)
		return (NULL);

	else
	{
		for (i = 0; i <= length; i++)
			s[i] = str[i];
	}
	return (s);
}

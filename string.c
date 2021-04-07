/**
 * _strlen - prints the length of a string
 * @s: string
 * Return: string length value
 */
unsigned int _strlen(char *s)
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
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 * Return: the number value of the comparison
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	if (s1[i] == s2[i])
	{
		return (0);
	}
	else
	{
		return (s1[i] - s2[i]);
	}
}


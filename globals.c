#include "shell.h"

/**
 * get_env - returns the shell environment
 * @env_address: address of the environment array
 * Only to be used to initialize the value
 * Consecutive calls should be passed NULL
 * Return: the environment (pointer to an array of strings)
 */
char **get_env(char ***env_address)
{
	static char **env;

	/* Initialize static variable. Should only be done once. */
	if (env_address)
		env = *env_address;
	return (env);
}

/**
 * get_argv - returns the main argument vector
 * @argv_address: address of argv
 * Only to be used to initialize the value
 * Consecutive calls should be passed NULL
 * Return: argv (pointer to an array of strings)
 */
char **get_argv(char ***argv_address)
{
	static char **argv;

	/* Initialize static variable. Should only be done once. */
	if (argv_address)
		argv = *argv_address;
	return (argv);
}

/**
 * get_count - returns the line count
 * @count_address: address of the count variable
 * Only to be used to initialize the value
 * Consecutive calls should be passed NULL
 * Return: line count
 */
int get_count(int *count_address)
{
	static int *count;

	/* Initialize static variable. Should only be done once. */
	if (count_address)
		count = count_address;
	return (*count);
}

/**
 * get_env_var - get the pointer to a specified environment variable
 * @get_var: the environment variable to find; must be terminated with '='
 * Return: pointer to the matching environment variable; NULL if not found
 */
char *get_env_var(const char *get_var)
{
	unsigned int var;
	int len = _strlen(get_var);
	int diff;
	char **env = get_env(NULL);

	for (var = 0; env[var]; var++)
	{
		diff = _strncmp(env[var], get_var, len);
		if (diff == 0)
			return (env[var]);
	}
	return (NULL);
}

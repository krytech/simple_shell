#include "shell.h"

/**
 * get_env - returns the environment
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

/**
 * env_builtin - prints all environment variables
 * @input_ll - linked list
 * Return: -1 if input_ll is NULL, otherwise 0
 */
int env(list_t *input_ll)
{
	int var;
	char **env = get_env(NULL);

	for (var = 0; env[var]; var++)
	{
		write(STDOUT_FILENO, env[var], _strlen(env[var]));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (-!input_ll);
}

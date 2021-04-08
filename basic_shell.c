#include "shell.h"

/**
 * get_env_var - get the pointer to a specified environment variable
 * @env: environment variable array
 * @get_var: the environment variable to find; must be terminated with '='
 * Return: pointer to the matching environment variable; NULL if not found
 */
char *get_env_var(char **env, const char *get_var)
{
	unsigned int var;
	int len = _strlen(get_var);
	int diff;

	for (var = 0; env[var]; var++)
	{
		diff = _strncmp(env[var], get_var, len);
		if (diff == 0)
			return (env[var]);
	}
	return (NULL);
}

/**
 * execute - creates and executes child process with arguments
 * @argv: command line arguments to pass to the child process
 */
void execute(char **argv)
{
	pid_t pid;

	pid = fork(); /* Create a child process */
	if (pid == -1)
		exit(EXIT_FAILURE);

	else if (pid == 0) /* Inside the child process: */
	{ /* Try to execute string arguments as a command */
		if (execve(argv[0], argv, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	if (wait(NULL) == -1) /* Let the child process exit before continuing */
		exit(EXIT_FAILURE);
}


/**
 * main - Thompson Shell imitation
 * @argc: number of command line arguments
 * @argv: command line arguments
 * @env: environment variables
 * Return: always 0 (needs to be updated)
 */
int main(int argc, char **argv, char **env)
{
	int getl_r;
	size_t buff_len = 0;
	char *buffer = NULL, *PATH = get_env_var(env, "PATH=");
	char **child_argv = NULL;
	str_list_t *child_CLA = NULL;
	int count = 0;

	while (1) /* Loop until forced to quit */
	{
		write(STDOUT_FILENO, "$", 1); /* Display the command prompt */
		/* Wait for and store user input */
		getl_r = getline(&buffer, &buff_len, stdin);
		if (getl_r == -1) /* ^D or other failure */
			count++; /* count for enter */
			break;
		/* Format input for execution */
		/* Create a linked list from the input */
		child_CLA = split_str(buffer, " \n");
		/* Create argv from the linked list */
		child_argv = str_list_t_to_array(child_CLA);
		count++; /* count for errors or execution */
		/* run search_path fuction */
		/* if search_path fails, run error_handle.c */
		/* if search finds the func, run execute */
		execute(child_argv); /* Execute the child process */
		free_list(child_CLA);
		free(child_argv);
	}
	write(STDOUT_FILENO, "\n", 1); /* Print newline before closing */
	free(buffer);
	return (0);
	/* TEMPORARY SECTION TO GET AROUND COMPILATION WARNINGS */
	argc += 0;
	argv += 0;
	env += 0;
}

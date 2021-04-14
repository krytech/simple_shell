#include "shell.h"

/**
 * cd - changes present working directory
 * @input_ll: linked list containing any arguments
 * Return: 0 on success, 2 on error
 */
int cd(str_list_t *input_ll)
{
	char *dir, *error;
	int status = 0;
	str_list_t *HOME = split_str(get_env_var("HOME="), "="),
		   *OLDPWD = split_str(get_env_var("OLDPWD="), "=");

	/* still need to allow variable expansion for $HOME */
	/* And update env vars */
	if (input_ll)
	{
		dir = input_ll->str;
		/* Check for - */
		if (_strncmp(dir, "-", 0) == 0)
			/* Check OLDPWD for NULL first? */
			status = chdir(OLDPWD->next->str);
		else
			status = chdir(dir);
		/* if chdir worked, Update PWD & OLDPWD*/
		/* char *getcwd(char *buf, size_t size); */
	}
	else if (HOME->next)
		status = chdir(HOME->next->str);
		/* if chdir worked, Update PWD & OLDPWD */

	if (status == -1)
	{	/* print error message */
		error = _strmerge(3, "cd: can't cd to ", input_ll->str, "\n");
		print_error(error);
		free(error);
		status = 2;
	}
	free_list(HOME);
	return (status);
}

/**
 * env - prints all environment variables
 * @input_ll - linked list (mostly useless, required for
 * prototype consistency with other built-ins)
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

/**
 * exit_built_in - closes the shell
 * @input_ll - linked list which may contain an exit code.
 * Prints an error if an invalid exit code was entered.
 * @queue - the command queue, so it can be free_list()'d
 * @exit_code - the exit code of the last command. Used
 * by default if no exit code is entered in input_ll.
 * Return: 2 on error, otherwise, does not return
 */
int exit_built_in(list_t *input_ll, list_t *queue, int exit_code)
{
	char *error;
	char *user_code;

	if (input_ll)
	{
		if (input_ll->next)
		{
			user_code = input_ll->next->str;
			/* RREPLACE ATOI */
			exit_code = atoi(user_code);
			/* If invalid number entered */
			if (exit_code <= 0 &&
			    _strncmp(user_code, "0", 0))
			{
				error = _strmerge(4, "exit: ", "Illegal number: ",
						 input_ll->next->str, "\n");
				print_error(error);
				free(error);
				return (2);
			}
		}
	}
	free_list(input_ll);
	free_list(queue);
	exit(exit_code);
}

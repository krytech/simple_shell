#include "shell.h"

/**
 * execute - creates and executes child process with arguments
 * @input_ll: linked list of commands for the child process
 */
void execute(str_list_t *input_ll)
{
	pid_t pid;
	char **child_argv = NULL;

	/* Create argv from the linked list */
	child_argv = str_list_t_to_array(input_ll);

	pid = fork(); /* Create a child process */
	if (pid == -1)
		exit(EXIT_FAILURE);

	else if (pid == 0) /* Inside the child process: */
	{ /* Try to execute string arguments as a command */
		if (execve(child_argv[0], child_argv, NULL) == -1)
			exit(EXIT_FAILURE);
	}
	if (wait(NULL) == -1) /* Let the child process exit before continuing */
		exit(EXIT_FAILURE);
	free(child_argv);
}

/**
 * get_input - Displays a prompt and retrieves user input
 * @input_ll: address of a string linked list pointer
 * input will be converted to a linked list and the address stored here
 * !NOTE! This pointer WILL be overwritten with a new address. It must
 * be free_list()'d before calling get_input() again to prevent memory leaks.
 * Return: 0 if getline fails, 1 on success
 */
int get_input(str_list_t **input_ll)
{
	int getl_r = 0;
	size_t buff_len = 0;
	char    *buffer = NULL,
		*prompt = "$",
		*delimiters = " \n\t";

	*input_ll = NULL;
	/* Display the command prompt */
	write(STDOUT_FILENO, prompt, _strlen(prompt));

	/* Wait for and store user input */
	getl_r = getline(&buffer, &buff_len, stdin);
	if (getl_r == -1) /* ^D or other failure */
	{
		free(buffer);
		return (0);
	}
	/* Format input for execution */
	/* Create a linked list from the input */
	*input_ll = split_str(buffer, delimiters);

	free(buffer);
	return (1);
}

/**
 * built_in - checks if input is calling a shell built-in
 * and executes the built in (may move that part to another function)
 * @input_ll: input string linked list
 * Return: ????????????
 * !NOTE! WILL SEGFAULT IF INPUT IS NULL
 */
int built_in(str_list_t *input_ll)
{
	int built_in;
	char *built_ins[] = {
		"alias",
		"cd",
		"env",
		"exit",
		"help",
		"setenv",
		"unsetenv",
		NULL
	};
	/* Check input's head node for a built-in command */
	/* Find the index of the built-in */
	for (built_in = 0; built_ins[built_in]; built_in++)
	{
		if (_strncmp(input_ll->str, built_ins[built_in], 0) == 0)
			break;
	}
	/* Call the appropriate built-in */
	switch (built_in)
	{
	case 0:
		/* alias(); */
		break;
	case 1:
		/* cd(); */
		break;
	case 2:
		env_builtin();
		break;
	case 3: /* exit_builtin(); */
		free_list(input_ll);
		/* if (input_ll->next) exit(atoi(input_ll->next->str)); */
		/* else */
		exit(0);
	/* ... */
	case 7:
		return (0);
	}
		return (1);
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
	char *PATH;
	str_list_t *child_CLA = NULL;
	int count = 0;

	get_env(&env);
	PATH = get_env_var("PATH=");
	while (1) /* Loop until forced to quit */
	{
		/* Get user input and generate a linked list */
		if (!get_input(&child_CLA))
			break;/* Close shell if user enters ^D */
		count++; /* count for errors or execution */

		/* Continue if no commands were entered */
		if (!child_CLA)
			continue;

		/* Check for and execute built-ins */
		if (!built_in(child_CLA))
		{
			/* If no built-in was found, run search_path fuction */
			/* if search_path fails, run error_handle.c */
			/* if search finds the func, execute child process */
			execute(child_CLA);
		}
		free_list(child_CLA);
	}
	write(STDOUT_FILENO, "\n", 1); /* Print newline before closing */
	return (0);
	/* TEMPORARY SECTION TO GET AROUND COMPILATION WARNINGS */
	argc += !(argv || env || PATH);
}

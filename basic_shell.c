#include "shell.h"

/**
 * get_input - Displays a prompt and retrieves user input
 * @input_ll: address of a string linked list pointer
 * input will be converted to a linked list and the address stored here
 * !NOTE! This pointer WILL be overwritten with a new address. It must
 * be free_list()'d before calling get_input() again to prevent memory leaks.
 * Return: 0 if getline fails, 1 on success
 * !NOTE! Yes, these return values are inconsistent
 */
int get_input(str_list_t **queue)
{
	int getl_r = 0, i;
	size_t buff_len = 0;
	char    *buffer = NULL,
		*prompt = "$";

	*queue = NULL;
	/* Display the command prompt */
	write(STDOUT_FILENO, prompt, _strlen(prompt));

	/* Wait for and store user input */
	getl_r = getline(&buffer, &buff_len, stdin);
	if (getl_r == -1) /* ^D or other failure */
	{
		free(buffer);
		write(STDOUT_FILENO, "\n", 1); /* Print newline before closing */
		return (0);
	}
	/* Save input line to history */
	/* Format input for execution */
	/* Strip out any comments "#" */
	for (i = 0; buffer[i]; i++)
	{
		if (buffer[i] == '#')
		{
			buffer[i] = '\0';
			break;
		}
	}
	/* Split into statements based on the command separator ";" */
	/* And add statements to a queue */
	*queue = split_str(buffer, ";\n");

	free(buffer);
	return (1);
}

/**
 * get_built_in - checks if input is calling a shell built-in and
 * returns a pointer to a built-in function if it finds one
 * @built_in_name: the name of the built-in to return
 * Return: pointer to the appropriate built-in; NULL if not found
 */
int (*get_built_in(char *built_in_name))(list_t *)
{
	int built_in;
	built_in_t built_ins[] = {
		/* {"alias", alias}, */
		{"cd", cd},
		{"env", env},
		/* {"exit", exit_built_in}, */
		/* {"help", help}, */
		/* {"setenv", setenv}, */
		/* {"unsetenv", unsetenv}, */
		{NULL, NULL}
	};

	/* Find the index of the built-in */
	for (built_in = 0; built_ins[built_in].name; built_in++)
	{
		if (_strncmp(built_in_name, built_ins[built_in].name, 0) == 0)
			return (built_ins[built_in].function);
	}
	return (NULL);
}

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
 * main - dash imitation
 * @argc: number of command line arguments
 * @argv: command line arguments
 * @env: environment variables
 * Return: always 0 (needs to be updated)
 */
int main(int argc, char **argv, char **env)
{
	int (*built_in)(list_t *);
	char *delimiters = " \t";
	str_list_t *input_ll = NULL, *queue = NULL, *command;
	int count = 0, loop = 1, exit_code = 0;

	get_env(&env);
	while (loop) /* Loop until forced to quit */
	{
		/* Get user input and generate a linked list */
		if (!get_input(&queue))
			break;/* Close shell if user enters ^D */

		count++; /* count for errors or execution */

		/* While there are statements in the queue... */
		for (command = queue; command; command = command->next)
		{
			/* Create linked list from each queued statement */
			input_ll = split_str(command->str, delimiters);
			/* Null check */
			if (!input_ll)
				break;

			if (_strncmp("exit", input_ll->str, 0) == 0)
			{
				/* this will be the last loop */
				loop = 0;
				/* in the user entered an exit code, save it */
				if (input_ll->next)
					exit_code = atoi(input_ll->next->str);
				/* We can't use atoi, also if atoi fails, print an error */
			}
			/* Check for and execute built-ins */
			else if ((built_in = get_built_in(input_ll->str)))
				exit_code = built_in(input_ll->next);
			/* If no built-in was found, run search_path fuction */
			else if (PATH_search(&input_ll))
				/* if search finds the func, execute child process */
				execute(input_ll);
			else
				/* if search_path fails, print an error */
				error_main(argv, input_ll->str, count);
			free_list(input_ll);
		}
		free_list(queue);
	}
	exit(exit_code);
	return (0);
	/* TEMPORARY SECTION TO GET AROUND COMPILATION WARNINGS */
	argc += 0;
}

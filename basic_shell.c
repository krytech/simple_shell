#include "shell.h"

int main(void)
{
	int getl_r, exec = 0;
	size_t len = 0;
	pid_t pid;
	char *buffer = NULL;
	str_list_t *child_CLAs = NULL;
	char **argv = NULL;
	char *prmpt = "Holberton Shell$";

	while (1) /* Loop until forced to quit */
	{
		printf("%s", prmpt); /* Display the command prompt */
		getl_r = getline(&buffer, &len, stdin); /* Wait for and store user input */
		if (getl_r == -1) /* ^D or other failure */
			break;
		/* Format input for execution */
		child_CLAs = split_str(buffer, " \n"); /* Create a linked list from the input */
		argv = str_list_t_to_array(child_CLAs); /* Create argv from the linked list */
		pid = fork(); /* Create a child process */
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0) /* Inside the child process: */
		{
			exec = execve(argv[0], argv, NULL); /* Attempt to execute the string arguments as a command */
			if (exec == -1)
			{
				exit(EXIT_FAILURE);
			}
		}
		if (wait(NULL) == -1) /* Let the child process exit before continuing */
			exit(EXIT_FAILURE);
		free_list(child_CLAs);
		free(argv);
	}
	free(buffer);
	return (0);
}

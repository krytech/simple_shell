#include "shell.h"

int main(void)
{
	int exec = 0, getl_r;
	size_t len = 0;
	pid_t pid;
	char *buffer = NULL;
	char *argv[] = {NULL, NULL};
	char *prmpt = "Holberton Shell$";

	while (1) /* Loop until forced to quit */
	{
		printf("%s", prmpt); /* Display the command prompt */
		getl_r = getline(&buffer, &len, stdin); /* Wait for and store user input */
		if (getl_r == -1)
			break;

		pid = fork(); 	/* Create a child process */
		if (pid == -1)
			exit(EXIT_FAILURE);
		else if (pid == 0) /* Inside the child process: */
		{
			argv[0] = strtok(buffer, "\n"); /* Format input for execution */
			exec = execve(argv[0], argv, NULL); /* Attempt to execute the string as a command */
			if (exec == -1)
				exit(EXIT_FAILURE);

		}
		if (wait(NULL) == -1) /* Let the child process exit before continuing */
			exit(EXIT_FAILURE);
	}
	free(buffer);
	return (0);
}
